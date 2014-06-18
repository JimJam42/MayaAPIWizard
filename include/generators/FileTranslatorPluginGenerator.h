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

#ifndef __FILE_TRANSLATOR_PLUGIN_GENERATOR_H__
#define __FILE_TRANSLATOR_PLUGIN_GENERATOR_H__

#include "SourceGenerator.h"

/// @file FileTranslatorPluginGenerator.h
/// @brief Generator to create a File Translator framework
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class FileTranslatorPluginGenerator
/// @brief Generator class inheriting from SourceGenerator to generate framework for a File Translator

class FileTranslatorPluginGenerator : public SourceGenerator
{
public:
    /// @brief ctr
    FileTranslatorPluginGenerator();
    /// @brief dtr
    ~FileTranslatorPluginGenerator();

    // overloads of virtual functions within SourceGenerator
    /// @brief Function to return the type of plugin this generator supports
    /// @returns PLUGIN_TYPE
    PLUGIN_TYPE genType() {return FILE_TRANS;}
    /// @brief overridden function to convert and store the attributes passed in
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE convertAndStoreAttributes();
    /// @brief overridden function to actually generate the framework
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE generate();

private:
    // plugin type specifics
    /// @brief Class name
    std::string m_ftClassName;
    /// @brief File translator name
    std::string m_ftName;
    /// @brief Name for the UI script
    std::string m_uiScriptName;
    /// @brief Whether it is impot or export or both
    std::string m_impExp;
    /// @brief The default file extension
    std::string m_defaultFileExtension;
    /// @brief Whether to add private attributes or not
    bool m_addPrivAttribs;

};

#endif /* __FILE_TRANSLATOR_PLUGIN_GENERATOR_H__ */
