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

#include "SourceGenerator.h"

#include "Utilities.h"

// include to allow parsing of input strings
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

#include <iostream>

SourceGenerator::SourceGenerator(int _extra)
{
    m_useableAttributes = NULL;
    initGenerator();
    setExtraAttribCount(_extra);
}

SourceGenerator::~SourceGenerator()
{
    if (m_useableAttributes != NULL)
    {
        m_useableAttributes->clear();
        delete m_useableAttributes;
    }
}

void SourceGenerator::initGenerator()
{
    m_totalAttributesRecieved = 0;
    m_defaultNumAttribs = 17; // includes all libraries

    m_useableAttributes = new std::vector<std::string>;
    m_useableAttributes->clear();
    m_extraArguments = new std::vector<AddedArgument>;
    m_extraArguments->clear();

    m_objectInitCode.clear();

    // clear all name vectors
    m_includeFiles.clear();
    m_srcFiles.clear();
    m_scripts.clear();

    m_incPath = "";
    m_srcPath = "";
    m_objPath = "";
    m_mocPath = "";
    m_scriptPath = "";
    m_rootPath= "";
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::setStack(std::stack<WizardPage *> &_stack)
{
    if (!_stack.empty())
    {
        m_pages = _stack;
        m_totalNumPages = m_pages.size();
        return WizardError::NO_ERROR;
    }
    return WizardError::ERR_EMPTY_STACK;
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::run()
{
    // read the stack to gain all the required information
    WizardError::WIZARD_ERROR_CODE status = readStack();
    if(status != WizardError::NO_ERROR)
    {
        return status;
    }
    // now lets create the strings needed for any objects added just to make this quicker and easier
    status = createObjectInitCode();
    if(status != WizardError::NO_ERROR)
    {
        return status;
    }
    // next store the attribute values to their correct locations to be used
    status = convertAndStoreAttributes();
    if(status != WizardError::NO_ERROR)
    {
        return status;
    }
    // now call the genration function to generate the files
    status = generate();
    if(status != WizardError::NO_ERROR)
    {
        return status;
    }
    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::readStack()
{
    if (!m_pages.empty())
    {
        // ensure the vector of attributes is empty so this is not overwriting anything
        m_useableAttributes->clear();
        std::string returnString = "";
        // what will happen here is we will read through the attributes
        // if any extra arguments exist they will be removed from the main list and stored in their own one
        // a test of the total together then will be conducted
        // so lets clear thje extra arguments vector just in case some data has crept in
        m_extraArguments->clear();
        m_numExtraArguments = 0;

        bool readingArguments = false;
        int argumentStageCount = 0;
        AddedArgument tempArg;
        tempArg._name = "";
        tempArg._shortName = "";
        tempArg._type = "";

        while (!m_pages.empty())
        {
            // loop through and read the top page
            returnString = m_pages.top()->getAttributes();
            // now parse the string to the delimiter ; and store within the vector in order
            // the specific plugin type generator will know this order and can then store these values to the correct type in the correct order
            boost::char_separator<char> delim(ATTRIB_DELIM);
            boost::tokenizer< boost::char_separator<char> > token(returnString,delim);
            BOOST_FOREACH (const std::string& attrib, token)
            {
                if (!attrib.empty()) // remove any cheeky empty attribs that have snuck in
                {
                    if (attrib == "#_#")
                    {
                        readingArguments ^= true;
                    }
                    else
                    {
                        if (readingArguments)
                        {
                            switch(argumentStageCount)
                            {
                                case(0):
                                {
                                    tempArg._vType = attrib;
                                    argumentStageCount++;
                                }break;
                                case(1):
                                {
                                    tempArg._type = attrib;
                                    argumentStageCount++;
                                }break;
                                case(2):
                                {
                                    tempArg._name = attrib;
                                    argumentStageCount++;
                                }break;
                                case(3):
                                {
                                    tempArg._shortName = attrib;
                                    argumentStageCount++;
                                }break;
                                case(4):
                                {
                                    // this is when the vector will read "--" so this argument has finished so push it back
                                    m_extraArguments->push_back(tempArg);
                                    m_numExtraArguments++;
                                    argumentStageCount=0;
                                }break;
                            }
                        }
                        else
                        {
                            m_useableAttributes->push_back(attrib);
                        }
                    }
                }
            }
            // then pop off
            m_pages.pop();
            // repeat until all pages have been read
        }
        m_totalAttributesRecieved = m_useableAttributes->size();

        if (m_totalAttributesRecieved == m_totalExpectedAttribs)
        {
            return WizardError::NO_ERROR;
        }
        return WizardError::ERR_UNEXPECTED_ATTRIB_COUNT;
    }
    return WizardError::ERR_NULL_POINTER;
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::createCMake(std::string _rootDirectory, std::string _projName)
{
    std::vector<std::string> cmakeFetch;
    cmakeFetch.clear();
    std::vector<std::string> noticeFetch;
    noticeFetch.clear();

    std::vector<std::string> toWrite;
    toWrite.clear();

    QString cmakeContents;
    WizardError::WIZARD_ERROR_CODE status = Utilities::getContentsOfFile(":/Framework/cmake",&cmakeContents);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(cmakeContents.toUtf8(), &err);
    QJsonObject obj;

    if(doc.isObject())
    {
        obj = doc.object();
    }
    else
    {
        return WizardError::ERR_GENERATOR_QUIT;
    }

    status = Utilities::findInJsonObj("genNotice",obj,&noticeFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    Utilities::writeVectorToVector(noticeFetch,&toWrite);

    noticeFetch.clear();

    toWrite.push_back("\n");

    status = Utilities::findInJsonObj("cmake",obj,&cmakeFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    // now need to replace a couple of quick easy things
    //  %_#_PROJNAME_#_%
    //  %_#_MAYALOC_#_%
    Utilities::replaceInStringVector(&cmakeFetch,"%_#_PROJNAME_#_%",_projName);
    Utilities::replaceInStringVector(&cmakeFetch,"%_#_MAYALOC_#_%",getMayaDir());

    // now we need to build up the libraries
    // we need both the libraries full dec and just the cmake name
    std::vector<std::string> libDecs;
    libDecs.clear();
    std::vector<std::string> libCmakeNames;
    libCmakeNames.clear();

    status = createCmakeLibDefs(&libDecs);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    status = createCmakeLibNames(&libCmakeNames);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    // now replace the last two things in the CMAKE template
    // %_#_LIBRARYDEFS_#_%
    Utilities::replaceInStringVectorWithVector(&cmakeFetch,"%_#_LIBRARYDEFS_#_%",libDecs);
    // %_#_CMAKELIBNAMES_#_%
    Utilities::replaceInStringVectorWithVector(&cmakeFetch,"%_#_CMAKELIBNAMES_#_%",libCmakeNames);

    Utilities::writeVectorToVector(cmakeFetch,&toWrite);

    // create CMakeLists.txt
    std::string path = std::string(_rootDirectory + "/CMakeLists.txt");

    std::string buildDir = _rootDirectory + "/build";

    if (!boost::filesystem::create_directory(buildDir))
    {
       return WizardError::ERR_DIRECTORY_CREATION_FAILED;
    }

    Utilities::writeVectorToFile(path.c_str(),toWrite);

    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::createQtProject(std::string _rootDirectory, std::string _projName)
{
    std::vector<std::string> qtprojFetch;
    qtprojFetch.clear();
    std::vector<std::string> noticeFetch;
    noticeFetch.clear();

    std::vector<std::string> toWrite;
    toWrite.clear();

    QString qtprojContents;
    WizardError::WIZARD_ERROR_CODE status = Utilities::getContentsOfFile(":/Framework/qtproj",&qtprojContents);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(qtprojContents.toUtf8(), &err);
    QJsonObject obj;

    if(doc.isObject())
    {
        obj = doc.object();
    }
    else
    {
        return WizardError::ERR_GENERATOR_QUIT;
    }

    status = Utilities::findInJsonObj("genNotice",obj,&noticeFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    Utilities::writeVectorToVector(noticeFetch,&toWrite);

    toWrite.push_back("\n");

    status = Utilities::findInJsonObj("qtproj",obj,&qtprojFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    // now need to replace the attributes
    //  %_#_MAYALOC_#_%
    //  %_#_PLUGINNAME_#_%
    //  %_#_SCRIPTFILES_#_%
    //  %_#_SRCFILES_#_%
    //  %_#_INCFILES_#_%
    //  %_#_MAYALIBRARIES_#_%
    Utilities::replaceInStringVector(&qtprojFetch,"%_#_MAYALOC_#_%",getMayaDir());
    Utilities::replaceInStringVector(&qtprojFetch,"%_#_PLUGINNAME_#_%",_projName);
    // need to create a temporary vector for the src files, can then be use for include files
    std::vector<std::string> tempFiles;
    tempFiles.clear();
    int numSrcFiles = int(m_srcFiles.size());
    int numIncFiles = int(m_includeFiles.size());
    int numScripts = int(m_scripts.size());

    std::string file = "";

    for (int i = 0; i< numSrcFiles; i++)
    {
        file = std::string("\t$$SRC_DIR/" + m_srcFiles.at(i));
        if (i != numSrcFiles-1)
        {
            file += " \\";
        }
        tempFiles.push_back(file);
    }
    Utilities::replaceInStringVectorWithVector(&qtprojFetch,"%_#_SRCFILES_#_%",tempFiles);
    file = "";
    tempFiles.clear();

    for (int i = 0; i< numIncFiles; i++)
    {
        file = std::string("\t$$INC_DIR/" + m_includeFiles.at(i));
        if (i != numIncFiles-1)
        {
            file += " \\";
        }
        tempFiles.push_back(file);
    }
    Utilities::replaceInStringVectorWithVector(&qtprojFetch,"%_#_INCFILES_#_%",tempFiles);
    file = "";
    tempFiles.clear();

    for (int i = 0; i< int(m_linkLibraries.size()); i++)
    {
        file = std::string("\t" + m_linkLibraries.at(i));
        if (i != int(m_linkLibraries.size())-1)
        {
            file += " \\";
        }
        tempFiles.push_back(file);
    }
    Utilities::replaceInStringVectorWithVector(&qtprojFetch,"%_#_MAYALIBRARIES_#_%",tempFiles);
    file = "";
    tempFiles.clear();

    // if any script files have been added and created, add them to the .pro
    if (numScripts > 0)
    {
        for (int i = 0; i< numScripts; i++)
        {
            file = std::string("\t$$SCRIPT_DIR/" + m_scripts.at(i));
            if (i != numScripts-1)
            {
                file += " \\";
            }
            tempFiles.push_back(file);
        }
        Utilities::replaceInStringVectorWithVector(&qtprojFetch,"%_#_SCRIPTFILES_#_%",tempFiles);
        file = "";
        tempFiles.clear();
    }
    else
    {
        Utilities::replaceInStringVector(&qtprojFetch,"%_#_SCRIPTFILES_#_%","");
    }
    // ******************************************************

    Utilities::writeVectorToVector(qtprojFetch,&toWrite);

    //create .pro
    std::string path = std::string(_rootDirectory + "/" + _projName + "Plugin.pro");

    Utilities::writeVectorToFile(path.c_str(),toWrite);

    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::createFileStructure(std::string _folderName)
{
    std::string creationPath = getCreateInDir();
    if (getMakeNewDir())
    {
        creationPath += std::string("/" + _folderName + "Plugin_" + getPluginVersion());
        boost::filesystem::path direc(creationPath);
        if (Utilities::pathExists(creationPath))
        {
            int ret = Utilities::warnOfFolderReplacement("This plugin folder already exists!",
                                                        "Do you want to overwrite the existing plugin?");

            switch(ret)
            {
                case(QMessageBox::Ok) : boost::filesystem::remove_all(direc); break;
                default: return WizardError::ERR_GENERATOR_QUIT; break;
            }
        }
        if (!boost::filesystem::create_directory(direc))
        {
           return WizardError::ERR_DIRECTORY_CREATION_FAILED;
        }
    }

    m_rootPath = creationPath;
    m_incPath = m_rootPath + "/include";
    m_srcPath = m_rootPath + "/src";
    m_objPath = m_rootPath + "/obj";
    m_mocPath = m_rootPath + "/moc";
    m_scriptPath = m_rootPath + "/scripts";

    bool removeExistingFolders = false;

    if (Utilities::pathExists(m_incPath) || Utilities::pathExists(m_srcPath) ||
            Utilities::pathExists(m_objPath) || Utilities::pathExists(m_mocPath) || Utilities::pathExists(m_scriptPath))
    {
        int ret = Utilities::warnOfFolderReplacement("It has been detected that a plugin may already exist in this location!",
                                                    "If you save to this location without creating a directory, old data may be lost. Do you want to proceed?");

        switch(ret)
        {
            case(QMessageBox::Ok) : removeExistingFolders = true; break;
            default: return WizardError::ERR_GENERATOR_QUIT; break;
        }
    }

    WizardError::WIZARD_ERROR_CODE status = WizardError::NO_ERROR;

    status = Utilities::safeCreateDirectory(m_incPath, removeExistingFolders);
    if (status != WizardError::NO_ERROR) return status;

    status = Utilities::safeCreateDirectory(m_srcPath, removeExistingFolders);
    if (status != WizardError::NO_ERROR) return status;

    status = Utilities::safeCreateDirectory(m_objPath, removeExistingFolders);
    if (status != WizardError::NO_ERROR) return status;

    status = Utilities::safeCreateDirectory(m_mocPath, removeExistingFolders);
    if (status != WizardError::NO_ERROR) return status;

    status = Utilities::safeCreateDirectory(m_scriptPath, removeExistingFolders);
    if (status != WizardError::NO_ERROR) return status;

    return WizardError::NO_ERROR;
}

void SourceGenerator::setExtraAttribCount(int _count)
{
    m_extraNumAtribs = _count;
    m_totalExpectedAttribs = m_defaultNumAttribs + m_extraNumAtribs;
}

std::string SourceGenerator::getUseableAttribAt(int _index)
{
    if (_index >= 0 && _index < m_totalAttributesRecieved)
    {
        return m_useableAttributes->at(_index);
    }
    return "_not_found_";
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::storeFirstHalfOfDefaultAttributes(int *_currentIndex)
{
    /*
     Order of attributes:
            -Write directory
            -Generate Qt Project
            -Generate Makefile
            -Make a new directory
            -Libraries (8 in total)
     */
    int indTemp = *_currentIndex; // take a copy so we dont mess up the original

    setCreateInDir(getUseableAttribAt(indTemp));
    indTemp++;
    setGenQtProj(Utilities::stringToBool(getUseableAttribAt(indTemp)));
    indTemp++;
    setGenCMake(Utilities::stringToBool(getUseableAttribAt(indTemp)));
    indTemp++;
    setMakeNewDir(Utilities::stringToBool(getUseableAttribAt(indTemp)));
    indTemp++;

    // now add the libraries
    std::vector<std::string> libs;
    std::string temp = "";
    libs.clear();
    for (int i = 0; i < MAX_NUM_LIBRARIES; i++)
    {
        temp = getUseableAttribAt(indTemp);
        if (temp != NO_LIB_STRING)
        {
            libs.push_back(temp);
        }
        indTemp++;
    }

    setLinkLibraries(libs);

    // now set the index back
    *_currentIndex = indTemp;
    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::storeSecondHalfOfDefaultAttributes(int *_currentIndex)
{
    /*
     Order of attributes:
            -Maya directory
            -Plugin type
            -Vendor name
            -Plugin version
            -Required API Version
     */
    int indTemp = *_currentIndex; // take a copy so we dont mess up the original

    setMayaDir(getUseableAttribAt(indTemp));
    indTemp++;
    setPluginType(Utilities::pluginTypeFromName(getUseableAttribAt(indTemp)));
    indTemp++;
    setVendorName(getUseableAttribAt(indTemp));
    indTemp++;
    setPluginVersion(getUseableAttribAt(indTemp));
    indTemp++;
    setReqAPIVersion(getUseableAttribAt(indTemp));

    // now set the index back
    *_currentIndex = indTemp;
    return WizardError::NO_ERROR;
}

void SourceGenerator::addIncludeFile(std::string _fileName)
{
    if (!_fileName.empty())
    {
        m_includeFiles.push_back(_fileName);
    }
}

void SourceGenerator::addSrcFile(std::string _fileName)
{
    if (!_fileName.empty())
    {
        m_srcFiles.push_back(_fileName);
    }
}

void SourceGenerator::addScript(std::string _script)
{
    if (!_script.empty())
    {
        m_scripts.push_back(_script);
    }
}

std::string SourceGenerator::getIncludeFileNameAt(int _index)
{
    if (_index >= 0 && _index < int(m_includeFiles.size()))
    {
        return m_includeFiles.at(_index);
    }
    return "_not_found_";
}

std::string SourceGenerator::getSrcFileNameAt(int _index)
{
    if (_index >= 0 && _index < int(m_srcFiles.size()))
    {
        return m_srcFiles.at(_index);
    }
    return "_not_found_";
}

void SourceGenerator::setMayaDir(std::string _dir)
{
    if (!_dir.empty())
    {
        m_mayaDir = _dir;
    }
}

void SourceGenerator::setPluginType(PLUGIN_TYPE _type)
{
    m_chosenPluginType = _type;
}

void SourceGenerator::setVendorName(std::string _name)
{
    if (!_name.empty())
    {
        m_vendorName= _name;
    }
}

void SourceGenerator::setPluginVersion(std::string _version)
{
    if (!_version.empty())
    {
        m_pluginVersion = _version;
    }
}

void SourceGenerator::setReqAPIVersion(std::string _version)
{
    if (!_version.empty())
    {
        m_requiredAPIVersion = _version;
    }
}

void SourceGenerator::setLinkLibraries(std::vector<std::string> &_lib)
{
    int numLibsPassed = _lib.size();
    // first make sure the link libraries are empty
    m_linkLibraries.clear();
    // now add each one to the vector
    for (int i = 0; i < numLibsPassed; i++)
    {
        m_linkLibraries.push_back(_lib.at(i));
    }
}

void SourceGenerator::setCreateInDir(std::string _dir)
{
    if (!_dir.empty())
    {
        m_createInDir = _dir;
    }
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::createObjectInitCode()
{
    // lets first start by making sure the vector we are going to store this too is clear
    m_objectInitCode.clear();
    // the first thing we need to do is scoot through all extra arguments and find all of the objects
    // we will store these to a seperate local vector to make things simpler
    std::vector<AddedArgument> allObjs;
    allObjs.clear();

    for (int i = 0; i < m_numExtraArguments; i++)
    {
        if (m_extraArguments->at(i)._vType == "OBJECT")
        {
            allObjs.push_back(m_extraArguments->at(i));
        }
    }

    // ok no we need to loop through this local vector and find out what type of object they are
    // we then need to create an instance of that type so we can create the object
    // we only want one of each kind so once one if two are found, it will only create once
    // to do this simply run through the local vector and get there type, check if this has already been stored
    // if it has then just dnt store it, else store it
    std::vector<OBJ_TYPE> typesToWrite;
    typesToWrite.clear();

    bool exists = false;

    for (int j = 0; j< int(allObjs.size()); j++)
    {
        exists = false;
        OBJ_TYPE temp = mapObjStringTypeToType(allObjs.at(j)._type);
        // now loop through the typesToWrite list to check it doesnt already exist
        for (int k = 0; k < int(typesToWrite.size()); k++)
        {
            if (typesToWrite.at(k) == temp)
            {
                exists = true;
            }
        }

        if (!exists)
        {
            typesToWrite.push_back(temp);
        }
    }

    // now we have all the types to create an instance for, create the instances and store them to the member vector
    for (int ii = 0; ii < int(typesToWrite.size()); ii++)
    {
        m_objectInitCode.push_back(std::string("\t" + attrInstanceFromType(typesToWrite.at(ii)) + "\n"));
    }

    // now we will add a line break just to make it a bit more readable
    m_objectInitCode.push_back("\n");

    // now simply must loop through all of the objects and create a simple instantiation of them
    // this can easily be done from their added argument data
    for (int jj = 0; jj < int(allObjs.size()); jj++)
    {
        m_objectInitCode.push_back(createSetCodeForObject(allObjs.at(jj)));
    }

    // just add another line break for a bit of formatting
    m_objectInitCode.push_back("\n");

    return WizardError::NO_ERROR;
}

std::vector<std::string> SourceGenerator::getLinkLibraries()
{
    if (m_linkLibraries.size() == MAX_NUM_LIBRARIES)
    {
        return m_linkLibraries;
    }
    std::vector<std::string> nullVec;
    nullVec.clear();
    return nullVec;
}

std::vector<AddedArgument>* SourceGenerator::getExtraArguments()
{
    return m_extraArguments;
}

AddedArgument SourceGenerator::getExtraArgumentAt(int _index)
{
    if (_index > -1 && _index < m_numExtraArguments)
    {
        return m_extraArguments->at(_index);
    }
    AddedArgument nullArg;
    return nullArg;
}

void SourceGenerator::genMakefiles(std::string _projName)
{
    if (getGenCMake())
    {
        createCMake(getRootPath(),_projName);
    }

    if (getGenQtProj())
    {
        createQtProject(getRootPath(),_projName);
    }
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::createDefaultMainSourceFile(std::string _template, std::string _className, std::string _include, std::string _writeTo)
{
    std::vector<std::string> toWrite;
    toWrite.clear();
    std::vector<std::string> incFetch;
    incFetch.clear();
    std::vector<std::string> noticeFetch;
    noticeFetch.clear();
    std::vector<std::string> fnFetch;
    fnFetch.clear();

    QString mainSrcContents;
    WizardError::WIZARD_ERROR_CODE status = Utilities::getContentsOfFile(std::string(":/Framework/"+_template),&mainSrcContents);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(mainSrcContents.toUtf8(), &err);
    QJsonObject obj;

    if(doc.isObject())
    {
        obj = doc.object();
    }
    else
    {
        return WizardError::ERR_GENERATOR_QUIT;
    }

    status = Utilities::findInJsonObj("genNotice",obj,&noticeFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    Utilities::writeVectorToVector(noticeFetch,&toWrite);
    // now clear the noticeFetch ready for next time
    noticeFetch.clear();

    // add a line break to ensure formatting is correct
    toWrite.push_back("\n");

    status = Utilities::findInJsonObj("includes",obj,&incFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    // now need to format string to replace variables with correct values
    // in this string, the variable to be replaced is %_#_INCLUDE_#_% which is the name of the include file for the new class file
    Utilities::replaceInStringVector(&incFetch,std::string("%_#_INCLUDE_#_%"), _include);
    // ******************************************************************

    Utilities::writeVectorToVector(incFetch,&toWrite);
    // now clear the noticeFetch ready for next time
    incFetch.clear();

    // add a line break to ensure formatting is correct
    toWrite.push_back("\n");

    status = Utilities::findInJsonObj("fn_initPlug",obj,&fnFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    // now need to format string to replace variables with correct values
    // 4 things to replace in this function
    //  %_#_VENDOR_#_%
    //  %_#_VERSION_#_%
    //  %_#_REQAPIVER_#_%
    //  %_#_CLASSNAME_#_%
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_VENDOR_#_%"), getVendorName());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_VERSION_#_%"), getPluginVersion());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_REQAPIVER_#_%"), getReqAPIVersion());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_CLASSNAME_#_%"), _className);
    // ******************************************************************

    Utilities::writeVectorToVector(fnFetch,&toWrite);
    // now clear the noticeFetch ready for next time
    fnFetch.clear();

    // add a line break to ensure formatting is correct
    toWrite.push_back("\n");

    status = Utilities::findInJsonObj("fn_uninitPlug",obj,&fnFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    // now need to format string to replace variables with correct values
    // 1 to replace here
    //  %_#_CLASSNAME_#_%
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_CLASSNAME_#_%"), _className);
    // ******************************************************************

    Utilities::writeVectorToVector(fnFetch,&toWrite);
    // now clear the noticeFetch ready for next time
    fnFetch.clear();

    Utilities::writeVectorToFile(_writeTo,toWrite);

    // clear the write vector to start again
    toWrite.clear();

    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::createNodeScriptTemplateFile(std::string _template, std::string _replaceWith, std::string _writeTo)
{
    WizardError::WIZARD_ERROR_CODE status = WizardError::NO_ERROR;

    std::vector<std::string> toWrite;
    toWrite.clear();
    std::vector<std::string> noticeFetch;
    noticeFetch.clear();
    std::vector<std::string> scriptFetch;
    scriptFetch.clear();

    QJsonParseError err;
    QJsonDocument doc;
    QJsonObject obj;

    QString scriptContents;
    status = Utilities::getContentsOfFile(std::string(":/Framework/"+_template),&scriptContents);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    doc = QJsonDocument::fromJson(scriptContents.toUtf8(), &err);

    if (!doc.isObject())
    {
        return WizardError::ERR_GENERATOR_QUIT;
    }

    obj = doc.object();

    noticeFetch.clear();

    status = Utilities::findInJsonObj("genNotice",obj,&noticeFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    Utilities::writeVectorToVector(noticeFetch,&toWrite);

    status = Utilities::findInJsonObj("uiFN",obj,&scriptFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    // need to replace %_#_TEMPLATENAME_#_% in this string
    Utilities::replaceInStringVector(&scriptFetch,std::string("%_#_TEMPLATENAME_#_%"),_replaceWith);
    // ******************************************************************

    Utilities::writeVectorToVector(scriptFetch,&toWrite);
    scriptFetch.clear();

    Utilities::writeVectorToFile(_writeTo,toWrite);
    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::replaceIncludeGuards(std::vector<std::string> *_grdVec, std::string _replaceWith, QJsonObject _obj)
{
    WizardError::WIZARD_ERROR_CODE status = Utilities::findInJsonObj("guards",_obj,_grdVec);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    // replace the guards attributes for the file name
    //  %_#_FILENAMECAPS_#_%
    QString uppName = _replaceWith.c_str();
    Utilities::replaceInStringVector(_grdVec,"%_#_FILENAMECAPS_#_%",uppName.toUpper().toStdString());
    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::createCmakeLibDefs(std::vector<std::string> *_libs)
{
    /*
     Ok here we need to create the following structure for each library
        SET(MAYA_FOUNDATION_LIB MAYA_FOUNDATION_LIB-NOTFOUND)
        FIND_LIBRARY(MAYA_FOUNDATION_LIB Foundation
            PATHS
            ${MAYA_LIB_DIR}
            DOC "The directory where the Foundation library resides"
            NO_DEFAULT_PATH)
     */

    _libs->clear();
    std::vector<std::string> temp;
    temp.clear();

    for (int i = 0; i< int(m_linkLibraries.size()); i++)
    {
        std::string oldLibName = m_linkLibraries.at(i);
        // need to remove the -l at the beginning of each library name as this is on by default
        std::string tempN = "";
        for (int j =2; j < int(oldLibName.size()); j++)
        {
            tempN += oldLibName.at(j);
        }

        // ok now create the above structure
        QString qTemp(tempN.c_str());
        QString libDec = "SET(MAYA_";
        libDec += qTemp.toUpper();
        libDec += "_LIB MAYA_";
        libDec +=qTemp.toUpper();
        libDec += "_LIB-NOTFOUND)\n";
        libDec += "FIND_LIBRARY(MAYA_";
        libDec += qTemp.toUpper();
        libDec += "_LIB ";
        libDec += qTemp;
        libDec += "\n\tPATHS\n\t${MAYA_LIB_DIR}\n\tDOC \"The directory where the ";
        libDec += qTemp;
        libDec += " library resides\"\n\tNO_DEFAULT_PATH)\n";
        temp.push_back(libDec.toStdString());
    }

    for (int k = 0; k < int(temp.size()); k++)
    {
        _libs->push_back(temp.at(k));
    }

    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE SourceGenerator::createCmakeLibNames(std::vector<std::string> *_names)
{
    // simply need to store each library in the following format here
    // ${MAYA_FOUNDATION_LIB}
    std::vector<std::string> cmakeNames;
    cmakeNames.clear();

    _names->clear();

    for (int i = 0; i< int(m_linkLibraries.size()); i++)
    {
        std::string oldLibName = m_linkLibraries.at(i);
        // need to remove the -l at the beginning of each library name as this is on by default
        std::string temp = "";
        for (int j =2; j < int(oldLibName.size()); j++)
        {
            temp += oldLibName.at(j);
        }

        QString qTemp(temp.c_str());
        QString cName = "\t${MAYA_";
        cName += qTemp.toUpper();
        cName += "_LIB} ";

        cmakeNames.push_back(cName.toStdString());

    }

    for (int k = 0; k < int(cmakeNames.size()); k++)
    {
        _names->push_back(cmakeNames.at(k));
    }
    return WizardError::NO_ERROR;
}

std::string SourceGenerator::objUnitStringTypeToMayaType(std::string _type)
{
    if (_type == "Angle Unit") return "MFnUnitAttribute::kAngle";
    else if (_type == "Distance Unit") return "MFnUnitAttribute::kDistance";
    else if (_type == "Time Unit") return "MFnUnitAttribute::kTime";
    else if (_type == "Last Value Unit") return "MFnUnitAttribute::kLast";
    else return "__not_found__";
}

std::string SourceGenerator::objNumericStringTypeToMayaType(std::string _type)
{
    if (_type == "Boolean Numeric") return "MFnNumericData::kBoolean";
    else if (_type == "One Byte Numeric") return "MFnNumericData::kByte";
    else if (_type == "One Char Numeric") return "MFnNumericData::kChar";
    else if (_type == "One Short Numeric") return "MFnNumericData::kShort";
    else if (_type == "Two Shorts Numeric") return "MFnNumericData::k2Short";
    else if (_type == "Three Shorts Numeric") return "MFnNumericData::k3Short";
    else if (_type == "One Long Numeric") return "MFnNumericData::kLong";
    else if (_type == "One Int Numeric") return "MFnNumericData::kInt";
    else if (_type == "Two Longs Numeric") return "MFnNumericData::k2Long";
    else if (_type == "Two Ints Numeric") return "MFnNumericData::k2Int";
    else if (_type == "Three Longs Numeric") return "MFnNumericData::k3Long";
    else if (_type == "Three Ints Numeric") return "MFnNumericData::k3Int";
    else if (_type == "One Float Numeric") return "MFnNumericData::kFloat";
    else if (_type == "Two Floats Numeric") return "MFnNumericData::k2Float";
    else if (_type == "Three Floats Numeric") return "MFnNumericData::k3Float";
    else if (_type == "One Double Numeric") return "MFnNumericData::kDouble";
    else if (_type == "Two Doubles Numeric") return "MFnNumericData::k2Double";
    else if (_type == "Three Doubles Numeric") return "MFnNumericData::k3Double";
    else if (_type == "Four Doubles Numeric") return "MFnNumericData::k4Double";
    else if (_type == "Address Numeric") return "MFnNumericData::kAddr";
    else if (_type == "Last Value Numeric") return "MFnNumericData::kLast";
    else return "__not_found__";
}

OBJ_TYPE SourceGenerator::mapObjStringTypeToType(std::string _type)
{
    if (_type == "Angle Unit") return UNIT_ATTR;
    else if (_type == "Distance Unit") return UNIT_ATTR;
    else if (_type == "Time Unit") return UNIT_ATTR;
    else if (_type == "Last Value Unit") return UNIT_ATTR;
    else if (_type == "Compound Attribute") return COMP_ATTR;
    else if (_type == "Enum Attribute") return ENUM_ATTR;
    else if (_type == "Generic Attribute") return GENER_ATTR;
    else if (_type == "Matrix Attribute") return MAT_ATTR;
    else if (_type == "Message Attribute") return MESS_ATTR;
    else if (_type == "Boolean Numeric") return NUM_ATTR;
    else if (_type == "One Byte Numeric") return NUM_ATTR;
    else if (_type == "One Char Numeric") return NUM_ATTR;
    else if (_type == "One Short Numeric") return NUM_ATTR;
    else if (_type == "Two Shorts Numeric") return NUM_ATTR;
    else if (_type == "Three Shorts Numeric") return NUM_ATTR;
    else if (_type == "One Long Numeric") return NUM_ATTR;
    else if (_type == "One Int Numeric") return NUM_ATTR;
    else if (_type == "Two Longs Numeric") return NUM_ATTR;
    else if (_type == "Two Ints Numeric") return NUM_ATTR;
    else if (_type == "Three Longs Numeric") return NUM_ATTR;
    else if (_type == "Three Ints Numeric") return NUM_ATTR;
    else if (_type == "One Float Numeric") return NUM_ATTR;
    else if (_type == "Two Floats Numeric") return NUM_ATTR;
    else if (_type == "Three Floats Numeric") return NUM_ATTR;
    else if (_type == "One Double Numeric") return NUM_ATTR;
    else if (_type == "Two Doubles Numeric") return NUM_ATTR;
    else if (_type == "Three Doubles Numeric") return NUM_ATTR;
    else if (_type == "Four Doubles Numeric") return NUM_ATTR;
    else if (_type == "Address Numeric") return NUM_ATTR;
    else if (_type == "Last Value Numeric") return NUM_ATTR;
    else return OBJ_NOTYPE;
}

std::string SourceGenerator::attrInstanceFromType(OBJ_TYPE _type)
{
    switch(_type)
    {
        // all of these will be set keyable by default except for num_attr which does contain this function
        case(UNIT_ATTR): return std::string("MFnUnitAttribute " +  attrInstanceNameFromType(UNIT_ATTR) +";\n\t" + attrInstanceNameFromType(UNIT_ATTR) + ".setKeyable(true);"); break;
        case(COMP_ATTR): return std::string("MFnCompoundAttribute " + attrInstanceNameFromType(COMP_ATTR) + ";\n\t" + attrInstanceNameFromType(COMP_ATTR) + ".setKeyable(true);"); break;
        case(ENUM_ATTR): return std::string("MFnEnumAttribute " + attrInstanceNameFromType(ENUM_ATTR) +";\n\t" + attrInstanceNameFromType(ENUM_ATTR) + ".setKeyable(true);"); break;
        case(GENER_ATTR): return std::string("MFnGenericAttribute " + attrInstanceNameFromType(GENER_ATTR) + ";\n\t" + attrInstanceNameFromType(GENER_ATTR) + ".setKeyable(true);"); break;
        case(MAT_ATTR): return std::string("MFnMatrixAttribute " + attrInstanceNameFromType(MAT_ATTR) +";\n\t" + attrInstanceNameFromType(MAT_ATTR) + ".setKeyable(true);"); break;
        case(MESS_ATTR): return std::string("MFnMessageAttribute " + attrInstanceNameFromType(MESS_ATTR) + ";\n\t" + attrInstanceNameFromType(MESS_ATTR) + ".setKeyable(true);"); break;
        case(NUM_ATTR): return std::string("MFnNumericData " + attrInstanceNameFromType(NUM_ATTR) + ";"); break;
        default: return "__no_instance__"; break;
    }
}

std::string SourceGenerator::attrInstanceNameFromType(OBJ_TYPE _type)
{
    switch(_type)
    {
        case(UNIT_ATTR): return "fnUn"; break;
        case(COMP_ATTR): return "fnCmp"; break;
        case(ENUM_ATTR): return "fnEn"; break;
        case(GENER_ATTR): return "fnGen"; break;
        case(MAT_ATTR): return "fnMat"; break;
        case(MESS_ATTR): return "fnMess"; break;
        case(NUM_ATTR): return "fnNum"; break;
        default: return "__no_instance__"; break;
    }
}

std::string SourceGenerator::defaultObjSet(AddedArgument _arg, OBJ_TYPE _type)
{
    std::string returnString = "";
    returnString += "\tm_";
    returnString += _arg._name;
    returnString += " = ";
    returnString += attrInstanceNameFromType(_type);
    returnString += ".create(\"";
    returnString += _arg._name;
    returnString += "\", \"";
    returnString += _arg._shortName;
    returnString += "\");";
    returnString += "\n\t// do any initialising and adding of the object here\n";
    return returnString;
}

std::string SourceGenerator::createSetCodeForObject(AddedArgument _arg)
{
    // only objects should ever be passed in but lets just do a quick test to make sure
    if (_arg._vType == "OBJECT")
    {
        std::string returnString = "";
        // what we return depends on the type of object, so lets first get that and then we can switch on it
        // will assume for all of these that there is an instance of MStatus called status for checking
        OBJ_TYPE type = mapObjStringTypeToType(_arg._type);

        switch(type)
        {
            case(UNIT_ATTR):
            {
                returnString += "\tm_";
                returnString += _arg._name;
                returnString += " = ";
                returnString += attrInstanceNameFromType(UNIT_ATTR);
                returnString += ".create(\"";
                returnString += _arg._name;
                returnString += "\", \"";
                returnString += _arg._shortName;
                returnString += "\", ";
                returnString += objUnitStringTypeToMayaType(_arg._type);
                returnString += ");";
                returnString += "\n\t// do any initialising and adding of the object here\n";
            }break;
            case(COMP_ATTR):
            {
                returnString = defaultObjSet(_arg,COMP_ATTR);
            }break;
            case(ENUM_ATTR):
            {
                returnString = defaultObjSet(_arg,ENUM_ATTR);
            }break;
            case(GENER_ATTR):
            {
                returnString = defaultObjSet(_arg,GENER_ATTR);
            }break;
            case(MAT_ATTR):
            {
                returnString = defaultObjSet(_arg,MAT_ATTR);
            }break;
            case(MESS_ATTR):
            {
                returnString = defaultObjSet(_arg,MESS_ATTR);
            }break;
            case(NUM_ATTR):
            {
                returnString += "\tm_";
                returnString += _arg._name;
                returnString += " = ";
                returnString += attrInstanceNameFromType(NUM_ATTR);
                returnString += ".create(";
                returnString += objNumericStringTypeToMayaType(_arg._type);
                returnString += ");";
                returnString += "\n\t// do any initialising and adding of the object here\n";
            }break;
            default: returnString = "__invalid_object__"; break;
        }

        return returnString;
    }
    else
    {
        return "__not_object__";
    }
}
