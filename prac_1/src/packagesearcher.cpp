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

#include "packagesearcher.h"

PKA_NAMESPACE_USE

/*!
 * \brief Constructor of the PackageSearcher class.
 * \param parent Ancestor object.
 */
PackageSearcher::PackageSearcher(QObject *parent)
    : QObject(parent),
      m_daemonRunning(false),
      m_packageList(QVariantList()),
      m_searchString(QString()),
      m_searchTransaction(nullptr)
{
    m_daemonRunning = Daemon::running();

    connect(Daemon::instance(), &Daemon::runningChanged,
            this, &PackageSearcher::_storeDaemonRunningState);
    connect(this, &PackageSearcher::searchRunningChanged,
            this, &PackageSearcher::searchSucceededChanged);
    connect(this, &PackageSearcher::searchRunningChanged,
            this, &PackageSearcher::searchFailedChanged);
    connect(this, &PackageSearcher::searchStringChanged,
            this, &PackageSearcher::searchSucceededChanged);
    connect(this, &PackageSearcher::searchStringChanged,
            this, &PackageSearcher::searchFailedChanged);
}

/*!
 * \brief Sets the state of the daemon.
 */
void PackageSearcher::_storeDaemonRunningState(bool running)
{
    if (m_daemonRunning != running) {
        m_daemonRunning = running;
        emit daemonRunningChanged();
    }
}

/*!
 * \brief Returns the state of the daemon.
 */
bool PackageSearcher::daemonRunning() const
{
    return m_daemonRunning;
}

/*!
 * \brief Searches for an available package with the specified name.
 * \param name Package name.
 */
void PackageSearcher::searchPackageByName(const QString &name)
{
    // Search transaction already exists
    if (m_searchTransaction != nullptr)
        return;

    m_searchString = name.trimmed();
    emit searchStringChanged();

    m_packageList.clear();
    emit packageListChanged();

    if (m_searchString.isEmpty())
        return;

    m_searchTransaction = Daemon::searchDetails(name);
    connect(m_searchTransaction, &Transaction::finished,
            this, &PackageSearcher::_processSearchResults);
    connect(m_searchTransaction, &Transaction::package,
            this, &PackageSearcher::_addPackageInfo);

    emit searchRunningChanged();
}

/*!
 * \brief Sends a signal to update the search completion status and list of packages.
 * \param status Completion status of the request.
 * \param runtime Request runtime.
 */
void PackageSearcher::_processSearchResults(Exit status, uint runtime)
{
    Q_UNUSED(status);
    Q_UNUSED(runtime);
    m_searchTransaction = nullptr;
    emit searchRunningChanged();
    emit packageListChanged();
}

/*!
 * \brief Returns a list of information about available packages.
 */
QVariantList PackageSearcher::packageList() const
{
    return m_packageList;
}

/*!
 * \brief Adds information about the found package to the information list.
 * \param info Package status.
 * \param packageID The identifier of the found package.
 * \param summary Package description.
 */
void PackageSearcher::_addPackageInfo(Info info, const QString &packageID, const QString &summary)
{
    QVariantMap packageInfo;
    switch (info) {
    case Info::Installed:
        packageInfo[QStringLiteral("status")] = tr("Installed");
        break;
    case Info::Available:
        packageInfo[QStringLiteral("status")] = tr("Available");
        break;
    default:
        packageInfo[QStringLiteral("status")] = tr("Unknown");
    }
    packageInfo[QStringLiteral("packageId")] = QString(packageID);
    packageInfo[QStringLiteral("name")] = Transaction::packageName(packageID);
    packageInfo[QStringLiteral("version")] = Transaction::packageVersion(packageID);
    packageInfo[QStringLiteral("architecture")] = Transaction::packageArch(packageID);
    packageInfo[QStringLiteral("summary")] = QString(summary);
    m_packageList.append(packageInfo);
}

/*!
 * \brief Returns the state of the package search.
 * \return \c true if a package is found, \c false otherwise.
 */
bool PackageSearcher::searchRunning() const
{
    return m_searchTransaction != nullptr;
}

/*!
 * \brief Returns the name of the required package.
 */
QString PackageSearcher::searchString() const
{
    return m_searchString;
}

/*!
 * \brief Returns \c true if the required package was not found, otherwise \c false.
 */
bool PackageSearcher::searchFailed() const
{
    return !searchRunning() && !m_searchString.isEmpty() && m_packageList.empty();
}

/*!
 * \brief Returns \c true if the required package is found, otherwise \c false.
 */
bool PackageSearcher::searchSucceeded() const
{
    return !searchRunning() && !m_searchString.isEmpty() && !m_packageList.empty();
}
