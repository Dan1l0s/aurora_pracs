/****************************************************************************
**
** Copyright (C) 2020 Open Mobile Platform LLC.
** Contact: https://community.omprussia.ru/open-source
**
** This file is part of the System Info project.
**
** $QT_BEGIN_LICENSE:BSD$
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Open Mobile Platform LLC copyright holder nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL OPEN MOBILE PLATFORM LLC OR
** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "packageinfoprovider.h"

PKA_NAMESPACE_USE

/*!
 * \brief Constructor of the PackageInfoProvider class.
 * \param parent Ancestor object.
 */
PackageInfoProvider::PackageInfoProvider(QObject *parent)
    : QObject(parent),
      m_architecture(QString()),
      m_description(QString()),
      m_errorString(QString()),
      m_hasError(false),
      m_license(QString()),
      m_name(QString()),
      m_packageId(QString()),
      m_searchTransaction(nullptr),
      m_size(0),
      m_status(QString()),
      m_summary(QString()),
      m_resolveTransaction(nullptr),
      m_version(QString()),
      m_url(QString())
{
}

/*!
 * \brief Forms information about a package with a given identifier.
 * \param packageId Package identifier.
 */
void PackageInfoProvider::setPackageId(QString packageId)
{
    // Search transaction already exists
    if (m_searchTransaction != nullptr || m_resolveTransaction != nullptr)
        return;

    m_hasError = false;
    emit hasErrorChanged();

    m_packageId = packageId;
    m_architecture = Transaction::packageArch(packageId);
    m_name = Transaction::packageName(packageId);
    m_version = Transaction::packageVersion(packageId);
    emit packageIdChanged();
    emit generalDataChanged();

    m_searchTransaction = Daemon::details(packageId);
    connect(m_searchTransaction, &Transaction::info,
            this, &PackageInfoProvider::_storePackageDetails);
    connect(m_searchTransaction, &Transaction::finished,
            this, &PackageInfoProvider::_processStoreTransactionCompletion);

    m_resolveTransaction = Daemon::resolve(m_name);
    connect(m_resolveTransaction, &Transaction::package,
            this, &PackageInfoProvider::_addPackageInfo);
    connect(m_resolveTransaction, &Transaction::finished,
            this, &PackageInfoProvider::_processResolveTransactionCompletion);
};

/*!
 * \brief Removes a request to get general information about a package after a search is complete.
 * \param status Completion status of the request.
 * \param runtime Request runtime.
 */
void PackageInfoProvider::_processStoreTransactionCompletion(Exit status, quint32 runtime)
{
    Q_UNUSED(runtime);
    m_searchTransaction = nullptr;
    _processExitStatus(status);
}

/*!
 * \brief Removes the request to get the package status after the search is complete.
 * \param status Completion status of the request.
 * \param runtime Request runtime.
 */
void PackageInfoProvider::_processResolveTransactionCompletion(Exit status, quint32 runtime)
{
    Q_UNUSED(runtime);
    m_resolveTransaction = nullptr;
    _processExitStatus(status);
}

/*!
 * \brief Generates an error description if a request for information about a package has failed.
 * \param status Completion status of the request.
 */
void PackageInfoProvider::_processExitStatus(Exit status)
{
    switch (status) {
    case Exit::Success:
        return;
    case Exit::Failed:
        m_errorString = tr("Transaction failed");
        break;
    default:
        m_errorString = tr("Transaction faild unexpectidly");
        break;
    }
    m_hasError = true;
    emit hasErrorChanged();
}

/*!
 * \brief Forms information about the status of the found package.
 * \param info Package status.
 * \param packageID The identifier of the found package.
 * \param summary Package description.
 */
void PackageInfoProvider::_addPackageInfo(Info info, const QString &packageID, const QString &summary)
{
    Q_UNUSED(summary);

    if (packageID != m_packageId)
        return;

    switch (info) {
    case Info::Installed:
        m_status = tr("Installed");
        break;
    case Info::Available:
        m_status = tr("Available");
        break;
    default:
        m_status = tr("Unknown");
    }
    emit statusChanged();
}

/*!
 * \brief Forms general information about the package.
 * \param values Package information.
 */
void PackageInfoProvider::_storePackageDetails(const PackageInfo &values)
{
    m_description = values.description();
    m_license = values.license();
    m_size = values.size();
    m_summary = values.summary();
    m_url = values.url();
    emit detailDataChanged();
}

/*!
 * \brief Returns a string with the package size and units.
 */
QString PackageInfoProvider::size() const
{
    QString sizes = QStringLiteral("KMGTPE");
    auto unit = sizes.constBegin();
    double value = m_size / 1024.0;
    while (value > 1024.0 && unit != sizes.constEnd()) {
        ++unit;
        value /= 1024.0;
    }
    return QStringLiteral("%1 %2iB").arg(value, 0, 'f', 2).arg(*unit);
}
