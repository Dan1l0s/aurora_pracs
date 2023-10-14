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

#ifndef CDBUTILS_H
#define CDBUTILS_H

#include <QString>
#include <QFile>
#include <QTextStream>

#define DECLARE_PROPERTY(Type, name) \
    Q_PROPERTY(Type name READ name NOTIFY name##Changed) \
    public: Type name() const; \
    Q_SIGNAL void name##Changed(Type); \
    private:

#define CHECK_PROPERTY(DBusName, propName, testName) \
    if (testName == QStringLiteral(DBusName)) { \
        emit propName##Changed(propName()); \
    }

namespace CDBUtils
{

[[maybe_unused]] static QString defaultRouteName()
{
    // NOTE: https://github.com/sailfishos/libconnman-qt/blob/master/libconnman-qt/networkmanager.cpp#L754
    QString defaultNetDev;
    QFile routeFile("/proc/net/route");
    if (routeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&routeFile);
        QString line = in.readLine();
        while (!line.isNull()) {
            QStringList lineList = line.split('\t');
            if (lineList.size() >= 11) {
                if ((lineList.at(1) == "00000000" && lineList.at(3) == "0003") ||
                   (lineList.at(0).startsWith("ppp") && lineList.at(3) == "0001")) {
                    defaultNetDev = lineList.at(0);
                    break;
                }
            }
            line = in.readLine();
        }
        routeFile.close();
    }

    if (defaultNetDev.isNull()) {
         QFile ipv6routeFile("/proc/net/ipv6_route");
         if (ipv6routeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
             QTextStream ipv6in(&ipv6routeFile);
             QString ipv6line = ipv6in.readLine();
             while (!ipv6line.isNull()) {
                 QStringList ipv6lineList = ipv6line.split(QRegExp("\\s+"));
                 if (ipv6lineList.size() >= 10) {
                     if (ipv6lineList.at(0) == "00000000000000000000000000000000" &&
                        (ipv6lineList.at(8).endsWith("3") || (ipv6lineList.at(8).endsWith("1")))) {
                         defaultNetDev = ipv6lineList.at(9).trimmed();
                         break;
                     }
                     ipv6line = ipv6in.readLine();
                 }
             }
             ipv6routeFile.close();
         }
    }

    return defaultNetDev;
}

[[maybe_unused]] static QString techPathToName(const QString &techName)
{
    auto defaultServiceTechNameSplit = techName.split(QStringLiteral("/"));
    if (defaultServiceTechNameSplit.isEmpty())
        return {  };

    return defaultServiceTechNameSplit.last().split(QStringLiteral("_")).first();
}
}

#endif // CDBUTILS_H
