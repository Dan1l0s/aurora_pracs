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

#ifndef PACKAGEINFOPROVIDER_H
#define PACKAGEINFOPROVIDER_H

#include <QObject>
#include <PackageKitAdaptor>

/*!
 * \brief Provides information about the package with the given identifier.
 */
class PackageInfoProvider : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString architecture READ architecture NOTIFY generalDataChanged)
    Q_PROPERTY(QString description READ description NOTIFY detailDataChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY hasErrorChanged)
    Q_PROPERTY(bool hasError READ hasError NOTIFY hasErrorChanged)
    Q_PROPERTY(QString license READ license NOTIFY detailDataChanged)
    Q_PROPERTY(QString name READ name NOTIFY generalDataChanged)
    Q_PROPERTY(QString packageId READ packageId WRITE setPackageId NOTIFY packageIdChanged)
    Q_PROPERTY(QString size READ size NOTIFY detailDataChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString summary READ summary NOTIFY detailDataChanged)
    Q_PROPERTY(QString version READ version NOTIFY generalDataChanged)
    Q_PROPERTY(QString url READ url NOTIFY detailDataChanged)

public:
    explicit PackageInfoProvider(QObject *parent = nullptr);

    QString architecture() const { return m_architecture; }
    QString description() const { return m_description; }
    QString errorString() const { return m_errorString; }
    bool hasError() const { return m_hasError; }
    QString license() const { return m_license; }
    QString name() const { return m_name; }
    QString packageId() const { return m_packageId; }
    void setPackageId(QString packageId);
    QString size() const;
    QString status() const { return m_status; }
    QString summary() const { return m_summary; }
    QString version() const { return m_version; }
    QString url() const { return m_url; }

signals:
    void detailDataChanged();
    void hasErrorChanged();
    void generalDataChanged();
    void packageIdChanged();
    void statusChanged();

private:
    void _addPackageInfo(PackageKitAdaptor::Info info, const QString &packageID, const QString &summary);
    void _processStoreTransactionCompletion(PackageKitAdaptor::Exit status, quint32 runtime);
    void _processResolveTransactionCompletion(PackageKitAdaptor::Exit status, quint32 runtime);
    void _processExitStatus(PackageKitAdaptor::Exit status);
    void _storePackageDetails(const PackageKitAdaptor::PackageInfo &values);

    QString m_architecture;
    QString m_description;
    QString m_errorString;
    bool m_hasError;
    QString m_license;
    QString m_name;
    QString m_packageId;
    PackageKitAdaptor::Transaction *m_searchTransaction;
    qulonglong m_size;
    QString m_status;
    QString m_summary;
    PackageKitAdaptor::Transaction *m_resolveTransaction;
    QString m_version;
    QString m_url;
};

#endif // PACKAGEINFOPROVIDER_H
