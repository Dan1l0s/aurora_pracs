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

#ifndef PKA_BITFIELDS_H
#define PKA_BITFIELDS_H

#include "global.h"

PKA_NAMESPACE_BEGIN

template<typename Enum>
class PKA_LIBRARY Bitfields final {
    static_assert((std::is_enum<Enum>::value), "Flag is only usable on enumeration types.");
public:
    inline Bitfields() : m_value(0ull) {  }
    inline Bitfields(quint64 value) : m_value(value) {  }

    inline Bitfields &operator&=(Enum mask) { m_value &= (1ull << static_cast<quint64>(mask)); return *this; }
    inline Bitfields &operator&=(Bitfields mask) { m_value &= mask.m_value; return *this; }
    inline Bitfields &operator|=(Enum mask) { m_value |= (1ull << static_cast<quint64>(mask)); return *this; }
    inline Bitfields &operator|=(Bitfields mask) { m_value |= mask.m_value; return *this; }

    inline Bitfields operator&(Enum mask) const { return Bitfields(m_value & (1ull << static_cast<quint64>(mask))); }
    inline Bitfields operator&(Bitfields mask) const { Bitfields(m_value & mask.m_value); }
    inline Bitfields operator|(Enum mask) const { return Bitfields(m_value | (1ull << static_cast<quint64>(mask))); }
    inline Bitfields operator|(Bitfields mask) const { return Bitfields(m_value | mask.m_value); }
    inline Bitfields operator~() const { return Bitfields(~m_value); }

    inline bool operator==(const Bitfields &other) { return m_value == other.m_value; }
    inline bool operator!() const { return !m_value; }
    inline operator quint64() const { return m_value; }

    inline bool testFlag(Enum flag) const { return static_cast<bool>(m_value & (1ull << static_cast<quint64>(flag))); }
    inline Bitfields &setFlag(Enum flag, bool on = true) { return on ? (*this |= flag) : (*this &= ~Bitfields(1ull << static_cast<quint64>(flag))); }

private:
    quint64 m_value { 0ull };
};

#define DECLARE_FLAGS(FlagsName, EnumName) using FlagsName = QFlags<EnumName>;
#define DECLARE_BITFIELDS(BitfieldsName, EnumName) using BitfieldsName = Bitfields<EnumName>;

PKA_NAMESPACE_END

#endif // PKA_BITFIELDS_H
