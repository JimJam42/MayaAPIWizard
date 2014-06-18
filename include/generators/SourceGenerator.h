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

#ifndef __SOURCE_GENERATOR_H__
#define __SOURCE_GENERATOR_H__

/// @file SourceGenerator.h
/// @brief Main generator class from which all inherit to generate source
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class SourceGenerator
/// @brief Base class for all generators, from which they all inherit.Contains standard and common
/// functions shared by all for generating framework and allows the generate page to ignore
/// what kind of generator is being called. Is a pure virtual function to force the inherited generators
/// to override the functions required to make plugin specific frameworks

#include <boost/filesystem.hpp>
#include <stack>

#include "Types.h"
#include "ErrorCodes.h"

#include "WizardPage.h"

// include for the reading of json files containing the framework
#include <QJsonDocument>
#include <QJsonObject>

#include <fstream>

#define MAX_NUM_LIBRARIES 8

#define COMMAND_PLUGIN_EXTRA_ATTRIB_COUNT 4
#define FILE_TRANS_EXTRA_ATTRIB_COUNT 6
#define NODE_PLUGIN_EXTRA_ATTRIB_COUNT 5
#define SW_SHADER_PLUGIN_EXTRA_ATTRIB_COUNT 2
#define HW_SHADER_PLUGIN_EXTRA_ATTRIB_COUNT 3
#define EMITTER_PLUGIN_EXTRA_ATTRIB_COUNT 3

/// @enum OBJ_TYPE
/// @brief The type of object being created
enum OBJ_TYPE
{
    OBJ_NOTYPE,
    UNIT_ATTR,
    COMP_ATTR,
    ENUM_ATTR,
    GENER_ATTR,
    MAT_ATTR,
    MESS_ATTR,
    NUM_ATTR
};

class SourceGenerator
{
public:
    /// @brief ctr
    /// @param [in] _extra int - extra number of attributes
    SourceGenerator(int _extra);
    /// @brief Virtual dtr
    virtual ~SourceGenerator();
    /// @brief Initialise common and default values for all generators
    void initGenerator();
    /// @brief Pass in the stack to be read
    /// @param [in] _stack std::stack<WizardPage*> - the stack containing all pages
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE setStack(std::stack<WizardPage*> &_stack);

    // virtual functions that will need to be overloaded
    // virtual function to simply return the type of plugin this generator will generate for
    /// @brief Pure virtual function to return the generation type - must over overridden
    /// @returns PLUGIN_TYPE
    virtual PLUGIN_TYPE genType() = 0;
    // virtual function to be overloaded to store the retrieved types from string to their correct locations in their correct types
    /// @brief Pure virtual function to convert attributes from strings to their correct format - must over overridden
    /// @returns WizardError::WIZARD_ERROR_CODE
    virtual WizardError::WIZARD_ERROR_CODE convertAndStoreAttributes() = 0;
    // virtual function that must be overriden to generate the files - called within run
    /// @brief Pure virtual function to generate framework for each plugin - must over overridden
    /// @returns WizardError::WIZARD_ERROR_CODE
    virtual WizardError::WIZARD_ERROR_CODE generate() = 0;
    /// @brief Runt he whole genration process from start to finish
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE run();

    // function to read the stack, stores it to the m_useableAttributes vector of strings
    /// @brief Recurse through the stack and read all pages, building up the collected information
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE readStack();

    // functions to generate makefiles
    /// @brief Create CMake file
    /// @param [in] _rootDirectory std::string - the root directory path
    /// @param [in] _projName std::string - the name of the project
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE createCMake(std::string _rootDirectory, std::string _projName);
    /// @brief Create Qt project
    /// @param [in] _rootDirectory std::string - the root directory path
    /// @param [in] _projName std::string - the name of the project
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE createQtProject(std::string _rootDirectory, std::string _projName);

    // functions to generate file structure - to be called in generate
    /// @brief Create the genric file structure required
    /// @param [in] _folderName std::string - name of root folder
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE createFileStructure(std::string _folderName);
    /// @brief Set the number of extra attribs
    /// @param [in] _count int - extra number
    void setExtraAttribCount(int _count);
    /// @brief Get the attribute at index
    /// @param [in] _index int - index to look at
    /// @returns std::string
    std::string getUseableAttribAt(int _index);

