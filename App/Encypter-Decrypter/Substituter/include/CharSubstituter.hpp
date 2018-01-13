///////////////////////////////////////////////////////////////////////////////
/// @file CharSubstituter.h
/// @brief Character Substituter Class of MasterMind.
///
/// Related Files:
/// @li CharSubstituter.cpp - Implementation
///
/// Copyright (C) 2009 Lissy Lau
///
/// MasterMind is free software: you can redistribute it and / or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.
///////////////////////////////////////////////////////////////////////////////

#ifndef _CHAR_SUBSTITUTER_H__
#define _CHAR_SUBSTITUTER_H__

#include <iostream>
#include <string>
#include "CharSubstituteConfigure.hpp"

class CharSubstituter
{
public:

    CharSubstituter(const CharSubstituteConfigure &configData_);
    virtual ~CharSubstituter();

    virtual std::string name() const;

    virtual void process(std::istream &in_, std::ostream &out_);

private: 

    CharSubstituter();

    static const std::string m_Name;  // Name of the component

    const CharSubstituteConfigure & m_ConfigData;
};

inline std::string CharSubstituter::name() const
{
    return m_Name;
}

#endif // _CHAR_SUBSTITUTER_H__

