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

#ifndef __ERRORCODES_H__
#define __ERRORCODES_H__

/// @file ErrorCodes.h
/// @brief Custom namespace containing custom error codes to allow easy catching of errors
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @namespace ErrorCodes
/// @brief Custom namespace containing custom error codes to allow easy catching of errors

#include <stdlib.h>
#include <string>
#include <QWidget>

/// @namespace WizardError
/// @brief Small custom namespace to define new error codes used by the wizard and then functions to understand them
namespace WizardError
{
    /// @enum WIZARD_ERROR_CODE
    /// @brief Specific error codes for the wizard to make error handling easy to understand
    enum WIZARD_ERROR_CODE
    {
        NO_ERROR = 0,
        ERR_NO_PATH_SPECIFIED,
        ERR_INVALID_PATH,
        ERR_NO_NAME_SPECIFIED,
        ERR_INVALID_NAME,
        ERR_NO_VERSION_SPECIFIED,
        ERR_INVALID_VERSION,
        ERR_INVALID_CHAR,
        ERR_EMPTY_VECTOR,
        ERR_EMPTY_STACK,
        ERR_NULL_POINTER,
        ERR_UNEXPECTED_ATTRIB_COUNT,
        ERR_DIRECTORY_CREATION_FAILED,
        ERR_GENERATOR_QUIT,
        ERR_FILE_DOES_NOT_EXIST,
        ERR_OBJECT_NOT_FOUND,
        ERR_VALUE_NOT_FOUND,
        ERR_CANT_OPEN_FILE,
        ERR_INVALID_ARGUMENTS,
        ERR_CONFLICTING_NAMES,
        ERR_INVALID_FILEEXT
    };
    /// @brief Function to convert an error code to a string
    /// @param [in] _code WIZARD_ERROR_CODE - error code to read
    /// @returns std::string
    std::string getErrorString(WIZARD_ERROR_CODE _code);
    /// @brief Function to check for error and return if one has occured
    /// @param [in] _code WIZARD_ERROR_CODE - code to check
    /// @param [in] _errorDilog bool - whether or not to show an error dialog
    /// @param [in] _parent QWidget* - parent for the error dialog
    /// @returns bool
    bool checkForError(WIZARD_ERROR_CODE _code, bool _errorDilog=false, QWidget *_parent=0);
}

#endif /* __ERRORCODES_H__ */
