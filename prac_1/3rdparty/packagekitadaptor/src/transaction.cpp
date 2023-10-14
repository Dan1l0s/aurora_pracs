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

#include "transaction.h"
#include "transaction_p.h"
#include "constants_p.h"

PKA_NAMESPACE_USE

TransactionPrivate::TransactionPrivate(const QString &path, QObject *parent)
    : QDBusAbstractInterface(Constants::packageKitService, path,
                             Constants::packageKitTransactionIface,
                             QDBusConnection::systemBus(), parent)
{
}

void TransactionPrivate::GetDetails(const QStringList &packageIds)
{
    asyncCall("GetDetails", packageIds);
}

void TransactionPrivate::Resolve(quint64 filter, const QStringList &search)
{
    asyncCall("Resolve", filter, search);
}

void TransactionPrivate::SearchDetails(quint64 filter, const QStringList &search)
{
    asyncCall("SearchDetails", filter, search);
}

QString Transaction::packageName(const QString &packageID)
{
    return packageID.left(packageID.indexOf(QLatin1Char(';')));
}

QString Transaction::packageData(const QString &packageID)
{
    qint32 start = packageID.indexOf(QLatin1Char(';'));
    if (start == -1)
        return {  };

    start = packageID.indexOf(QLatin1Char(';'), ++start);
    if (start == -1)
        return {  };

    start = packageID.indexOf(QLatin1Char(';'), ++start);
    if (start == -1)
        return {  };

    return packageID.mid(++start);
}

QString Transaction::packageArch(const QString &packageID)
{
    qint32 start = packageID.indexOf(QLatin1Char(';'));
    if (start == -1)
        return {  };

    start = packageID.indexOf(QLatin1Char(';'), ++start);
    if (start == -1)
        return {  };

    qint32 end = packageID.indexOf(QLatin1Char(';'), ++start);
    return end == -1 ? packageID.mid(start) : packageID.mid(start, end - start);
}

QString Transaction::packageVersion(const QString &packageID)
{
    qint32 start = packageID.indexOf(QLatin1Char(';'));
    if (start == -1)
        return {  };

    qint32 end = packageID.indexOf(QLatin1Char(';'), ++start);
    return end == -1 ? packageID.mid(start) : packageID.mid(start, end - start);
}

Transaction::Transaction(TransactionPrivate *data)
    : m_data(data)
{
    if (!m_data.isNull()) {
        m_data->setParent(this);

        connect(m_data.data(), &TransactionPrivate::Package, [this](quint32 info, const QString &packageId, const QString &summary) {
            emit package(static_cast<Info>(info), packageId, summary);
        });
        connect(m_data.data(), &TransactionPrivate::Details,
                this, &Transaction::info);
        connect(m_data.data(), &TransactionPrivate::Finished, [this](quint32 exit, quint32 runtime) {
            emit finished(static_cast<Exit>(exit), runtime);
            this->deleteLater();
        });
        connect(m_data.data(), &TransactionPrivate::ErrorCode, [this](quint32 code, const QString &details) {
            emit errorCode(static_cast<Error>(code), details);
        });
    }
}
