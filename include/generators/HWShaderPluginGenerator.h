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

#ifndef __HWSHADER_PLUGIN_GENERATOR_H__
#define __HWSHADER_PLUGIN_GENERATOR_H__

#include "SourceGenerator.h"

/// @file HWShaderPluginGenerator.h
/// @brief Generator to create Hardeware Shader framework
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class HWShaderPluginGenerator
/// @brief Generator class inheriting from SourceGenerator to generate framework for a Hardware Shader

class HWShaderPluginGenerator : public SourceGenerator
{
public:
    /// @brief ctr
    HWShaderPluginGenerator();
    /// @brief dtr
    ~HWShaderPluginGenerator();

    // overloads of virtual functions within SourceGenerator
    /// @brief Function to return the type of plugin this generator supports
    /// @returns PLUGIN_TYPE
    PLUGIN_TYPE genType() {return SHADER_HW;}
    /// @brief overridden function to convert and store the attributes passed in
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE convertAndStoreAttributes();
    /// @brief overridden function to actually generate the framework
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE generate();

private:
    /// @brief Name of the main plugin class
    std::string m_hwName;
    /// @brief Name of the shader override class
    std::string m_hwNameOR;
    /// @brief Whether to add objects or not
    bool m_addObjs;

};

#endif /* __HWSHADER_PLUGIN_GENERATOR_H__ */
