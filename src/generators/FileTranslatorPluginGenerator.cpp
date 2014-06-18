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

#include "FileTranslatorPluginGenerator.h"

#include "Utilities.h"

FileTranslatorPluginGenerator::FileTranslatorPluginGenerator() : SourceGenerator(FILE_TRANS_EXTRA_ATTRIB_COUNT)
{

}

FileTranslatorPluginGenerator::~FileTranslatorPluginGenerator()
{

}

WizardError::WIZARD_ERROR_CODE FileTranslatorPluginGenerator::convertAndStoreAttributes()
{
    /* this function is unique to this generator and will be different (yet similar)
       on every generator type
       the order of attributes passed to this generator are
            ** Generic Default attribs **
            *****************************
            ** Plugin Specific Attribs **
            -Class name
            -File Translator name
            -UI Script name
            -Import or Export or Both
            -Default file extension
            -Whether to add your own attributes
            *****************************
            ** Generic Default attribs **
    */

    int currentInd = 0; // create a index count to keep track of where we are
    WizardError::WIZARD_ERROR_CODE status; // keep track of other functions status

    // set the first of the default common attributes
    status = storeFirstHalfOfDefaultAttributes(&currentInd);

    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    // now set the plugin specific attributes
    m_ftClassName = getUseableAttribAt(currentInd);
    currentInd++;
    m_ftName = getUseableAttribAt(currentInd);
    currentInd++;
    m_uiScriptName = getUseableAttribAt(currentInd);
    currentInd++;
    m_impExp = getUseableAttribAt(currentInd);
    currentInd++;
    m_defaultFileExtension = getUseableAttribAt(currentInd);
    currentInd++;
    m_addPrivAttribs = Utilities::stringToBool(getUseableAttribAt(currentInd));
    currentInd++;

    // set the last of the generic common attributes
    status = storeSecondHalfOfDefaultAttributes(&currentInd);

    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE FileTranslatorPluginGenerator::generate()
{
    WizardError::WIZARD_ERROR_CODE status = WizardError::NO_ERROR;
    // first we need to generate the file structure
    createFileStructure(m_ftClassName);
    // file structure created

    // lets now create the files needed
    std::string mainSrcFileName = "main.cpp";
    std::string ftHeaderName = m_ftClassName + "Plugin.h";
    std::string ftSrcName = m_ftClassName + "Plugin.cpp";
    std::string ftUIScriptName = m_uiScriptName + ".mel";

    addIncludeFile(ftHeaderName);
    addSrcFile(mainSrcFileName);
    addSrcFile(ftSrcName);
    addScript(ftUIScriptName);

    std::string mainSrcFilePath = std::string(getSrcPath() + "/" + mainSrcFileName);
    std::string ftIncFilePath = std::string(getIncPath() + "/" + ftHeaderName);
    std::string ftSrcFilePath = std::string(getSrcPath() + "/" + ftSrcName);
    std::string ftUIScriptPath = std::string(getScriptPath() + "/" + ftUIScriptName);

    std::vector<std::string> toWrite;
    toWrite.clear();

    std::vector<std::string> fnFetch;
    fnFetch.clear();
    std::vector<std::string> incFetch;
    incFetch.clear();
    std::vector<std::string> grdFetch;
    grdFetch.clear();
    std::vector<std::string> noticeFetch;
    noticeFetch.clear();
    std::vector<std::string> classFetch;
    classFetch.clear();
    std::vector<std::string> scriptFetch;
    scriptFetch.clear();

    //==================================================================================================
    // first we will write the main.cpp to init and deinit the plugin
    QString mainSrcContents;
    status = Utilities::getContentsOfFile(":/Framework/fileTransMain",&mainSrcContents);
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
    // in this string, the variable to be replaced is %_#_FTINCLUDE_#_% which is the name of the include file for the new class file
    Utilities::replaceInStringVector(&incFetch,std::string("%_#_FTINCLUDE_#_%"), ftHeaderName);
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
    // 5 things to replace in this function
    //  %_#_VENDOR_#_%
    //  %_#_VERSION_#_%
    //  %_#_REQAPIVER_#_%
    //  %_#_FTNAME_#_%
    //  %_#_FTCLASSNAME_#_%
    //  %_#_UISCRIPTNAME_#_%
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_VENDOR_#_%"), getVendorName());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_VERSION_#_%"), getPluginVersion());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_REQAPIVER_#_%"), getReqAPIVersion());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_FTNAME_#_%"), m_ftName);
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_FTCLASSNAME_#_%"), m_ftClassName);
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_UISCRIPTNAME_#_%"), m_uiScriptName);
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
    //  %_#_FTNAME_#_%
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_FTNAME_#_%"), m_ftName);
    // ******************************************************************

    Utilities::writeVectorToVector(fnFetch,&toWrite);
    // now clear the noticeFetch ready for next time
    fnFetch.clear();

    Utilities::writeVectorToFile(mainSrcFilePath,toWrite);

    // clear the write vector to start again
    toWrite.clear();

    //==================================================================================================
    // now we will write out the .h header file for the plugin

    // now get information for the header file for this command
    QString hContents;
    QString classContents;
    status = Utilities::getContentsOfFile(":/Framework/fileTransH",&hContents);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    status = Utilities::getContentsOfFile(":/Framework/coreClassDef",&classContents);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    doc = QJsonDocument::fromJson(hContents.toUtf8(), &err);
    QJsonDocument classDoc = QJsonDocument::fromJson(classContents.toUtf8(),&err);

    if (!doc.isObject() || !classDoc.isObject())
    {
        return WizardError::ERR_GENERATOR_QUIT;
    }

    obj = doc.object();

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

    // set to the class obj to get the guards
    obj = classDoc.object();

    status = replaceIncludeGuards(&grdFetch,m_ftClassName,obj);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    // add the first two guards only, the last element will go at the end of the header
    Utilities::writeStringToVector(grdFetch.at(0),&toWrite);
    Utilities::writeStringToVector(grdFetch.at(1),&toWrite);

    // add a line break to ensure formatting is correct
    toWrite.push_back("\n");

    // switch the object back to the header now
    obj = doc.object();

    status = Utilities::findInJsonObj("includes",obj,&incFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    Utilities::writeVectorToVector(incFetch,&toWrite);
    // clear the incFetch ready for next time
    incFetch.clear();

    // add a line break to ensure formatting is correct
    toWrite.push_back("\n");

    // switch obj context back to the class stuff
    obj = classDoc.object();
    status = Utilities::findInJsonObj("classDef",obj,&classFetch);

    // lets just now replace %_#_CTRPARAMS_#_%, %_#_CREATORRETTYPE_#_% and %_#_CREATORPARAMS_#_% as we know here
    // they will be "" void and "" respectively
    Utilities::replaceInStringVector(&classFetch,"%_#_CTRPARAMS_#_%","");
    Utilities::replaceInStringVector(&classFetch,"%_#_CREATORRETTYPE_#_%","void");
    Utilities::replaceInStringVector(&classFetch,"%_#_CREATORPARAMS_#_%","");

    // now need to format string to replace variables with correct values
    // as some of the attributes to be replaced will come from the json file for the command header
    // I first need to read that in
    // so first lets switch the obj context back
    obj = doc.object();
    // need a temp vector to build up a vector if chosen options
    std::vector<std::string> temp;
    temp.clear();
    status = Utilities::findInJsonObj("reqFns",obj,&temp);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    // need to replace some things in the required fns
    // %_#_WRITEMETHODBOOL_#_%
    // %_#_READMETHODBOOL_#_%
    // %_#_DEFEXT_#_%
    if (m_impExp == "import")
    {
        Utilities::replaceInStringVector(&temp,"%_#_WRITEMETHODBOOL_#_%","false");
        Utilities::replaceInStringVector(&temp,"%_#_READMETHODBOOL_#_%","true");
    }
    else if (m_impExp == "export")
    {
        Utilities::replaceInStringVector(&temp,"%_#_WRITEMETHODBOOL_#_%","true");
        Utilities::replaceInStringVector(&temp,"%_#_READMETHODBOOL_#_%","false");
    }
    else // this will default to this is anything has gone wrong anywhere
    {
        Utilities::replaceInStringVector(&temp,"%_#_WRITEMETHODBOOL_#_%","true");
        Utilities::replaceInStringVector(&temp,"%_#_READMETHODBOOL_#_%","true");
    }
    Utilities::replaceInStringVector(&temp,"%_#_DEFEXT_#_%",m_defaultFileExtension);
    // write the temp to the fnFetch vector to build up all required functions
    Utilities::writeVectorToVector(temp,&fnFetch);

    temp.clear();
    // now lets write out the function decs for if it is export or import
    if (m_impExp == "import" || m_impExp == "importexport")
    {
        status = Utilities::findInJsonObj("importFns",obj,&temp);
        if (status != WizardError::NO_ERROR)
        {
            return status;
        }
        Utilities::writeVectorToVector(temp,&fnFetch);
        temp.clear();
    }
    if (m_impExp == "export" || m_impExp == "importexport")
    {
        status = Utilities::findInJsonObj("exportFns",obj,&temp);
        if (status != WizardError::NO_ERROR)
        {
            return status;
        }
        Utilities::writeVectorToVector(temp,&fnFetch);
        temp.clear();
    }
    // ******************************************************************

    // now I need to replace the attributes within the classDef
    //  %_#_CLASSNAME_#_%
    //  %_#_INHERITFROM_#_%
    //  %_#_FNSPECFN_#_%
    //  %_#_FNSPECATTRIBS_#_%
    Utilities::replaceInStringVector(&classFetch,"%_#_CLASSNAME_#_%",m_ftClassName);
    Utilities::replaceInStringVector(&classFetch,"%_#_INHERITFROM_#_%","MPxFileTranslator");
    Utilities::replaceInStringVectorWithVector(&classFetch, "%_#_FNSPECFN_#_%",fnFetch);
    if (m_addPrivAttribs)
    {
        // build up a vector of the arguments as member attributes
        std::vector<std::string> tempArgs;
        tempArgs.clear();

        for (int i = 0; i < getNumExtraArguments(); i++)
        {
            if (getExtraArgumentAt(i)._vType == "MEMBER")
            {
                tempArgs.push_back(Utilities::argumentToStringRep(getExtraArgumentAt(i)));
            }
        }
        Utilities::replaceInStringVectorWithVector(&classFetch,"%_#_FNSPECATTRIBS_#_%",tempArgs);
    }
    else
    {
        Utilities::replaceInStringVector(&classFetch,"%_#_FNSPECATTRIBS_#_%","");
    }
    Utilities::replaceInStringVector(&classFetch,"%_#_PUBLICATTRIBS_#_%","");
    // ******************************************************************

    Utilities::writeVectorToVector(classFetch,&toWrite);

    classFetch.clear();

    // add a line break to ensure formatting is correct
    toWrite.push_back("\n");

    Utilities::writeStringToVector(grdFetch.at(2),&toWrite);
    // now need to clear the guards
    grdFetch.clear();

    Utilities::writeVectorToFile(ftIncFilePath, toWrite);

    toWrite.clear();

    //==================================================================================================
    // next is the .cpp source file for the plugin

    QString cppContents;

    status = Utilities::getContentsOfFile(":/Framework/fileTransCpp",&cppContents);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    doc = QJsonDocument::fromJson(cppContents.toUtf8(), &err);
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

    status = Utilities::findInJsonObj("includes",obj,&incFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    // need to replace the attributes
    Utilities::replaceInStringVector(&incFetch,"%_#_FTINCLUDE_#_%",ftHeaderName);
    Utilities::writeVectorToVector(incFetch,&toWrite);
    incFetch.clear();

    toWrite.push_back("\n");

    fnFetch.clear();
    temp.clear();

    status = Utilities::findInJsonObj("reqFns",obj,&temp);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    Utilities::writeVectorToVector(temp,&fnFetch);

    temp.clear();

    if (m_impExp == "import" || m_impExp == "importexport")
    {
        Utilities::findInJsonObj("importFns",obj,&temp);
        if (status != WizardError::NO_ERROR)
        {
            return status;
        }
        Utilities::writeVectorToVector(temp,&fnFetch);
    }
    if (m_impExp == "export" || m_impExp == "importexport")
    {
        Utilities::findInJsonObj("exportFns",obj,&temp);
        if (status != WizardError::NO_ERROR)
        {
            return status;
        }
        Utilities::writeVectorToVector(temp,&fnFetch);
    }

    temp.clear();
    // now replace all instances of the class name with the right value
    Utilities::replaceInStringVector(&fnFetch,"%_#_CLASSNAME_#_%",m_ftClassName);

    Utilities::writeVectorToVector(fnFetch,&toWrite);

    Utilities::writeVectorToFile(ftSrcFilePath,toWrite);

    toWrite.clear();
    temp.clear();

    //==================================================================================================
    // finally is the .mel script for the plugin

    QString scriptContents;
    status = Utilities::getContentsOfFile(":/Framework/fileTransUIScript",&scriptContents);
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
    // need to replace %_#_UISCRIPTNAME_#_% in this string
    Utilities::replaceInStringVector(&scriptFetch,std::string("%_#_UISCRIPTNAME_#_%"),m_uiScriptName);
    // ******************************************************************

    Utilities::writeVectorToVector(scriptFetch,&toWrite);
    scriptFetch.clear();

    Utilities::writeVectorToFile(ftUIScriptPath,toWrite);

    // clear the write vector to start again
    toWrite.clear();

    //==================================================================================================

    genMakefiles(m_ftClassName);

    return WizardError::NO_ERROR;
}
