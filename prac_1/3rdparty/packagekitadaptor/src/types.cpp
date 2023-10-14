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

#include "types.h"

PKA_NAMESPACE_USE

DaemonInfo::DaemonInfo()
    : QVariantMap()
{
}

DaemonInfo::DaemonInfo(const QVariantMap &details)
    : QVariantMap(details)
{
}

QString DaemonInfo::backendAuthor() const
{
    return value(QStringLiteral("BackendAuthor")).value<QString>();
}

QString DaemonInfo::backendDescription() const
{
    return value(QStringLiteral("BackendDescription")).value<QString>();
}

QString DaemonInfo::backendName() const
{
    return value(QStringLiteral("BackendName")).value<QString>();
}

QString DaemonInfo::distroId() const
{
    return value(QStringLiteral("DistroId")).value<QString>();
}

QStringList DaemonInfo::mimeTypes() const
{
    return value(QStringLiteral("MimeTypes")).value<QStringList>();
}

QVersionNumber DaemonInfo::version() const
{
    return QVersionNumber(value(QStringLiteral("VersionMajor")).value<qint32>(),
                          value(QStringLiteral("VersionMinor")).value<qint32>(),
                          value(QStringLiteral("VersionMicro")).value<qint32>());
}

Network DaemonInfo::network() const
{
    return static_cast<Network>(value(QStringLiteral("NetworkState")).value<quint32>());
}

Filters DaemonInfo::filters() const
{
    return static_cast<Filters>(value(QStringLiteral("Filters")).value<quint32>());
}

Groups DaemonInfo::groups() const
{
    return static_cast<Groups>(value(QStringLiteral("Groups")).value<quint64>());
}

Roles DaemonInfo::roles() const
{
    return static_cast<Roles>(value(QStringLiteral("Roles")).value<quint64>());
}

bool DaemonInfo::locked() const
{
    return value(QStringLiteral("Locked")).value<bool>();
}

PackageInfo::PackageInfo()
    : QVariantMap()
{
}

PackageInfo::PackageInfo(const QVariantMap &details)
    : QVariantMap(details)
{
}

QString PackageInfo::packageId() const
{
    return value(QStringLiteral("package-id")).value<QString>();
}

QString PackageInfo::description() const
{
    return value(QStringLiteral("description")).value<QString>();
}

QString PackageInfo::summary() const
{
    return value(QStringLiteral("summary")).value<QString>();
}

QString PackageInfo::license() const
{
    return value(QStringLiteral("license")).value<QString>();
}

QString PackageInfo::url() const
{
    return value(QStringLiteral("url")).value<QString>();
}

quint64 PackageInfo::size() const
{
    return value(QStringLiteral("size")).value<quint64>();
}

Group PackageInfo::group() const
{
    return static_cast<Group>(value(QStringLiteral("group")).value<quint32>());
}
