///////////////////////////////////////////////////////////////////////////////
/// @file Substituter_Main.cpp
/// @brief Main Entrance of Substituter (CLI-based)
///
/// Related Files:
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

#include <fstream>
#include <iostream>
#include <string.h>
#include <argp.h>
#include "CharSubstituteConfigure.hpp"
#include "CharSubstituter.hpp"

static const std::string g_strAppName = "MasterMind Substituter";
const char * argp_program_bug_address = "<Lissy.Lau@gmail.com>";

// Hard-coded and settable configuration options
struct AppOptions
{
    char          vmajor;
    char          vminor;
    std::string   date;
    std::string   inFile;
    std::string   outFile;
    std::string   scheme;
    bool          bEncrypt;
};

static AppOptions appOptions =
{
    1,                    // vmajor         (hard-coded)
    0,                    // vminor         (hard-coded)
    __DATE__" "__TIME__,  // date           (hard-coded)
    "",                   // inFile         (command-line settable)
    "",                   // outFile        (command-line settable)
    "",                   // scheme         (command-line settable)
    false,                // bEncrypt       (command-line settable)
};

static struct argp_option appArgpOptions[] =
{
    {"inFile",        'i', "INPUT_FILE",  0, "Input file",                                      0},
    {"outFile",       'o', "OUTPUT_FILE", 0, "Output file, output to STD_OUT if not specified", 0},
    {"scheme",        's', "SCHEME",      0, "Substitution scheme",                             0},
    {"encrypt",       'e', NULL,          0, "Encrypt or decrypt flag",                         0},
    {0}
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Print the version of the application
///
/// @param[in] stream - FILE stream destination of the output
/// @param[in] state  - Unused
///
/// @returns - None
///////////////////////////////////////////////////////////////////////////////
static void printVersion
(
    FILE *              stream,
    struct argp_state * state __attribute__((unused))
)
{
    if (NULL != stream)
    {
        fprintf(stream, "%s v%d.%d %s\n", g_strAppName.c_str(),
                appOptions.vmajor, appOptions.vminor, appOptions.date.c_str());
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Parse the command line options
///
/// @param[in] key   - The key referring to the command line argument
/// @param[in] arg   - The value of the current command line argument
/// @param[in] state - Used to get the current argument setting
///
/// @returns - An error indication (EINVAL) or 0 on success
///////////////////////////////////////////////////////////////////////////////
static error_t parseOpt
(
    int                 key,
    char *              arg,
    struct argp_state * state
)
{
    if (NULL == state)
    {
        return EINVAL;
    }

    AppOptions * arguments = static_cast<AppOptions *>(state->input);

    switch (key)
    {
        case 'i':    // --inFile
            arguments->inFile = arg;
            break;

        case 'o':    // --outFile
            arguments->outFile = arg;
            break;

        case 's':    // --scheme
            arguments->scheme = arg;
            break;

        case 'e':    // --encrypt
            arguments->bEncrypt = true;

        case ARGP_KEY_ARG:
            argp_error(state, "Too many arguments!");
            break;

        case ARGP_KEY_END:
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp argp = {appArgpOptions, parseOpt, "", "", 0, 0, 0};

void processSubstitution(const AppOptions &appOptions_)
{
    CharSubstituteConfigure charSubstituteConfig(appOptions_.scheme, appOptions_.bEncrypt);
    CharSubstituter charSubstituter(charSubstituteConfig);

    std::ifstream inFile;
    inFile.open(appOptions_.inFile.c_str());
    if ("" != appOptions_.outFile)
    {
        std::ofstream outFile;
        outFile.open(appOptions_.outFile.c_str());
        charSubstituter.process(inFile, outFile);
        outFile.close();
    }
    else
    {
        // Output to STD_OUT when outFile is not specified
        charSubstituter.process(inFile, std::cout);
    }
    inFile.close();
}

int main(int argc, char ** argv)
{
    // Or set the argp_program_version
    argp_program_version_hook = printVersion;

    if (argp_parse(&argp, argc, argv, 0, 0, &appOptions))
    {
        return -1;
    }

    processSubstitution(appOptions);

    return 0;
}
