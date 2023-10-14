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

#ifndef SIMCARDSIFACE_H
#define SIMCARDSIFACE_H

#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>

class SimCardsIfacePrivate;

class SimCardsIface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool available READ available CONSTANT)

    Q_PROPERTY(qint32 simCardsCount READ simCardsCount NOTIFY simCardsCountChanged)
    Q_PROPERTY(qint32 simCardIndex READ simCardIndex WRITE setSimCardIndex NOTIFY simCardIndexChanged)
    Q_PROPERTY(QString simCardName READ simCardName NOTIFY simCardNameChanged)
    Q_PROPERTY(QString operatorName READ operatorName NOTIFY operatorNameChanged)
    Q_PROPERTY(bool simCardEnabled READ simCardEnabled NOTIFY simCardEnabledChanged)
    Q_PROPERTY(bool preferredDataTransfer READ preferredDataTransfer NOTIFY preferredDataTransferChanged)
    Q_PROPERTY(bool preferredVoiceCall READ preferredVoiceCall NOTIFY preferredVoiceCallChanged)

public:
    explicit SimCardsIface(QObject *parent = nullptr);
    ~SimCardsIface() override = default;

    bool available() const;

    qint32 simCardsCount() const;
    qint32 simCardIndex() const;
    QString simCardName() const;
    QString operatorName() const;
    bool simCardEnabled() const;
    bool preferredDataTransfer() const;
    bool preferredVoiceCall() const;

signals:
    void simCardsCountChanged(qint32 simCardsCount);
    void simCardIndexChanged(qint32 simCardIndex);
    void simCardNameChanged(const QString &simCardName);
    void operatorNameChanged(const QString &operatorName);
    void simCardEnabledChanged(bool simCardEnabled);
    void preferredDataTransferChanged(bool preferredDataTransfer);
    void preferredVoiceCallChanged(bool preferredVoiceCall);

public slots:
    void setSimCardIndex(qint32 simCardIndex);

private:
    QSharedPointer<SimCardsIfacePrivate> m_data { nullptr };
};

#endif // SIMCARDSIFACE_H
