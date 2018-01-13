///////////////////////////////////////////////////////////////////////////////
/// @file CharSubstituter.cpp
/// @brief Character Substituter Class of MasterMind.
///
/// Related Files:
/// @li CharSubstituter.h - Declaration
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

#include "CharSubstituter.hpp"

const std::string CharSubstituter::m_Name = "Character Substituter";

CharSubstituter::~CharSubstituter()
{
}

CharSubstituter::CharSubstituter(const CharSubstituteConfigure &configData_) :
m_ConfigData(configData_)
{
}

void CharSubstituter::process(std::istream &in_, std::ostream &out_)
{
    if (m_ConfigData.isValid())
    {
        in_.unsetf(std::ios::skipws);
        out_.unsetf(std::ios::skipws);

        unsigned char tmpChar;

        while (EOF != in_.peek())
        {
            in_ >> tmpChar;
            out_ << m_ConfigData.getChar(tmpChar);
        }
    }
    else
    {
        std::cout << "[" << __PRETTY_FUNCTION__ << "] Invalid substitution configuration!" << std::endl;
    }
}

