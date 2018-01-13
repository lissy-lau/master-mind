///////////////////////////////////////////////////////////////////////////////
/// @file CharSubstituteConfigure.cpp
/// @brief Character Substitution Configuration Class of MasterMind.
///
/// Related Files:
/// @li CharSubstituteConfigure.h - Declaration
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

#include <ctype.h>
#include <string.h>
#include <fstream>
#include <locale>
#include "CharSubstituteConfigure.hpp"

const std::string CharSubstituteConfigure::m_Name = "Character Substitution Configuration";

CharSubstituteConfigure::~CharSubstituteConfigure()
{
}

CharSubstituteConfigure::CharSubstituteConfigure
(
    std::string scheme_,
    bool bEncrypt_
) :
m_Valid(false)
{
    // Version check
    LIBXML_TEST_VERSION

    xmlDocPtr schemeDoc = xmlParseFile(scheme_.c_str());

    if (NULL != schemeDoc)
    {
        if (checkScheme(schemeDoc))
        {
            if (readScheme(schemeDoc, bEncrypt_))
            {
                m_Valid = true;
            }
        }

        xmlFreeDoc(schemeDoc);
    }
    else
    {
        std::cout << "[" << __PRETTY_FUNCTION__ << "] Failed to create XML Scheme Doc!" << std::endl;
    }
}

CharSubstituteConfigure::CharSubstituteConfigure(const CharSubstituteConfigure &obj_)
{
    memcpy(m_Data, obj_.m_Data, VOCABULARY_SIZE);
    m_Valid = obj_.m_Valid;
}

CharSubstituteConfigure & CharSubstituteConfigure::operator =(const CharSubstituteConfigure &obj_)
{
    memcpy(m_Data, obj_.m_Data, VOCABULARY_SIZE);
    m_Valid = obj_.m_Valid;

    return (*this);
}

bool CharSubstituteConfigure::checkScheme(xmlDocPtr schemeDoc_)
{
    bool bOK = false;

    // Parameter validation
    if (NULL == schemeDoc_)
    {
        std::cout << "[" << __PRETTY_FUNCTION__ << "] Invalid substitution scheme!" << std::endl;
        return false;
    }

    /// @todo Will change the hard-coded file name to sth. in configuration file
    xmlDocPtr schemaDoc = xmlReadFile("../../Schema/SubstitutionScheme.xsd", NULL,
                                      XML_PARSE_NONET | XML_PARSE_NOENT);
    if (NULL != schemaDoc)
    {
        xmlSchemaParserCtxtPtr parserCtxt = xmlSchemaNewDocParserCtxt(schemaDoc);

        if (NULL != parserCtxt)
        {
            xmlSchemaPtr schema = xmlSchemaParse(parserCtxt);

            if (NULL != schema)
            {
                xmlSchemaValidCtxtPtr validCtxt = xmlSchemaNewValidCtxt(schema);

                if (NULL != validCtxt)
                {
                    if (0 == xmlSchemaValidateDoc(validCtxt, schemeDoc_))
                    {
                        bOK = true;
                    }

                    xmlSchemaFreeValidCtxt(validCtxt);
                }
                else
                {
                    std::cout << "[" << __PRETTY_FUNCTION__;
                    std::cout << "] Failed to create XML Schema Validate Context!" << std::endl;
                }

                xmlSchemaFree(schema);
            }
            else
            {
                std::cout << "[" << __PRETTY_FUNCTION__;
                std::cout << "] Failed to create XML Schema!" << std::endl;
            }

            xmlSchemaFreeParserCtxt(parserCtxt);
        }
        else
        {
            std::cout << "[" << __PRETTY_FUNCTION__;
            std::cout << "] Failed to create XML Schema Parser Context!" << std::endl;
        }

        xmlFreeDoc(schemaDoc);
    }
    else
    {
        std::cout << "[" << __PRETTY_FUNCTION__;
        std::cout << "] Failed to create XML Schema Doc!" << std::endl;
    }

    return bOK;
}

