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

#include "storageinfomodel.h"
#include <QStandardPaths>

StorageInfoModel::StorageInfoModel(QObject *parent)
    : QAbstractListModel(parent)
{
    refresh();
}

int StorageInfoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_items.count();
}

QHash<int, QByteArray> StorageInfoModel::roleNames() const
{
    return {
        { BlockSizeRole,      QByteArrayLiteral("blockSize") },
        { BytesAvailableRole, QByteArrayLiteral("bytesAvailable") },
        { BytesFreeRole,      QByteArrayLiteral("bytesFree") },
        { BytesTotalRole,     QByteArrayLiteral("bytesTotal") },
        { DeviceRole,         QByteArrayLiteral("device") },
        { DisplayNameRole,    QByteArrayLiteral("displayName") },
        { FileSystemTypeRole, QByteArrayLiteral("fileSystemType") },
        { IsReadOnlyRole,     QByteArrayLiteral("isReadOnly") },
        { IsReadyRole,        QByteArrayLiteral("isReady") },
        { IsRootRole,         QByteArrayLiteral("isRoot") },
        { NameRole,           QByteArrayLiteral("name") },
        { RootPathRole,       QByteArrayLiteral("rootPath") },
    };
}

QVariant StorageInfoModel::data(const QModelIndex &index, int role) const
{
    auto iItem = index.row();
    if (iItem < 0 || iItem >= m_items.count())
        return QVariant();
    auto item = m_items[iItem];
    switch (role) {
    case BlockSizeRole:
        return item.blockSize();
    case BytesAvailableRole:
        return item.bytesAvailable();
    case BytesFreeRole:
        return item.bytesFree();
    case BytesTotalRole:
        return item.bytesTotal();
    case DeviceRole:
        return item.device();
    case DisplayNameRole:
        return item.displayName();
    case FileSystemTypeRole:
        return item.fileSystemType();
    case IsReadOnlyRole:
        return item.isReadOnly();
    case IsReadyRole:
        return item.isReady();
    case IsRootRole:
        return item.isRoot();
    case NameRole:
        return item.name();
    case RootPathRole:
        return item.rootPath();
    default:
        return QVariant();
    }
}

void StorageInfoModel::refresh()
{
    beginResetModel();
    m_items.clear();
    for (auto &mountedVolume : QStorageInfo::mountedVolumes()) {
        if (mountedVolume.isValid())
            m_items.append(mountedVolume);
    }
    endResetModel();
}
