/*
  Copyright (C) 2014 Callum James

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __UTILITIES_H__
#define __UTILITIES_H__

/// @file Utilities.h
/// @brief Custom namepsace containing generic and commonly used functions and tools
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @namespace Utilities
/// @brief Custom namepsace containing generic and commonly used functions and tools

#include "Types.h"

#include <stdlib.h>
#include <string>

#include "ErrorCodes.h"

#include <QMessageBox>
#include <QFile>

// include for the reading of json files containing the framework
#include <QJsonDocument>
#include <QJsonObject>

#define NO_LIB_STRING "__no_lib_type__"

/// @namespace Utilities
/// @brief Custom namepsace containing generic and commonly used functions and tools
namespace Utilities
{
    /// @brief Get plugin type name from type
    /// @param [in] _type PLUGIN_TYPE - type passed in
    /// @returns std::string
    std::string pluginTypeName(PLUGIN_TYPE _type);
    /// @brief Get plugin type from name
    /// @param [in] _name std::string - name passed in
    /// @returns PLUGIN_TYPE
    PLUGIN_TYPE pluginTypeFromName(std::string _name);
    /// @brief Get the name of a library from its type and set link ready or not
    /// @param [in] _lib MAYA_LIBRARIES - library to get the name of
    /// @param [in] _linkReady bool - whether to retur it link ready or not
    std::string libraryTypeName(MAYA_LIBRARIES _lib, bool _linkReady=true);
    /// @brief Get the name of a library from its type in string form and set link ready or not
    /// @param [in] _libType std::string - library type to get the name of
    /// @param [in] _linkReady bool - whether to retur it link ready or not
    std::string libraryTypeName(std::string _libType, bool _linkReady=true);

    /// @brief Represent a bool as a string
    /// @param [in] _b bool - bool passed in
    /// @returns std::string
    std::string boolToString(bool _b);
    /// @brief Convert a string to a bool
    /// @param [in] _s std::string - string passed in
    /// @returns bool
    bool stringToBool(std::string _s);
    /// @brief Modify file paths if necessary due to platform being built on
    /// @param [in] _path std::string - path to modify
    /// @returns std::string
    std::string PLATFORM_FILE_PATH(std::string _path);
    /// @brief Check if a path exists
    /// @param [in] _path std::string - path to check
    /// @returns bool
    bool pathExists(std::string _path);
    /// @brief Warn of a folder being replaced
    /// @param [in] _main std::string - the main message for the dialog
    /// @param [in] _secondary std::string - the secondary message for the dialog
    /// @returns int - choice chosen
    int warnOfFolderReplacement(std::string _main, std::string _secondary);
    /// @brief Safe create a directory
    /// @param [in] _path std::string - path of dir to create
    /// @param [in] _removeIfExists bool - remove directory if it already exists
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE safeCreateDirectory(std::string _path, bool _removeIfExists);
    /// @brief Get the full contents of a file
    /// @param [in] _path std::string - path to file
    /// @param [out] _contents QString* - string to write contents to
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE getContentsOfFile(std::string _path, QString *_contents);
    /// @brief Find object in Json file - write result to string
    /// @param [in] _toFind std::string - to find
    /// @param [in] _obj QJsonObject - the object to search
    /// @param [out] _str std::string* - the string to write to
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE findInJsonObj(std::string _toFind, QJsonObject &_obj, std::string *_str);
    /// @brief Find object in Json file - write result to vector of strings
    /// @param [in] _toFind std::string - to find
    /// @param [in] _obj QJsonObject - the object to search
    /// @param [out] _str std::vector<std::string>* - the vector to write to
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE findInJsonObj(std::string _toFind, QJsonObject &_obj, std::vector<std::string> *_str);

    /// @brief Replace in string with string
    /// @param [out] _string std::string* - to replace in
    /// @param [in] _pattern std::string - pattern to replace
    /// @param [in] _replaceWith std::string - replace with
    void replaceInString(std::string *_string, std::string _pattern, std::string _replaceWith);
    /// @brief Replace in vector of strings with string
    /// @param [out] _vec std::vector<std::string>* - to replace in
    /// @param [in] _pattern std::string - pattern to replace
    /// @param [in] _replaceWith std::string - replace with
    void replaceInStringVector(std::vector<std::string> *_vec, std::string _pattern, std::string _replaceWith);
    /// @brief Replace in string with vector of strings
    /// @param [out] _string std::string* - to replace in
    /// @param [in] _pattern std::string - pattern to replace
    /// @param [in] _replaceWith std::vector<std::string> - replace with
    void replaceInStringWithVector(std::string *_string, std::string _pattern, std::vector<std::string> _replaceWith);
    /// @brief Replace in vector of strings with vector of strings
    /// @param [out] _vec std::vector<std::string>* - to replace in
    /// @param [in] _pattern std::string - pattern to replace
    /// @param [in] _replaceWith std::vector<std::string> - replace with
    void replaceInStringVectorWithVector(std::vector<std::string> *_vec, std::string _pattern,
                                         std::vector<std::string> _replaceWith);
    // append on the end of the dest vector
    /// @brief append a string onto a vector of strings
    /// @param [in] _string std::string - string to append
    /// @param [out] _dest std::vector<std::string> - destination vector
    void writeStringToVector(std::string _string, std::vector<std::string> *_dest);
    // simply append on the end of the dest vector
    /// @brief append a vector of strings onto a vector of strings
    /// @param [in] _src std::vector<std::string> - vector of strings to append
    /// @param [out] _dest std::vector<std::string> - destination vector
    void writeVectorToVector(std::vector<std::string> _src, std::vector<std::string> *_dest);

    /// @brief Write the contents of a vector of strings to a file
    /// @param [in] _filePath std::string -path of file to write to
    /// @param [in] _vec std::vector<std::string> - vector to write
    /// @returns WizardError::WIZARD_ERROR_PAGE
    WizardError::WIZARD_ERROR_CODE writeVectorToFile(std::string _filePath, std::vector<std::string> &_vec);

    /// @brief Create string representation of argument
    /// @param [in] _arg AddedArgument - argument passed in
    /// @returns std::string
    std::string argumentToStringRep(AddedArgument _arg);
    /// @brief Create valid string representation of argument type
    /// @param [in] _type std::string - type passed in
    /// @returns std::string
    std::string argumentTypeToTypeInString(std::string _type);
    /// @brief Create valid string declaration of MObject for header file
    /// @param [in] _class std::string - class to add to
    /// @param [in] _name std::string - name of new member
    /// @returns std::string
    std::string createObjectCppDecString(std::string _class, std::string _name);
    /// @brief Convert an argument type to its Maya equivalent
    /// @param [in] _type std::string - type passed in
    /// @returns std::string
    std::string argTypeToMayaTypeString(std::string _type);

    /// @brief get node plugin name from type
    /// @param [in] _type ND_TYPE - type passed in
    /// @returns std::string
    std::string nodePluginTypeToName(ND_TYPE _type);
    /// @brief Get node plugin type from its name
    /// @param [in] _name std::string - the node name
    /// @returns ND_TYPE
    ND_TYPE nodePluginTypeFromName(std::string _name);


}

#endif /* __UTILITIES_H__ */
