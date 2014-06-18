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

#include "Utilities.h"

#include <QJsonArray>

#include <fstream>

// include boost/filesystem for file checking
#include <boost/filesystem.hpp>

#ifdef DARWIN
    #include <CoreFoundation/CoreFoundation.h>
#endif

#ifdef WIN32
    #include <windows.h>
#endif

std::string Utilities::pluginTypeName(PLUGIN_TYPE _type)
{
    switch(_type)
    {
        case(SIMPLE_CMD): return std::string("Simple Mel Command");break;
        case(CMD): return std::string("Mel Command");break;
        case(TOOL): return std::string("Interactive Tool");break;
        case(NODE): return std::string("Node");break;
        case(FILE_TRANS): return std::string("File Translator");break;
        case(SHADER_SW): return std::string("Software Shader");break;
        case(SHADER_HW): return std::string("Hardware Shader");break;
        case(FIELD): return std::string("Dynamic Field");break;
        case(EMITTER): return std::string("Dynamic Emitter");break;
        case(SPRING): return std::string("Dynamic Spring");break;
        case(SHAPE): return std::string("Shape");break;
        default: return std::string("__undefined_type__");break;
    }
}

PLUGIN_TYPE Utilities::pluginTypeFromName(std::string _name)
{
    if      (_name == "Simple Mel Command") return SIMPLE_CMD;
    else if (_name == "Mel Command") return CMD;
    else if (_name == "Interactive Tool") return TOOL;
    else if (_name == "Node") return NODE;
    else if (_name == "File Translator") return FILE_TRANS;
    else if (_name == "Software Shader") return SHADER_SW;
    else if (_name == "Hardware Shader") return SHADER_HW;
    else if (_name == "Dynamic Field") return FIELD;
    else if (_name == "Dynamic Emitter") return EMITTER;
    else if (_name == "Dynamic Spring") return SPRING;
    else if (_name == "Shape") return SHAPE;
    else return NO_PLUGIN_TYPE;
}

std::string Utilities::libraryTypeName(MAYA_LIBRARIES _lib, bool _linkReady)
{
    std::string returnString = "";
    if (_linkReady)
    {
        returnString += "-l";
    }

    switch(_lib)
    {
        case(LIB_FOUNDATION): returnString += "Foundation";break;
        case(LIB_OPEN_MAYA): returnString += "OpenMaya";break;
        case(LIB_OPEN_MAYA_UI): returnString += "OpenMayaUI";break;
        case(LIB_OPEN_MAYA_ANIM): returnString += "OpenMayaAnim";break;
        case(LIB_OPEN_MAYA_FX): returnString += "OpenMayaFX";break;
        case(LIB_OPEN_MAYA_RENDER): returnString += "OpenMayaRender";break;
        case(LIB_IMAGE): returnString += "Image";break;
        case(LIB_MOCAP): returnString += "mocap";break;
        default: returnString = NO_LIB_STRING;break;
    }

    return returnString;
}

std::string Utilities::libraryTypeName(std::string _libType, bool _linkReady)
{
    std::string returnString = "";
    if (_linkReady)
    {
        returnString += "-l";
    }

    if(_libType == "LIB_FOUNDATION") returnString += "Foundation";
    else if(_libType == "LIB_OPEN_MAYA") returnString += "OpenMaya";
    else if(_libType == "LIB_OPEN_MAYA_UI") returnString += "OpenMayaUI";
    else if(_libType == "LIB_OPEN_MAYA_ANIM") returnString += "OpenMayaAnim";
    else if(_libType == "LIB_OPEN_MAYA_FX") returnString += "OpenMayaFX";
    else if(_libType == "LIB_OPEN_MAYA_RENDER") returnString += "OpenMayaRender";
    else if(_libType == "LIB_IMAGE") returnString += "Image";
    else if(_libType == "LIB_MOCAP") returnString += "mocap";
    else    returnString = NO_LIB_STRING;

    return returnString;
}

std::string Utilities::boolToString(bool _b)
{
    return _b ? "true" : "false";
}

bool Utilities::stringToBool(std::string _s)
{
    if (_s == "true" || _s == "True" || _s == "TRUE")
    {
        return true;
    }
    return false;
}

std::string Utilities::PLATFORM_FILE_PATH(std::string _path)
{
    std::string prefixString;
    prefixString.clear();

#ifdef DARWIN
    char prefix[FILENAME_MAX];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);

    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)prefix, FILENAME_MAX))
    {
        std::cerr<<"Could not get relative path of application bundle - exiting!"<<std::endl;
        exit(EXIT_FAILURE);
    }
    CFRelease(resourcesURL);
    prefixString = std::string(prefix);
#endif

