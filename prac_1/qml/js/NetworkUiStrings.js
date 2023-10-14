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

.import ru.omp.SystemInfo 1.0 as SystemInfo

/**
 * Returns the encryption mode of a Wi-Fi network.
 *
 * @param {string} value the encryption mode code.
 * @returns {string}
 */
function encryptionMode(value) {
    return _encryptionModes[value] || qsTr("Unknown")
}
var _encryptionModes = {}
_encryptionModes["none"] = qsTr("None")
_encryptionModes["mixed"] = qsTr("Mixed")
_encryptionModes["aes"] = "AES"
_encryptionModes["tkip"] = "TKIP"
_encryptionModes["wep"] = "WEP"

/**
 * Returns the connection error a Wi-Fi network.
 *
 * @param {string} value the error code.
 * @returns {string}
 */
function error(value) {
    return _errors[value] || qsTr("Unknown")
}
var _errors = {}
_errors["out-of-range"] = qsTr("Out of range")
_errors["pin-missing"] = qsTr("PIN missing")
_errors["dhcp-failed"] = qsTr("DHCP failed")
_errors["connect-failed"] = qsTr("Connect failed")
_errors["login-failed"] = qsTr("Login failed")
_errors["auth-failed"] = qsTr("Auth failed")
_errors["invalid-key"] = qsTr("Invalid key")

/**
 * Returns the frequency of a Wi-Fi network.
 *
 * @param {number} value The frequency of a Wi-Fi network in MHz.
 * @returns {string}
 */
function frequency(value) {
    return qsTr("%L1 GHz").arg(value / 1e3)
}

/**
 * Returns the IPv4 properties of a network service.
 *
 * @param {number} value The IPv4 properties.
 * @returns {string}
 */
function ipv4(value) {
    if (!value)
        return qsTr("Undefined")
    var text = []
    if (value.Address)
        text.push(qsTr("Address: %1").arg(value.Address))
    if (value.Netmask)
        text.push(qsTr("Netmask: %1").arg(value.Netmask))
    if (value.Gateway)
        text.push(qsTr("Gateway: %1").arg(value.Gateway))
    text.push(qsTr("Method: %1").arg(_ipMethods[value.Method] || qsTr("Unknown")))
    return text.join("\n")
}
var _ipMethods = {}
_ipMethods["dhcp"] = "DHCP"
_ipMethods["manual"] = qsTr("Manual")
_ipMethods["auto"] = qsTr("Auto")
_ipMethods["off"] = qsTr("Off")
_ipMethods["fixed"] = qsTr("Fixed")

/**
 * Returns the IPv6 properties of a network service.
 *
 * @param {number} value The IPv6 properties.
 * @returns {string}
 */
function ipv6(value) {
    if (!value)
        return qsTr("Undefined")
    var text = []
    if (value.Address)
        text.push(qsTr("Address: %1").arg(value.Address))
    if (value.PrefixLength)
        text.push(qsTr("Prefix length: %1").arg(value.PrefixLength))
    if (value.Gateway)
        text.push(qsTr("Gateway: %1").arg(value.Gateway))
    if (value.Method === "auto")
        text.push(qsTr("Privacy: %1").arg(_ipPrivacies[value.Privacy] || qsTr("Unknown")))
    text.push(qsTr("Method: %1").arg(_ipMethods[value.Method] || qsTr("Unknown")))
    return text.join("\n")
}
var _ipPrivacies = {}
_ipPrivacies["disabled"] = qsTr("Disabled")
_ipPrivacies["enabled"] = qsTr("Enabled")
_ipPrivacies["prefered"] = qsTr("Prefered")

/**
 * Returns the rate of a connection.
 *
 * @param {number} value The rate in b/s
 * @returns {string}
 */
function rate(value) {
    return qsTr("%L1 Mb/s").arg(value / 1e6)
}

/**
 * Returns the security type of a Wi-Fi network.
 *
 * @param {string} value the security type.
 * @returns {string}
 */
function security(value) {
    return _securities[value] || qsTr("Unknown")
}
var _securities = {}
_securities["none"] = qsTr("None")
_securities["ieee8021x"] = "IEEE8021x"
_securities["psk"] = "PSK"
_securities["wep"] = "WEP"
_securities["wps"] = "WPS"

/**
 * Returns the security type of a Wi-Fi network.
 *
 * @param {numer} value the security type ID.
 * @returns {string}
 */
function securityType(value) {
    return _securityTypes[value] || qsTr("Unknown")
}
var _securityTypes = []
_securityTypes[SystemInfo.CDBService.SecurityNone] = qsTr("None")
_securityTypes[SystemInfo.CDBService.SecurityWEP] = "WEP"
_securityTypes[SystemInfo.CDBService.SecurityPSK] = "PSK"
_securityTypes[SystemInfo.CDBService.SecurityIEEE802] = "IEEE802"

/**
 * Returns the state of the connection to the Internet.
 *
 * @param {string} value the connection state.
 * @returns {string}
 */
function state(value) {
    return _states[value] || qsTr("Unknown")
}
var _states = {}
_states["idle"] = qsTr("Idle")
_states["failure"] = qsTr("Failure")
_states["association"] = qsTr("Association")
_states["configuration"] = qsTr("Configuration")
_states["ready"] = qsTr("Ready")
_states["disconnect"] = qsTr("Disconnect")
_states["online"] = qsTr("Online")

/**
 * Returns the type of a network service.
 *
 * @param {string} value the service type
 * @returns {string}
 */
function type(value) {
    return _types[value] || qsTr("Unknown")
}
var _types = {}
_types["cellular"] = qsTr("Cellular")
_types["ethernet"] = qsTr("Ethernet")
_types["wifi"] = qsTr("Wi-Fi")