bool CharSubstituteConfigure::readScheme(xmlDocPtr schemeDoc_, bool bEncrypt_)
{
    bool bCaseSensitive = false;
    bool bKeepOriginal  = true;
    bool bOK            = true;

    unsigned char unknownChar = ' ';

    xmlChar * readChar = NULL;

    // Parameter validation
    if (NULL == schemeDoc_)
    {
        std::cout << "[" << __PRETTY_FUNCTION__ << "] Invalid substitution scheme!" << std::endl;
        return false;
    }

    // Get the root element, check if the scheme is empty
    xmlNodePtr curNode = xmlDocGetRootElement(schemeDoc_);

    if (NULL != curNode)
    {
        if (NULL != (curNode = curNode->xmlChildrenNode))
        {
            // Ignore other nodes
            while (NULL != curNode)
            {
                if (0 == xmlStrcmp(curNode->name, BAD_CAST "SubstitutionAlgorithm"))
                {
                    break;
                }
                curNode = curNode->next;
            }

            // Read substitution algorithm configuration
            // The configuration should be valid since it's been validated with the schema
            readChar = xmlGetProp(curNode, BAD_CAST "Name");
            if ((NULL != readChar)&&(0 == xmlStrcmp(readChar, BAD_CAST "Simple Substitution")))
            {
                xmlFree(readChar);

                readChar = xmlGetProp(curNode, BAD_CAST "CaseSensitive");
                if ((NULL != readChar)&&(0 == xmlStrcmp(readChar, BAD_CAST "1")))
                {
                    bCaseSensitive = true;
                }
                xmlFree(readChar);

                readChar = xmlGetProp(curNode, BAD_CAST "KeepUnknownChar");
                if ((NULL != readChar)&&(0 == xmlStrcmp(readChar, BAD_CAST "0")))
                {
                    bKeepOriginal = false;
                }
                xmlFree(readChar);

                readChar = xmlGetProp(curNode, BAD_CAST "UnknownMask");
                if ((NULL != readChar)&&(1 == xmlStrlen(readChar)))
                {
                    unknownChar = readChar[0];
                }
                else
                {
                    if (!bKeepOriginal)
                    {
                        std::cout << "[" << __PRETTY_FUNCTION__;
                        std::cout << "] Invalid unknown mask character!" << std::endl;
                        bOK = false;
                    }
                }
                xmlFree(readChar);

                // Initialization substitution tuples
                if (bOK)
                {
                    for (int i = 0; i < VOCABULARY_SIZE; i++)
                    {
                        if (isprint((unsigned char)i))
                        {
                            if (bKeepOriginal)
                            {
                                m_Data[i] = (unsigned char)i;
                            }
                            else
                            {
                                m_Data[i] = unknownChar;
                            }
                        }
                        else
                        {
                            // Do NOT substitute non-printable characters
                            m_Data[i] = (unsigned char)i;
                        }
                    }
                }
            }
            else
            {
                std::cout << "[" << __PRETTY_FUNCTION__;
                std::cout << "] Unsupported substitution algorithm!" << std::endl;
                bOK = false;

                xmlFree(readChar);
            }
        }

        // Read substitution tuples
        while (bOK)
        {
            unsigned char plainChar  = '\0';
            unsigned char cipherChar = '\0';

            // Ignore other nodes
            while (NULL != (curNode = curNode->next))
            {
                if (0 == xmlStrcmp(curNode->name, BAD_CAST "SubstitutionTuple"))
                {
                    break;
                }
            }

            // No more substitution tuples to read
            if (NULL == curNode)
            {
                break;
            }

            readChar = xmlGetProp(curNode, BAD_CAST "Plain");
            if ((NULL != readChar)&&(1 == xmlStrlen(readChar)))
            {
                plainChar = readChar[0];
            }
            else
            {
                std::cout << "[" << __PRETTY_FUNCTION__;
                std::cout << "] Invalid plain character!" << std::endl;
                bOK = false;
                break;
            }
            xmlFree(readChar);

            readChar = xmlGetProp(curNode, BAD_CAST "Cipher");
            if ((NULL != readChar)&&(1 == xmlStrlen(readChar)))
            {
                cipherChar = readChar[0];
            }
            else
            {
                std::cout << "[" << __PRETTY_FUNCTION__;
                std::cout << "] Invalid cipher character!" << std::endl;
                bOK = false;
                break;
            }
            xmlFree(readChar);

            if (bCaseSensitive)
            {
                if (bEncrypt_)
                {
                    m_Data[(int)plainChar] = cipherChar;
                }
                else
                {
                    m_Data[(int)cipherChar] = plainChar;
                }
            }
            else
            {
                if (bEncrypt_)
                {
                    m_Data[(int)std::toupper(plainChar)] = std::toupper(cipherChar);
                    m_Data[(int)std::tolower(plainChar)] = std::tolower(cipherChar);
                }
                else
                {
                    m_Data[(int)std::toupper(cipherChar)] = std::toupper(plainChar);
                    m_Data[(int)std::tolower(cipherChar)] = std::tolower(plainChar);
                }
            }
        }
    }
    else
    {
        std::cout << "[" << __PRETTY_FUNCTION__;
        std::cout << "] Substitution Scheme is empty!" << std::endl;
        bOK = false;
    }

    return bOK;
}

