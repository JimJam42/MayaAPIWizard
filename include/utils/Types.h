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

#ifndef __TYPES_H__
#define __TYPES_H__

/// @file Types.h
/// @brief Header to define comonly used types across classes
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014

#include <stdio.h>
#include <string>
#include <vector>

/// @enum PLUGIN_TYPE
/// @brief Different possible plugin type identifiers
enum PLUGIN_TYPE
{
    NO_PLUGIN_TYPE, // works as a null type that will be defaulted to test if a type has been set
    SIMPLE_CMD,
    CMD,
    TOOL,
    NODE,
    FILE_TRANS,
    SHADER_HW,
    SHADER_SW,
    FIELD,
    EMITTER,
    SPRING,
    SHAPE
};

/// @enum ND_TYPE
/// @brief Specific node type identifiers
enum ND_TYPE
{
    ND_NOTYPE,
    ND_BASIC_NODE,
    ND_LOCATOR_NODE,
    ND_DEFORMER_NODE,
    ND_MANIP_CONTAIN,
    ND_IK_SOLVER,
    ND_TRANSFORM,
    ND_HW_SHADER_NODE,
    ND_OBJECT,
    ND_IMAGE_PLANE,
    ND_PARTICLE_ATTRIB_MAPPER,
    ND_CONSTRAINT,
    ND_MANIP
};

/// @enum MAYA_LIBRARIES
/// @brief different maya library identifiers
enum MAYA_LIBRARIES
{
    LIB_FOUNDATION,
    LIB_OPEN_MAYA,
    LIB_OPEN_MAYA_UI,
    LIB_OPEN_MAYA_ANIM,
    LIB_OPEN_MAYA_FX,
    LIB_OPEN_MAYA_RENDER,
    LIB_IMAGE,
    LIB_MOCAP,
    NO_LIB_TYPE
};

/// @struct AddedArgument
/// @brief Structure used to store any added arguments from the node graph together for easier
/// storage, reading and  movement of data
struct AddedArgument // used to store arguments found within the attributes vector
{
    /// @brief the paramater type, such as OBJECT or ARGUMENT
    std::string _vType;
    /// @brief the value type, such as bool or int
    std::string _type;
    /// @brief the name of the added argument
    std::string _name;
    /// @brief the short name of the arugment that will be used on the comnmand line
    std::string _shortName;
};

#endif /* __TYPES_H__ */
