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

#ifndef __NODE_PLUGIN_GENERATOR_H__
#define __NODE_PLUGIN_GENERATOR_H__

#include "SourceGenerator.h"

/// @file NodePluginGenerator.h
/// @brief Generator to create Node plugin framework
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class NodePluginGenerator
/// @brief Generator class inheriting from SourceGenerator to generate framework for a Node Maya plugin

class NodePluginGenerator : public SourceGenerator
{
public:
    /// @brief ctr
    NodePluginGenerator();
    /// @brief dtr
    ~NodePluginGenerator();

    // overloads of virtual functions within SourceGenerator
    /// @brief Function to return the type of plugin this generator supports
    /// @returns PLUGIN_TYPE
    PLUGIN_TYPE genType() {return NODE;}
    /// @brief overridden function to convert and store the attributes passed in
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE convertAndStoreAttributes();
    /// @brief overridden function to actually generate the framework
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE generate();

private:
    /// @brief The name of the node plugin
    std::string m_nodePluginName;
    /// @brief The chosen type of node to make
    ND_TYPE m_chosenType;
    /// @brief The class from which the ndoe inherits
    std::string m_inheritsFrom;
    /// @brief The type of node as a Maya type (string)
    std::string m_mayaNodeType;
    /// @brief Whether to add objects or not
    bool m_addObjs;

    /// @brief Get specific functions to this node type
    /// @param [in] _type ND_TYPE - the node type to use
    /// @param [in] _obj QJsonObject - the object within which the data is stored
    /// @param [out] _vec std::vector<std::string>* - the vector to write the results to
    WizardError::WIZARD_ERROR_CODE getNodeTypeSpecificFns(ND_TYPE _type, QJsonObject _obj,
                                                                           std::vector<std::string> *_vec);

};

#endif /* __NODE_PLUGIN_GENERATOR_H__ */
