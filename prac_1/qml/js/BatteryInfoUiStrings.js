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

.import ru.omp.SystemInfo.BatteryInfo 1.0 as BatteryInfo

/**
 * Returns the name of a charger type.
 *
 * @param {number} value the charger type ID
 * @returns {string}
 */
function chargerType(value) {
    return _chargerTypes[value] || qsTr("Unknown")
}
var _chargerTypes = []
_chargerTypes[BatteryInfo.WallCharger] = qsTr("Wall charger")
_chargerTypes[BatteryInfo.USBCharger] = qsTr("USB charger")
_chargerTypes[BatteryInfo.VariableCurrentCharger] = qsTr("Variable current charger")

/**
 * Returns the name of a battery charging state.
 *
 * @param {number} value the charging state ID.
 * @returns {string}
 */
function chargingState(value) {
    return _chargingStates[value] || qsTr("Unknown")
}
var _chargingStates = []
_chargingStates[BatteryInfo.Charging] = qsTr("Charging")
_chargingStates[BatteryInfo.IdleChargingState] = qsTr("Idle")
_chargingStates[BatteryInfo.Discharging] = qsTr("Discharging")

/**
 * Returns the name of a battery health status.
 *
 * @param {number} value the health status ID.
 * @returns {string}
 */
function health(value) {
    return _healths[value] || qsTr("Unknown")
}
var _healths = []
_healths[BatteryInfo.HealthBad] = qsTr("Bad")
_healths[BatteryInfo.HealthOk] = qsTr("Ok")

/**
 * Returns the name of a battery charge level.
 *
 * @param {number} value the charge level ID.
 * @returns {string}
 */
function levelStatus(value) {
    return _levelStatuses[value] || qsTr("Unknown")
}
var _levelStatuses = []
_levelStatuses[BatteryInfo.LevelEmpty] = qsTr("Empty")
_levelStatuses[BatteryInfo.LevelLow] = qsTr("Low")
_levelStatuses[BatteryInfo.LevelOk] = qsTr("Ok")
_levelStatuses[BatteryInfo.LevelFull] = qsTr("Full")