#ifdef WIN32
    wchar_t buffer[FILENAME_MAX];
    _wgetcwd(buffer,FILENAME_MAX);
    std::wstring wstr(buffer);
    std::string winPath(wstr.begin(), wstr.end());
    std::replace(winPath.begin(), winPath.end(), '\\','/');
    prefixString = std::string(winPath);
#endif

    std::string returnString = "";
    if (!prefixString.empty())
    {
        returnString += prefixString;
        returnString += "/";
    }
    returnString += _path;

    return (returnString);
}

bool Utilities::pathExists(std::string _path)
{
    if(!boost::filesystem::exists(_path))
    {
        return false;
    }
    return true;
}

int Utilities::warnOfFolderReplacement(std::string _main, std::string _secondary)
{
    QMessageBox msgBox;
    msgBox.setText(QString(_main.c_str()));
    if (!_secondary.empty())
    {
        msgBox.setInformativeText(QString(_secondary.c_str()));
    }
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    return msgBox.exec();
}

WizardError::WIZARD_ERROR_CODE Utilities::safeCreateDirectory(std::string _path, bool _removeIfExists)
{
    boost::filesystem::path dir(_path);
    if(Utilities::pathExists(_path) && _removeIfExists)
    {
        boost::filesystem::remove_all(dir);
    }
    if (!boost::filesystem::create_directory(_path))
    {
       return WizardError::ERR_DIRECTORY_CREATION_FAILED;
    }
    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE Utilities::getContentsOfFile(std::string _path, QString *_contents)
{
    QFile fileBeingRead(_path.c_str());
    if (!fileBeingRead.exists())
    {
        return WizardError::ERR_FILE_DOES_NOT_EXIST;
    }
    fileBeingRead.open(QFile::ReadOnly);
    QString fileSource = fileBeingRead.readAll();
    fileBeingRead.close();

    *_contents = fileSource;

    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE Utilities::findInJsonObj(std::string _toFind, QJsonObject &_obj, std::string *_str)
{
    QJsonValue val = _obj.value(QString(_toFind.c_str()));
    QString tempStr = "";


    if (val.isString())
    {
        tempStr = val.toString();
    }

    if (tempStr.isEmpty())
    {
        return WizardError::ERR_VALUE_NOT_FOUND;
    }
    *_str = tempStr.toStdString();
    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE Utilities::findInJsonObj(std::string _toFind, QJsonObject &_obj, std::vector<std::string> *_str)
{
    std::vector<std::string> tempStore;
    tempStore.clear();

    QJsonValue val = _obj.value(QString(_toFind.c_str()));
    QJsonArray arr;

    if (val.isArray())
    {
        arr = val.toArray();

        int size = arr.size();
        for (int i = 0; i < size; i++)
        {
            tempStore.push_back(arr.at(i).toString().toStdString());
        }
    }

    if (tempStore.empty())
    {
        return WizardError::ERR_VALUE_NOT_FOUND;
    }

    // valid to write to vector so ensure the destination vector is empty
    _str->clear();
    int numLines = int(tempStore.size());
    for (int i =0; i <numLines; i++)
    {
        _str->push_back(tempStore.at(i));
    }
    return WizardError::NO_ERROR;
}

void Utilities::replaceInString(std::string *_string, std::string _pattern, std::string _replaceWith)
{
    while (_string->find(_pattern.c_str()) != std::string::npos)
    {
        _string->replace(_string->find(_pattern.c_str()),_pattern.length(),_replaceWith);
    }
}

void Utilities::replaceInStringVector(std::vector<std::string> *_vec, std::string _pattern, std::string _replaceWith)
{
    for (int i =0; i < int(_vec->size()); i++)
    {
        while (_vec->at(i).find(_pattern.c_str()) != std::string::npos)
        {
            _vec->at(i).replace(_vec->at(i).find(_pattern.c_str()),_pattern.length(),_replaceWith);
        }
    }
}

void Utilities::replaceInStringWithVector(std::string *_string, std::string _pattern, std::vector<std::string> _replaceWith)
{
    std::string temp = "";
    int size = int(_replaceWith.size());
    for (int i = 0; i <size; i++)
    {
        temp += std::string(_replaceWith.at(i) + "\n");
    }

    while (_string->find(_pattern.c_str()) != std::string::npos)
    {
        _string->replace(_string->find(_pattern.c_str()),_pattern.length(),temp.c_str());
    }
}

void Utilities::replaceInStringVectorWithVector(std::vector<std::string> *_vec, std::string _pattern,
                                     std::vector<std::string> _replaceWith)
{
    std::string temp = "";
    int size = int(_replaceWith.size());
    for (int i = 0; i <size; i++)
    {
        temp += std::string(_replaceWith.at(i) + "\n");
    }

    for (int i =0; i < int(_vec->size()); i++)
    {
        while (_vec->at(i).find(_pattern.c_str()) != std::string::npos)
        {
            _vec->at(i).replace(_vec->at(i).find(_pattern.c_str()),_pattern.length(),temp.c_str());
        }
    }
}

void Utilities::writeStringToVector(std::string _string, std::vector<std::string> *_dest)
{
    _dest->push_back(std::string(_string+"\n"));
}

void Utilities::writeVectorToVector(std::vector<std::string> _src, std::vector<std::string> *_dest)
{
    for (int i =0; i < int(_src.size()); i++)
    {
        _dest->push_back(std::string(_src.at(i) + "\n"));
    }
}

WizardError::WIZARD_ERROR_CODE Utilities::writeVectorToFile(std::string _filePath, std::vector<std::string> &_vec)
{
    std::ofstream file(_filePath.c_str());
    if (file.is_open())
    {
        for (int i = 0; i < int(_vec.size()); i++)
        {
            file << _vec.at(i);
        }
        file.close();
    }
    else
    {
        return WizardError::ERR_FILE_DOES_NOT_EXIST;
    }
    return WizardError::NO_ERROR;
}

std::string Utilities::argumentToStringRep(AddedArgument _arg)
{
    std::string returnStr = "\t";
    if (_arg._vType == "OBJECT")
    {
        returnStr += "static MObject";
    }
    else
    {
        returnStr += argumentTypeToTypeInString(_arg._type);
    }
    returnStr += " ";
    returnStr += std::string("m_" + _arg._name + ";");
    return returnStr;
}

std::string Utilities::argumentTypeToTypeInString(std::string _type)
{
    if (_type == "Boolean") return "bool";
    else if (_type == "Character") return "char";
    else if (_type == "Integer") return "int";
    else if (_type == "Double") return "double";
    else if (_type == "Float") return "float";
    else if (_type == "String") return "MString";
    else if (_type == "Vector") return "MVector";
    else if (_type == "Matrix") return "MMatrix";
    else return "__no_type__";
}

std::string Utilities::createObjectCppDecString(std::string _class, std::string _name)
{
    return std::string("MObject " + _class + "::m_" + _name + ";");
}

std::string Utilities::argTypeToMayaTypeString(std::string _type)
{
    if (_type == "Boolean") return "MSyntax::kBoolean";
    else if (_type == "Character") return "MSyntax::kString";
    else if (_type == "Integer") return "MSyntax::kUnsigned";
    else if (_type == "Double") return "MSyntax::kDouble";
    else if (_type == "Float") return "MSyntax::kDouble";
    else if (_type == "String") return "MSyntax::kString";
    else return "__no_type__";
}

std::string Utilities::nodePluginTypeToName(ND_TYPE _type)
{
    switch(_type)
    {
        case(ND_BASIC_NODE): return std::string("Depend Node"); break;
        case(ND_LOCATOR_NODE): return std::string("Locator Node"); break;
        case(ND_DEFORMER_NODE): return std::string("Deformer Node"); break;
        case(ND_MANIP_CONTAIN): return std::string("Manip Container Node"); break;
        case(ND_IK_SOLVER): return std::string("IK Solver Node"); break;
        case(ND_TRANSFORM): return std::string("Transform Node"); break;
        case(ND_HW_SHADER_NODE): return std::string("Hardware Shader Node"); break;
        case(ND_OBJECT): return std::string("Object Set Node"); break;
        case(ND_IMAGE_PLANE): return std::string("Image Plane Node"); break;
        case(ND_PARTICLE_ATTRIB_MAPPER): return std::string("Particle Attribute Mapper Node"); break;
        case(ND_CONSTRAINT): return std::string("Constraint Node"); break;
        case(ND_MANIP): return std::string("Manipulator Node"); break;
        default: return std::string("__no_type__"); break;
    }
}

ND_TYPE Utilities::nodePluginTypeFromName(std::string _name)
{
    if(_name == "Depend Node") return ND_BASIC_NODE;
    else if(_name == "Locator Node") return ND_LOCATOR_NODE;
    else if(_name == "Deformer Node") return ND_DEFORMER_NODE;
    else if(_name == "Manip Container Node") return ND_MANIP_CONTAIN;
    else if(_name == "IK Solver Node") return ND_IK_SOLVER;
    else if(_name == "Transform Node") return ND_TRANSFORM;
    else if(_name == "Hardware Shader Node") return ND_HW_SHADER_NODE;
    else if(_name == "Object Set Node") return ND_OBJECT;
    else if(_name == "Image Plane Node") return ND_IMAGE_PLANE;
    else if(_name == "Particle Attribute Mapper Node") return ND_PARTICLE_ATTRIB_MAPPER;
    else if(_name == "Constraint Node") return ND_CONSTRAINT;
    else if(_name == "Manipulator Node") return ND_MANIP;
    else return ND_NOTYPE;
}
