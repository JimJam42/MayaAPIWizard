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

#include "ErrorCodes.h"

#include <iostream>
#include <QString>
#include <QMessageBox>

std::string WizardError::getErrorString(WIZARD_ERROR_CODE _code)
{
    switch(_code)
    {
        case(NO_ERROR)                      : return std::string("No error reported"); break;
        case(ERR_NO_PATH_SPECIFIED)         : return std::string("No path has been specified"); break;
        case(ERR_INVALID_PATH)              : return std::string("Invalid Path"); break;
        case(ERR_NO_NAME_SPECIFIED)         : return std::string("No name specified"); break;
        case(ERR_INVALID_NAME)              : return std::string("Invalid name given"); break;
        case(ERR_NO_VERSION_SPECIFIED)      : return std::string("No version specified"); break;
        case(ERR_INVALID_VERSION)           : return std::string("Invalid version"); break;
        case(ERR_INVALID_CHAR)              : return std::string("Invalid character used"); break;
        case(ERR_EMPTY_VECTOR)              : return std::string("Attempt to use an empty vector"); break;
        case(ERR_EMPTY_STACK)               : return std::string("Attempt to use an empty stack"); break;
        case(ERR_NULL_POINTER)              : return std::string("Attempted access to NULL pointer"); break;
        case(ERR_UNEXPECTED_ATTRIB_COUNT)   : return std::string("Unexpected number of attributes"); break;
        case(ERR_DIRECTORY_CREATION_FAILED) : return std::string("Creation of directiory failed"); break;
        case(ERR_GENERATOR_QUIT)            : return std::string("Generator process unexpectedly quit"); break;
        case(ERR_FILE_DOES_NOT_EXIST)       : return std::string("File does not exist"); break;
        case(ERR_OBJECT_NOT_FOUND)          : return std::string("Object not found"); break;
        case(ERR_VALUE_NOT_FOUND)           : return std::string("Value not found"); break;
        case(ERR_CANT_OPEN_FILE)            : return std::string("Could not open file"); break;
        case(ERR_INVALID_ARGUMENTS)         : return std::string("Invalid arguments somewhere. Check all names and short names are not NULL and none are the same!"); break;
        case(ERR_CONFLICTING_NAMES)         : return std::string("Conflicting names have been entered! Maybe there are two names that cannot be the same!"); break;
        case(ERR_INVALID_FILEEXT)           : return std::string("Invalid file name, can only contain alpha numeric characters or numbers"); break;
        default                             : return std::string("Invalid Error Code"); break;
    }
}

bool WizardError::checkForError(WIZARD_ERROR_CODE _code, bool _errorDilog, QWidget *_parent)
{
    if (_code == NO_ERROR)
    {
        #ifdef WIZ_DEBUG
            printError(_code);
        #endif
        return true;
    }
    else
    {
        std::string errorString = getErrorString(_code);
        std::cout<<"**!! "<<errorString<<" !!**"<<std::endl;
        if (_errorDilog)
        {
            QMessageBox *errDialog = new QMessageBox();
            errDialog->critical(_parent,"Error",QString(errorString.c_str()));
        }
        return false;
    }
}
