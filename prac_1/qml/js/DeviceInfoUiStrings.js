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

.import ru.omp.SystemInfo.DeviceInfo 1.0 as DeviceInfo

/**
 * Returns the names of the device lock types.
 *
 * @param {number} value the lock type mask.
 * @returns {string} comma separated lock type names.
 */
function locks(value) {
    return _deviceLockStrings.filter(function(lockString, lockId) {
        return value & lockId
    }).join(", ") || _deviceLockStrings[DeviceInfo.NoLock]
}
var _deviceLockStrings = []
_deviceLockStrings[DeviceInfo.NoLock] = qsTr("No lock")
_deviceLockStrings[DeviceInfo.PinLock] = qsTr("PIN lock")
_deviceLockStrings[DeviceInfo.TouchOrKeyboardLock] = qsTr("Touch or keyboard lock")

/**
 * Returns the name of the device thermal state.
 *
 * @param {number} value the thermal state ID.
 * @returns {string}
 */
function thermalState(value) {
    return _thermalStateStrings[value] || qsTr("Unknown")
}
var _thermalStateStrings = []
_thermalStateStrings[DeviceInfo.NormalThermal] = qsTr("Normal")
_thermalStateStrings[DeviceInfo.WarningThermal] = qsTr("Warning")
_thermalStateStrings[DeviceInfo.AlertThermal] = qsTr("Alert")
_thermalStateStrings[DeviceInfo.ErrorThermal] = qsTr("Error")
