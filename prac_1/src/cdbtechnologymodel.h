/****************************************************************************
**
** Copyright (C) 2021 Open Mobile Platform LLC.
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
**   * Neither the name of copyright holder nor the names of its contributors
**     may be used to endorse or promote products derived from this software
**     without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
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

#ifndef CDBTECHNOLOGYMODEL_H
#define CDBTECHNOLOGYMODEL_H

#include <QAbstractListModel>
#include <QtDBus/QDBusVariant>

#include "cdbtypes.h"

class QTimer;
class CDBService;
class CDBTechnologyModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool powered READ powered NOTIFY poweredChanged)
    Q_PROPERTY(bool available READ available NOTIFY availableChanged)

public:
    enum ManagerRoles
    {
        ServiceRole = Qt::UserRole + 1,
    };

    explicit CDBTechnologyModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    QString name() const;
    bool powered() const;
    bool available() const;

    Q_INVOKABLE void init();

public slots:
    void setName(QString name);
    void requestScan();

signals:
    void nameChanged(QString name);
    void poweredChanged(bool powered);
    void availableChanged(bool available);

private slots:
    void onTechWiFiChanged(const QString &name, const QDBusVariant &val);
    void onServicesChanged(const ServiceList&, const DBusObjectList&);
    void scanWifi() const;

private:
    QString m_name;

    QMap<QString, CDBService *> m_cachedServices;
    bool m_powered{ false };
    bool m_available{ false };
    QTimer *m_timer;
};

#endif // CDBTECHNOLOGYMODEL_H
