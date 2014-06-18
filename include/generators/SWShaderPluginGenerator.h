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

#ifndef __SWSHADER_PLUGIN_GENERATOR_H__
#define __SWSHADER_PLUGIN_GENERATOR_H__

/// @file SWShaderPluginGenerator.h
/// @brief Generator to create Software Shader framework
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class SWShaderPluginGenerator
/// @brief Generator class inheriting from SourceGenerator to generate framework for a Software Shader

#include "SourceGenerator.h"

class SWShaderPluginGenerator : public SourceGenerator
{
public:
    /// @brief ctr
    SWShaderPluginGenerator();
    /// @brief dtr
    ~SWShaderPluginGenerator();

    // overloads of virtual functions within SourceGenerator
    /// @brief Function to return the type of plugin this generator supports
    /// @returns PLUGIN_TYPE
    PLUGIN_TYPE genType() {return SHADER_SW;}
    /// @brief overridden function to convert and store the attributes passed in
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE convertAndStoreAttributes();
    /// @brief overridden function to actually generate the framework
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE generate();

private:
    /// @brief The name of the software shader
    std::string m_swName;
    /// @brief Whether to add objects or not
    bool m_addObjs;

};

#endif /* __SWSHADER_PLUGIN_GENERATOR_H__ */