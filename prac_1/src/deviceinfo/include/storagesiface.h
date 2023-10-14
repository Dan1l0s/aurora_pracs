/*******************************************************************************
**
** Copyright (C) 2022 Open Mobile Platform LLC.
** Contact: https://community.omprussia.ru/open-source
**
** This file is part of the Aurora OS Application Template project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

#ifndef STORAGESIFACE_H
#define STORAGESIFACE_H

#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>

class StoragesIfacePrivate;

class StoragesIface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool available READ available CONSTANT)

    Q_PROPERTY(bool extStorageMounted READ extStorageMounted NOTIFY extStorageMountedChanged)
    Q_PROPERTY(QString extStorageDeviceLabel READ extStorageDeviceLabel NOTIFY extStorageDeviceLabelChanged)
    Q_PROPERTY(quint32 extStoragePartitionsCount READ extStoragePartitionsCount NOTIFY extStoragePartitionsCountChanged)
    Q_PROPERTY(quint64 extStorageBytesTotal READ extStorageBytesTotal NOTIFY extStorageBytesTotalChanged)
    Q_PROPERTY(quint64 extStorageBytesUsed READ extStorageBytesUsed NOTIFY extStorageBytesUsedChanged)
    Q_PROPERTY(quint64 extStorageBytesFree READ extStorageBytesFree NOTIFY extStorageBytesFreeChanged)

    Q_PROPERTY(QString intStorageDeviceLabel READ intStorageDeviceLabel NOTIFY intStorageDeviceLabelChanged)
    Q_PROPERTY(QString intStorageFileSystemType READ intStorageFileSystemType NOTIFY intStorageFileSystemTypeChanged)
    Q_PROPERTY(quint64 intStorageBytesTotal READ intStorageBytesTotal NOTIFY intStorageBytesTotalChanged)
    Q_PROPERTY(quint64 intStorageBytesUsed READ intStorageBytesUsed NOTIFY intStorageBytesUsedChanged)
    Q_PROPERTY(quint64 intStorageBytesFree READ intStorageBytesFree NOTIFY intStorageBytesFreeChanged)

    Q_PROPERTY(QString intUsrPartsDeviceLabel READ intUsrPartsDeviceLabel NOTIFY intUsrPartsDeviceLabelChanged)
    Q_PROPERTY(QString intUsrPartsFileSystemType READ intUsrPartsFileSystemType NOTIFY intUsrPartsFileSystemTypeChanged)
    Q_PROPERTY(quint64 intUsrPartsBytesTotal READ intUsrPartsBytesTotal NOTIFY intUsrPartsBytesTotalChanged)
    Q_PROPERTY(quint64 intUsrPartsBytesUsed READ intUsrPartsBytesUsed NOTIFY intUsrPartsBytesUsedChanged)
    Q_PROPERTY(quint64 intUsrPartsBytesFree READ intUsrPartsBytesFree NOTIFY intUsrPartsBytesFreeChanged)

public:
    explicit StoragesIface(QObject *parent = nullptr);
    ~StoragesIface() override = default;

    bool available() const;

    bool extStorageMounted() const;
    QString extStorageDeviceLabel() const;
    quint32 extStoragePartitionsCount() const;
    quint64 extStorageBytesTotal() const;
    quint64 extStorageBytesUsed() const;
    quint64 extStorageBytesFree() const;

    QString intStorageDeviceLabel() const;
    QString intStorageFileSystemType() const;
    quint64 intStorageBytesTotal() const;
    quint64 intStorageBytesUsed() const;
    quint64 intStorageBytesFree() const;

    QString intUsrPartsDeviceLabel() const;
    QString intUsrPartsFileSystemType() const;
    quint64 intUsrPartsBytesTotal() const;
    quint64 intUsrPartsBytesUsed() const;
    quint64 intUsrPartsBytesFree() const;

signals:
    void extStorageMountedChanged(bool mounted);
    void extStorageDeviceLabelChanged(const QString &deviceLabel);
    void extStoragePartitionsCountChanged(quint32 partitionsCount);
    void extStorageBytesTotalChanged(quint64 bytesTotal);
    void extStorageBytesUsedChanged(quint64 bytesUsed);
    void extStorageBytesFreeChanged(quint64 bytesFree);

    void intStorageDeviceLabelChanged(const QString &deviceLabel);
    void intStorageFileSystemTypeChanged(const QString &fileSystemType);
    void intStorageBytesTotalChanged(quint64 bytesTotal);
    void intStorageBytesUsedChanged(quint64 bytesUsed);
    void intStorageBytesFreeChanged(quint64 bytesFree);

    void intUsrPartsDeviceLabelChanged(const QString &deviceLabel);
    void intUsrPartsFileSystemTypeChanged(const QString &fileSystemType);
    void intUsrPartsBytesTotalChanged(quint64 bytesTotal);
    void intUsrPartsBytesUsedChanged(quint64 bytesUsed);
    void intUsrPartsBytesFreeChanged(quint64 bytesFree);

private:
    QSharedPointer<StoragesIfacePrivate> m_data { nullptr };
};

#endif // STORAGESIFACE_H
