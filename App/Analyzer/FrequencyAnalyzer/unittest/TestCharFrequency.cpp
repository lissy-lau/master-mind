///////////////////////////////////////////////////////////////////////////////
/// @file TestCharFrequency.cpp
/// @brief Unit Test of CharFrequency
///
/// Related Files:
/// @li CharFrequency.hpp - Character Frequency Class Declaration
/// @li CharFrequency.cpp - Character Frequency Class Implementation
///
/// Copyright (C) 2011 Lissy Lau <Lissy.Lau@gmail.com>
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

#include <UnitTest++.h>
#include "CharFrequency.hpp"

SUITE(CharFrequency)
{
    TEST(ConstructorAndDestructor)
    {
        CharFrequency charFreq1;
        CharFrequency *charFreq2 = new CharFrequency();
        delete charFreq2;
        charFreq2 = NULL;
    }
    TEST(getAlnum_Initial)
    {
    }
}

