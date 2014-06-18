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

#ifndef __COMMAND_PLUGIN_GENERATOR_H__
#define __COMMAND_PLUGIN_GENERATOR_H__

/// @file CommandPluginGenerator.h
/// @brief Generator to create Mel Command framework
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class CommandPluginGenerator
/// @brief Generator class inheriting from SourceGenerator to generate framework for a CommandPlugin

#include "SourceGenerator.h"

class CommandPluginGenerator : public SourceGenerator
{
public:
    /// @brief ctr
    CommandPluginGenerator();
    /// @brief dtr
    ~CommandPluginGenerator();

    // overloads of virtual functions within SourceGenerator
    /// @brief Function to return the type of plugin this generator supports
    /// @returns PLUGIN_TYPE
    PLUGIN_TYPE genType() {return CMD;}
    /// @brief overridden function to convert and store the attributes passed in
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE convertAndStoreAttributes();
    /// @brief overridden function to actually generate the framework
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE generate();

private:
    // plugin type specifics
    /// @brief The name of the command
    std::string m_commandName;
    /// @brief The name of the command class
    std::string m_commandClassName;
    /// @brief Is the command redoable?
    bool m_redoable;
    /// @brief Whether to add arguments or not to the command
    bool m_addArgs;

    // some utility functions specific to this generator to make generation of code easier
    /// @brief Function to automatically generate the right flag for the argument passed in
    /// @param [in] _arg AddedArgument - the argument passed in
    /// @returns std::string
    std::string getAddFlagFromArgument(AddedArgument _arg);
    /// @brief Function to generate the parser setup code for the passed in argument
    /// @param [in] _arg AddedArgument - the argument passed in
    /// @returns std::string
    std::string parserFlagSetFromArgument(AddedArgument _arg);
};

#endif /* __COMMAND_PLUGIN_GENERATOR_H__ */
