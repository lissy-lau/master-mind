///////////////////////////////////////////////////////////////////////////////
/// @file CharFrequency.hpp
/// @brief Character Frequency Class of MasterMind.
///
/// Related Files:
/// @li CharFrequency.cpp - Implementation
///
/// Copyright (C) 2009 Lissy Lau <Lissy.Lau@gmail.com>
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

#ifndef _CHAR_FREQUENCY_HPP__
#define _CHAR_FREQUENCY_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <locale>

//////////////////////////////////////////////////////////////////////////////
/// @class CharFrequency
/// @brief Character frequency class
//////////////////////////////////////////////////////////////////////////////
class CharFrequency
{
public:

    // ---- LIFECYCLE ----

    ///////////////////////////////////////////////////////////////////////////
    /// @fn CharFrequency
    /// @brief Constructor
    ///////////////////////////////////////////////////////////////////////////
    CharFrequency();

    ///////////////////////////////////////////////////////////////////////////
    /// @fn ~CharFrequency
    /// @brief Destructor
    ///////////////////////////////////////////////////////////////////////////
    virtual ~CharFrequency();

    // ---- OPERATORS ----

    // ---- OPERATIONS ----

    ///////////////////////////////////////////////////////////////////////////
    /// @fn process
    /// @brief Character frequency statistics on the input stream
    ///
    /// @param[in] in_             - Input stream
    /// @param[in] loc_            - Locale
    /// @param[in] bSkipWS_        - Whether to skip whitespaces
    /// @param[in] bCaseSensitive_ - Whether to process in case sensitive manner
    ///
    /// @returns - None
    ///////////////////////////////////////////////////////////////////////////
    virtual void process
    (
        std::istream &in_,
        const std::locale &loc_,
        const bool &bSkipWS_ = false,
        const bool &bCaseSensitive_ = false
    );

    // ---- ACCESS ----

    // ---- INQUIRY ----

    ///////////////////////////////////////////////////////////////////////////
    /// @fn name
    /// @brief Get the name of the component
    ///
    /// @returns - Name of the component
    ///////////////////////////////////////////////////////////////////////////
    virtual std::string name() const;

    ///////////////////////////////////////////////////////////////////////////
    /// @fn getAlnum
    /// @brief Get the frequency per alphanumeric character
    ///
    /// @param[out] vMap_   - Vector to store the frequencies
    /// @param[in] bSorted_ - Whether to sort the output in alphabetic order
    ///
    /// @returns - None
    ///////////////////////////////////////////////////////////////////////////
    void getAlnum
    (
        std::vector<std::pair<unsigned int, unsigned char> > &vMap_,
        const bool &bSorted_ = false
    );

    ///////////////////////////////////////////////////////////////////////////
    /// @fn getAlnum
    /// @brief Get the frequency of alphanumeric characters
    ///
    /// @returns - Frequency of alphanumeric characters
    ///////////////////////////////////////////////////////////////////////////
    unsigned int getAlnum() const;

    ///////////////////////////////////////////////////////////////////////////
    /// @fn getPunct
    /// @brief Get the frequency of punctuation characters
    ///
    /// @returns - Frequency of punctuation characters
    ///////////////////////////////////////////////////////////////////////////
    unsigned int getPunct() const;

    ///////////////////////////////////////////////////////////////////////////
    /// @fn getSpace
    /// @brief Get the frequency of whitespace characters
    ///
    /// @returns - Frequency of whitespace characters
    ///////////////////////////////////////////////////////////////////////////
    unsigned int getSpace() const;

    ///////////////////////////////////////////////////////////////////////////
    /// @fn getCtrl
    /// @brief Get the frequency of control characters
    ///
    /// @returns - Frequency of control characters
    ///////////////////////////////////////////////////////////////////////////
    unsigned int getCtrl() const;

    ///////////////////////////////////////////////////////////////////////////
    /// @fn getPrint
    /// @brief Get the frequency of printable characters
    ///
    /// @returns - Frequency of printable characters
    ///////////////////////////////////////////////////////////////////////////
    unsigned int getPrint() const;

    ///////////////////////////////////////////////////////////////////////////
    /// @fn getUnknown
    /// @brief Get the frequency of unknown characters
    ///
    /// @returns - Frequency of unknown characters
    ///////////////////////////////////////////////////////////////////////////
    unsigned int getUnknown() const;

private: 

    void reset();

    static const std::string m_Name;                    ///< Name of the component

    std::map<unsigned char, unsigned int> m_FreqAlnum;  ///< Frequency per alphanumeric character
    unsigned int m_FreqTotalAlnum;                      ///< Frequency of alphanumeric characters
    unsigned int m_FreqPunct;                           ///< Frequency of punctuation characters
    unsigned int m_FreqSpace;                           ///< Frequency of whitespace characters
    unsigned int m_FreqCtrl;                            ///< Frequency of control characters
    unsigned int m_FreqPrint;                           ///< Frequency of all printable characters
    unsigned int m_FreqUnknown;                         ///< Frequency of unknown characters
};

inline std::string CharFrequency::name() const
{
    return m_Name;
}

inline unsigned int CharFrequency::getAlnum() const
{
    return m_FreqTotalAlnum;
}

inline unsigned int CharFrequency::getPunct() const
{
    return m_FreqPunct;
}

inline unsigned int CharFrequency::getSpace() const
{
    return m_FreqSpace;
}

inline unsigned int CharFrequency::getCtrl() const
{
    return m_FreqCtrl;
}

inline unsigned int CharFrequency::getPrint() const
{
    return m_FreqPrint;
}

inline unsigned int CharFrequency::getUnknown() const
{
    return m_FreqUnknown;
}

#endif // _CHAR_FREQUENCY_HPP__

