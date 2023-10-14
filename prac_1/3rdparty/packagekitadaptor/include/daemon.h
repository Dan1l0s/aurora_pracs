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

#ifndef PKA_DAEMON_H
#define PKA_DAEMON_H

#include "types.h"
#include "transaction.h"

PKA_NAMESPACE_BEGIN

class DaemonPrivate;
class PKA_LIBRARY Daemon final : public QObject
{
    Q_OBJECT

public:
    static Daemon *instance();

    static bool running();
    static DaemonInfo info();

    static Transaction *details(const QString &packageID);
    static Transaction *details(const QStringList &packageIDs);
    static Transaction *resolve(const QString &packageName, Filters filters = Filter::None);
    static Transaction *resolve(const QStringList &packageNames, Filters filters = Filter::None);
    static Transaction *searchDetails(const QString &search, Filters filters = Filter::None);
    static Transaction *searchDetails(const QStringList &search, Filters filters = Filter::None);

signals:
    void runningChanged(bool running);
    void infoChanged(const DaemonInfo &info);

private:
    explicit Daemon(QObject *parent = nullptr);

private:
    static Daemon *m_instance;
    QSharedPointer<DaemonPrivate> m_data { nullptr };
};

PKA_NAMESPACE_END

#endif // PKA_DAEMON_H
