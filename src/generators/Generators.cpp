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

#include "Generators.h"

#include "CommandPluginGenerator.h"
#include "FileTranslatorPluginGenerator.h"
#include "NodePluginGenerator.h"
#include "SWShaderPluginGenerator.h"
#include "HWShaderPluginGenerator.h"
#include "EmitterPluginGenerator.h"

SourceGenerator* Generators::getPluginGenerator(PLUGIN_TYPE _type)
{
    switch(_type)
    {
        case(CMD)       : return new CommandPluginGenerator; break;
        case(FILE_TRANS): return new FileTranslatorPluginGenerator; break;
        case(NODE)      : return new NodePluginGenerator; break;
        case(SHADER_SW) : return new SWShaderPluginGenerator; break;
        case(SHADER_HW) : return new HWShaderPluginGenerator; break;
        case(EMITTER) : return new EmitterPluginGenerator; break;
        default         : return NULL; break;
    }
}
