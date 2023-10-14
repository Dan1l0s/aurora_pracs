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

#ifndef PACKAGEKITPROVIDER_H
#define PACKAGEKITPROVIDER_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <PackageKitAdaptor>

/*!
 * \brief Provides a list of packages available on the device.
 */
class PackageSearcher : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool daemonRunning READ daemonRunning NOTIFY daemonRunningChanged)
    Q_PROPERTY(QVariantList packageList READ packageList NOTIFY packageListChanged)
    Q_PROPERTY(bool searchFailed READ searchFailed NOTIFY searchFailedChanged)
    Q_PROPERTY(bool searchSucceeded READ searchSucceeded NOTIFY searchSucceededChanged)
    Q_PROPERTY(bool searchRunning READ searchRunning NOTIFY searchRunningChanged)
    Q_PROPERTY(QString searchString READ searchString NOTIFY searchStringChanged)

public:
    explicit PackageSearcher(QObject *parent = nullptr);

    Q_INVOKABLE bool daemonRunning() const;
    Q_INVOKABLE QVariantList packageList() const;
    Q_INVOKABLE bool searchFailed() const;
    Q_INVOKABLE bool searchSucceeded() const;
    Q_INVOKABLE void searchPackageByName(const QString &name);
    Q_INVOKABLE bool searchRunning() const;
    Q_INVOKABLE QString searchString() const;

Q_SIGNALS:
    void daemonRunningChanged();
    void packageListChanged();
    void searchFailedChanged();
    void searchSucceededChanged();
    void searchRunningChanged();
    void searchStringChanged();

private:
    void _storeDaemonRunningState(bool running);
    void _processSearchResults(PackageKitAdaptor::Exit status, uint runtime);
    void _addPackageInfo(PackageKitAdaptor::Info info, const QString &packageID, const QString &summary);

    bool m_daemonRunning;
    QVariantList m_packageList;
    QString m_searchString;
    PackageKitAdaptor::Transaction *m_searchTransaction;
};

#endif // PACKAGEKITPROVIDER_H