    // two functions to get the default attributes which will always exist in any plugin
    /// @brief Function to store the first lot of default attributes after plugin specifics
    /// @param [in] _currentIndex int* - the current index which can be modified
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE storeFirstHalfOfDefaultAttributes(int *_currentIndex);
    /// @brief Function to store the second lot of default attributes after plugin specifics
    /// @param [in] _currentIndex int* - the current index which can be modified
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE storeSecondHalfOfDefaultAttributes(int *_currentIndex);
    /// @brief Get the number of attributes recieved
    /// @returns int
    int numAttribsRecieved() {return m_totalAttributesRecieved;}
    // add either an include, src file or compiler flag name to the sotrage vectors
    /// @brief add an include file
    /// @param [in] _fileName std::string - script name to add
    void addIncludeFile(std::string _fileName);
    /// @brief add a source file
    /// @param [in] _fileName std::string - script name to add
    void addSrcFile(std::string _fileName);
    /// @brief add a script file
    /// @param [in] _script std::string - script name to add
    void addScript(std::string _script);
    // functions to retrieve single values from the vectors at the specified index
    /// @brief Get include file name at index
    /// @param [in] _index int - index to look at
    /// @returns std::string
    std::string getIncludeFileNameAt(int _index);
    /// @brief Get source file name at index
    /// @param [in] _index int - index to look at
    /// @returns std::string
    std::string getSrcFileNameAt(int _index);
    /// @brief Get script name at index
    /// @param [in] _index int - index to look at
    /// @returns std::string
    std::string getScriptNameAt(int _index);
    // functions to return the entire vectors
    /// @brief get vector of all include files
    /// @returns std::vector<std::string>
    std::vector<std::string> getIncludeFileNames() {return m_includeFiles;}
    /// @brief get vector of all source files
    /// @returns std::vector<std::string>
    std::vector<std::string> getSrcFileNames() {return m_srcFiles;}
    /// @brief get vector of all scripts
    /// @returns std::vector<std::string>
    std::vector<std::string> getScriptNames() {return m_scripts;}

    // setters to all default attributes
    /// @brief Set the maya directory
    /// @param [in] _dir std::string - the directory within which maya resides
    void setMayaDir(std::string _dir);
    /// @brief Set the plugin type
    /// @param [in] _type PLUGIN_TYPE - the type of plugin to set
    void setPluginType(PLUGIN_TYPE _type);
    /// @brief Set vendor name
    /// @param [in] _name std::string - vendor name
    void setVendorName(std::string _name);
    /// @brief Set plugin version
    /// @param [in] _version std::string - version
    void setPluginVersion(std::string _version);
    /// @brief Set required api version
    /// @param [in] _version std::string - version
    void setReqAPIVersion(std::string _version);
    /// @brief Set the libraries to link to
    /// @param [in] _lib std::vector<std::string> - vector of libraries
    void setLinkLibraries(std::vector<std::string> &_lib);
    /// @brief Set the create in directory
    /// @param [in] _dir std::string - directory to create in
    void setCreateInDir(std::string _dir);
    /// @brief Set to generate a qt project
    /// @param [in] _create bool - to creae or not
    void setGenQtProj(bool _create) {m_generateQtProject = _create;}
    /// @brief Set to generate a Cmake file
    /// @param [in] _create bool - to create or not
    void setGenCMake(bool _create) {m_generateCMake = _create;}
    /// @brief Set to make a new directory
    /// @param [in] _create bool - create or not
    void setMakeNewDir(bool _create) {m_makeNewDir = _create;}

    /// @brief Create the object set code
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE createObjectInitCode();

