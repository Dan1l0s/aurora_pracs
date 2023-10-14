/****************************************************************************
**
** Copyright (C) 2021 Open Mobile Platform LLC.
** Contact: https://community.omprussia.ru/open-source
**
** This file is part of the PackageKitAdaptor project.
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

#include "daemon.h"
#include "daemon_p.h"
#include "transaction_p.h"
#include "constants_p.h"

PKA_NAMESPACE_USE

DaemonPrivate::DaemonPrivate(QObject *parent)
    : QDBusAbstractInterface(Constants::packageKitService, Constants::packageKitPath,
                             Constants::packageKitIface, QDBusConnection::systemBus(), parent)
{
    QDBusServiceWatcher *watcher = new QDBusServiceWatcher(Constants::packageKitService,
                                                           QDBusConnection::systemBus(),
                                                           QDBusServiceWatcher::WatchForOwnerChange, this);

    connect(watcher, &QDBusServiceWatcher::serviceOwnerChanged,
            this, [this] (const QString &service, const QString &oldOwner, const QString &newOwner) {
        Q_UNUSED(service)
        Q_UNUSED(oldOwner)

        if (!newOwner.isEmpty()) {
            _makeInfoRequest();

            if (!m_running) {
                m_running = true;
                emit runningChanged(m_running);
            }
        } else if (m_running) {
            m_running = false;
            emit runningChanged(m_running);
        }
    });

    _makeInfoRequest();
}

bool DaemonPrivate::running() const
{
    return m_running;
}

DaemonInfo DaemonPrivate::info() const
{
    return m_info;
}

Transaction *DaemonPrivate::details(const QStringList &packageIDs)
{
    TransactionPrivate *transactionPrivate = _makeTransactionPrivate();
    Transaction *transaction = new Transaction(transactionPrivate);
    transactionPrivate->GetDetails(packageIDs);
    return transaction;
}

Transaction *DaemonPrivate::resolve(const QStringList &packageNames, Filters filters)
{
    TransactionPrivate *transactionPrivate = _makeTransactionPrivate();
    Transaction *transaction = new Transaction(transactionPrivate);
    transactionPrivate->Resolve(filters, packageNames);
    return transaction;
}

Transaction *DaemonPrivate::searchDetails(const QStringList &search, Filters filters)
{
    TransactionPrivate *transactionPrivate = _makeTransactionPrivate();
    Transaction *transaction = new Transaction(transactionPrivate);
    transactionPrivate->SearchDetails(filters, search);
    return transaction;
}

void DaemonPrivate::_updateInfo(const QVariantMap &info)
{
    if (!m_running) {
        m_running = true;
        emit runningChanged(m_running);
    }

    if (m_info != info) {
        m_info = info;
        emit infoChanged(m_info);
    }
}

TransactionPrivate *DaemonPrivate::_makeTransactionPrivate()
{
    QDBusPendingReply<QDBusObjectPath> reply = call(QStringLiteral("CreateTransaction"));
    TransactionPrivate *transactionPrivate = new TransactionPrivate(reply.value().path(), parent());
    Q_ASSERT(transactionPrivate->isValid());
    return transactionPrivate;
}

void DaemonPrivate::_makeInfoRequest()
{
    QDBusMessage message = QDBusMessage::createMethodCall(Constants::packageKitService,
                                                          Constants::packageKitPath,
                                                          Constants::dbusProperties,
                                                          QStringLiteral("GetAll"));
    message << Constants::packageKitService;
    QDBusConnection::systemBus().callWithCallback(message, this, SLOT(_updateInfo(QVariantMap)));
}

Daemon *Daemon::m_instance = nullptr;

Daemon *Daemon::instance()
{
    if (m_instance == nullptr)
        m_instance = new Daemon(qApp);
    return m_instance;
}

bool Daemon::running()
{
    return instance()->m_data->running();
}

DaemonInfo Daemon::info()
{
    return instance()->m_data->info();
}

Transaction *Daemon::details(const QString &packageID)
{
    return instance()->m_data->details(QStringList(packageID));
}

Transaction *Daemon::details(const QStringList &packageIDs)
{
    return instance()->m_data->details(packageIDs);
}

Transaction *Daemon::resolve(const QString &packageName, Filters filters)
{
    return instance()->m_data->resolve(QStringList(packageName), filters);
}

Transaction *Daemon::resolve(const QStringList &packageNames, Filters filters)
{
    return instance()->m_data->resolve(packageNames, filters);
}

Transaction *Daemon::searchDetails(const QString &search, Filters filters)
{
    return instance()->m_data->searchDetails(QStringList(search), filters);
}

Transaction *Daemon::searchDetails(const QStringList &search, Filters filters)
{
    return instance()->m_data->searchDetails(search, filters);
}

Daemon::Daemon(QObject *parent)
    : QObject(parent), m_data(new DaemonPrivate(this))
{
    qRegisterMetaType<Filter>("Filter");
    qRegisterMetaType<Filters>("Filters");
    qRegisterMetaType<Group>("Group");
    qRegisterMetaType<Groups>("Groups");
    qRegisterMetaType<Role>("Role");
    qRegisterMetaType<Roles>("Roles");
    qRegisterMetaType<Network>("Network");
    qRegisterMetaType<Info>("Info");
    qRegisterMetaType<Error>("Error");
    qRegisterMetaType<Exit>("Exit");
    qRegisterMetaType<DaemonInfo>("DaemonInfo");
    qRegisterMetaType<PackageInfo>("PackageInfo");

    connect(m_data.data(), &DaemonPrivate::runningChanged,
            this, &Daemon::runningChanged);
    connect(m_data.data(), &DaemonPrivate::infoChanged,
            this, &Daemon::infoChanged);
}
