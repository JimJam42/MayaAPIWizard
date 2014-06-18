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

#ifndef __GENERATORS_H__
#define __GENERATORS_H__

#include "Types.h"
#include "SourceGenerator.h"

/// @file Generators.h
/// @brief Custom namespace to get the correct generator based on the plugin type
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @namespace Generators
/// @brief Custom namespace to get the correct generator based on the plugin type

/// @namespace Generators
/// @brief Simple custom namespace containing function to return correct generator for a plugin type
namespace Generators
{
    /// @brief Function to return the correct generator based on the passed in plugin type
    /// @param [in] _type PLUGIN_TYPE - the plugin type passed in
    /// @returns SOurceGenerator*
    SourceGenerator* getPluginGenerator(PLUGIN_TYPE _type);
}

#endif /* __GENERATORS_H__ */