    // getters from all default attributes
    /// @brief get maya directory
    /// @returns std::string
    std::string getMayaDir() {return m_mayaDir;}
    /// @brief get plugin type
    /// @returns PLUGIN_TYPE
    PLUGIN_TYPE getPluginType() {return m_chosenPluginType;}
    /// @brief get vendor name
    /// @returns std::string
    std::string getVendorName() {return m_vendorName;}
    /// @brief get plugin version
    /// @returns std::string
    std::string getPluginVersion() {return m_pluginVersion;}
    /// @brief get required API version
    /// @returns std::string
    std::string getReqAPIVersion() {return m_requiredAPIVersion;}
    /// @brief Get vector of libraries to link
    /// @returns std::vector<std::string>
    std::vector<std::string> getLinkLibraries();
    /// @brief Get directory to create in
    /// @returns std::string
    std::string getCreateInDir() {return m_createInDir;}
    /// @brief Get if wanting to generate Qt project file
    /// @returns bool
    bool getGenQtProj() {return m_generateQtProject;}
    /// @brief Get if wanting to generate CMake file
    /// @returns bool
    bool getGenCMake() {return m_generateCMake;}
    /// @brief Get if wanting to make a new directory
    /// @returns bool
    bool getMakeNewDir() {return m_makeNewDir;}

    /// @brief Get include path for directory
    /// @returns std::string
    std::string getIncPath() {return m_incPath;}
    /// @brief Get source path for directory
    /// @returns std::string
    std::string getSrcPath() {return m_srcPath;}
    /// @brief Get obj path for directory
    /// @returns std::string
    std::string getObjPath() {return m_objPath;}
    /// @brief Get moc path for directory
    /// @returns std::string
    std::string getMocPath() {return m_mocPath;}
    /// @brief Get script path for directory
    /// @returns std::string
    std::string getScriptPath() {return m_scriptPath;}
    /// @brief Get root path for directory
    /// @returns std::string
    std::string getRootPath() {return m_rootPath;}
    /// @brief Get the vector containing the object init code
    /// @returns std::vector<std::string>
    std::vector<std::string> objInitCode() {return m_objectInitCode;}
    /// @brief Get number of extra arguments
    /// @returns int
    int getNumExtraArguments() {return m_numExtraArguments;}
    /// @brief get all extra arguments
    /// @returns std::vector<AddedArgument>*
    std::vector<AddedArgument>* getExtraArguments();
    /// @brief Get argument at specified index
    /// @param [in] _index int - index to look at
    /// @returns AddedArgument
    AddedArgument getExtraArgumentAt(int _index);
    /// @brief function to generate the appropriate make files
    /// @param [in] _projName std::string - the project name
    void genMakefiles(std::string _projName);

    // the following function can used when the main source file is a standard init template, with a single include to replace and the standard
    // parameters to replace
    //  %_#_VENDOR_#_%
    //  %_#_VERSION_#_%
    //  %_#_REQAPIVER_#_%
    //  %_#_CLASSNAME_#_%
    // if the plugin requires more form main.cpp it will ned ot be written manually
    // currently the two can use this are emitter and SW SHader due to the others requiring other replacements
    /// @brief Create a default main source file
    /// @param [in] _template std::string - resource file alias for file
    /// @param [in] _className std::string - name of the class
    /// @param [in] _include std::string - include file name
    /// @param [in] _writeTo std::string - file to write to
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE createDefaultMainSourceFile(std::string _template, std::string _className, std::string _include, std::string _writeTo);
    /// @brief Create a default script for a node plugin
    /// @param [in] _template std::string - resource file alias for file
    /// @param [in] _replaceWith std::string - replace with this string
    /// @param [in] _writeTo std::string - file to write to
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE createNodeScriptTemplateFile(std::string _template, std::string _replaceWith, std::string _writeTo);
    // function to replace the include guard names
    /// @brief Replace the pattern for include guards
    /// @param [out] _grdVec std::vector<std::string>* - vector to modify
    /// @param [in] _replaceWith std::string - replace with this string
    /// @param [in] _obj QJsonObject - obj to look into
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE replaceIncludeGuards(std::vector<std::string> *_grdVec, std::string _replaceWith, QJsonObject _obj);

private:
    /// @brief the number of pages created in the stack
    int m_totalNumPages;
    /// @brief The total number of attributes recieved from reading the pages
    int m_totalAttributesRecieved;
    /// @brief default number of attributes
    int m_defaultNumAttribs;
    /// @brief Numbr of extra attributes on top of the default number
    int m_extraNumAtribs;
    /// @brief number of attributes expected to come through
    int m_totalExpectedAttribs;
    /// @brief the number of extra arguments created
    int m_numExtraArguments;
    /// @brief the stack of pages created when going through the wizard
    std::stack<WizardPage*> m_pages;

    /// @brief all attributes collected from the stack of pages
    std::vector<std::string> *m_useableAttributes;
    /// @brief extra arguments added
    std::vector<AddedArgument> *m_extraArguments;

    // the following vectors will store include files, src files and compiler flags
    // these can then be added to make files and stored to the correct directories upon organisation if need be
    /// @brief vector of include files
    std::vector<std::string> m_includeFiles;
    /// @brief vector of source files
    std::vector<std::string> m_srcFiles;
    /// @brief vector of scripts
    std::vector<std::string> m_scripts;
    /// @brief Vector of strings to hold the initialisation code for added objects
    std::vector<std::string> m_objectInitCode;

    // some folder paths to mak things simpler
    /// @brief include path in the created directories
    std::string m_incPath;
    /// @brief source path in the created directories
    std::string m_srcPath;
    /// @brief obj path in the created directories
    std::string m_objPath;
    /// @brief moc path in the created directories
    std::string m_mocPath;
    /// @brief script path in the created directories
    std::string m_scriptPath;
    /// @brief Root path of the created directories
    std::string m_rootPath;

    // these attributes are standard for any plugin type and so can be stored here to then be accessed
    /// @brief Directory where Maya exists
    std::string m_mayaDir;
    /// @brief The chosen plugin type
    PLUGIN_TYPE m_chosenPluginType;
    /// @brief Vendor name for the plugin
    std::string m_vendorName;
    /// @brief The version of the plugin
    std::string m_pluginVersion;
    /// @brief Required API version for Maya
    std::string m_requiredAPIVersion;
    /// @brief Vector of libraries to link to
    std::vector <std::string> m_linkLibraries;
    /// @brief The directory to create in
    std::string m_createInDir;
    /// @brief Should we generate a Qt project file
    bool m_generateQtProject;
    /// @brief Should we generate a CMake file
    bool m_generateCMake;
    /// @brief Whether or not to make a new directory
    bool m_makeNewDir;

    // couple of functions to create the write strings for cmake lib declarations and their names
    /// @brief Create vector of lib defs ready to write to Cmake file
    /// @param [out] _libs std::vector<std::string> - vector to write to
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE createCmakeLibDefs(std::vector<std::string> *_libs);
    /// @brief Create vector of lib names ready to write to Cmake file
    /// @param [out] _name std::vector<std::string> - vector to write to
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE createCmakeLibNames(std::vector<std::string> *_names);


    // the following functions are call used for the build up of init code for any added objects
    /// @brief Convert unit type to Maya type
    /// @param [in] _type std::string - type to convert
    /// @returns std::string
    std::string objUnitStringTypeToMayaType(std::string _type);
    /// @brief Convert numeric type to Maya type
    /// @param [in] _type std::string - type to convert
    /// @returns std::string
    std::string objNumericStringTypeToMayaType(std::string _type);
    /// @brief Map a string representation of an object type to an enum representation
    /// @param [in] _type std::string - string rep type
    /// @returns OBJ_TYPE
    OBJ_TYPE mapObjStringTypeToType(std::string _type);
    /// @brief Create instance from OBJ type
    /// @param [in] _type OBJ_TYPE - the type to create
    /// @returns std::string
    std::string attrInstanceFromType(OBJ_TYPE _type);
    /// @brief Get the name of an instance of an objext type
    /// @param [in] _type OBJ_TYPE - the obj type
    /// @returns std::string
    std::string attrInstanceNameFromType(OBJ_TYPE _type);

    /// @brief create a default object set with no special conditions
    /// @param [in] _arg AddedArgument - the argument to set
    /// @param [in] _type OBJ_TYPE - the type of object
    /// @returns std::string
    std::string defaultObjSet(AddedArgument _arg, OBJ_TYPE _type);
    /// @brief create the code to set an object with the correct type
    /// @param [in] _arg AddedArgument - the argument to set
    /// @returns std::string
    std::string createSetCodeForObject(AddedArgument _arg);
};

#endif /* __SOURCE_GENERATOR_H__ */
