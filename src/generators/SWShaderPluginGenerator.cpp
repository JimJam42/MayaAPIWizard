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

#include "SWShaderPluginGenerator.h"

#include "Utilities.h"

SWShaderPluginGenerator::SWShaderPluginGenerator() : SourceGenerator(SW_SHADER_PLUGIN_EXTRA_ATTRIB_COUNT)
{

}

SWShaderPluginGenerator::~SWShaderPluginGenerator()
{

}

WizardError::WIZARD_ERROR_CODE SWShaderPluginGenerator::convertAndStoreAttributes()
{
    /* this function is unique to this generator and will be different (yet similar)
       on every generator type
       the order of attributes passed to this generator are
            ** Generic Default attribs **
            *****************************
            ** Plugin Specific Attribs **
            -Class name
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
    m_swName = getUseableAttribAt(currentInd);
    currentInd++;
    m_addObjs = Utilities::stringToBool(getUseableAttribAt(currentInd));
    currentInd++;

    // set the last of the generic common attributes
    status = storeSecondHalfOfDefaultAttributes(&currentInd);

    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE SWShaderPluginGenerator::generate()
{
    WizardError::WIZARD_ERROR_CODE status = WizardError::NO_ERROR;
    // first we need to generate the file structure
    createFileStructure(m_swName);
    // file structure created

    std::string mainSrcFileName = "main.cpp";
    std::string swHeaderName = m_swName + "Plugin.h";
    std::string swSrcName = m_swName + "Plugin.cpp";
    std::string swUIScriptName = "AE" + m_swName + "Template.mel";

    addSrcFile(mainSrcFileName);
    addSrcFile(swSrcName);
    addIncludeFile(swHeaderName);
    addScript(swUIScriptName);

    std::string mainSrcFilePath = std::string(getSrcPath() + "/" + mainSrcFileName);
    std::string swIncFilePath = std::string(getIncPath() + "/" + swHeaderName);
    std::string swSrcFilePath = std::string(getSrcPath() + "/" + swSrcName);
    std::string swUIScriptPath = std::string(getScriptPath() + "/" + swUIScriptName);

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

    QJsonParseError err;
    QJsonDocument doc;
    QJsonObject obj;

    //==================================================================================================
    // first we will write the main.cpp to init and deinit the plugin

    status = createDefaultMainSourceFile("swShaderMain",m_swName,swHeaderName,mainSrcFilePath);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    //==================================================================================================
    // next we will write the .h
    QString hContents;
    QString classContents;
    status = Utilities::getContentsOfFile(":/Framework/swShaderH",&hContents);
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

    status = replaceIncludeGuards(&grdFetch,m_swName,obj);
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

    // firstly though lets quickly replace the public attributes in the class def with the required ones
    status = Utilities::findInJsonObj("reqPubAttribs",obj,&temp);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    // now replace %_#_PUBLICATTRIBS_#_% in coreClassDef with this vector
    Utilities::replaceInStringVectorWithVector(&classFetch,"%_#_PUBLICATTRIBS_#_%",temp);

    temp.clear();

    // we can also replace %_#_INHERITFROM_#_% with the right class to inherit from
    Utilities::replaceInStringVector(&classFetch,"%_#_INHERITFROM_#_%","MPxNode");

    // now lets get the required functions for all node types
    status = Utilities::findInJsonObj("reqFns",obj,&temp);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    // now we need to write these to the fnFetch so we can use temp again
    Utilities::writeVectorToVector(temp,&fnFetch);
    temp.clear();

    Utilities::replaceInStringVectorWithVector(&classFetch,"%_#_FNSPECFN_#_%",fnFetch);
    fnFetch.clear();

    // now replace %_#_CLASSNAME_#_% within classFetch with the right name
    Utilities::replaceInStringVector(&classFetch,"%_#_CLASSNAME_#_%",m_swName);

    // now replace the private attributes/objects
    if (m_addObjs)
    {
        // here we simply need to igore the ARGUMENT types
        std::vector<std::string> tempArgs;
        tempArgs.clear();

        for (int i = 0; i < getNumExtraArguments(); i++)
        {
            if (getExtraArgumentAt(i)._vType != "ARGUMENT") // cannot accept arguments here
            {
                tempArgs.push_back(Utilities::argumentToStringRep(getExtraArgumentAt(i)));
            }
        }
        Utilities::replaceInStringVectorWithVector(&classFetch,"%_#_FNSPECATTRIBS_#_%",tempArgs);
        tempArgs.clear();
    }
    else
    {
        Utilities::replaceInStringVector(&classFetch,"%_#_FNSPECATTRIBS_#_%","");
    }

    Utilities::writeVectorToVector(classFetch,&toWrite);

    classFetch.clear();

    // add a line break to ensure formatting is correct
    toWrite.push_back("\n");

    Utilities::writeStringToVector(grdFetch.at(2),&toWrite);
    // now need to clear the guards
    grdFetch.clear();

    Utilities::writeVectorToFile(swIncFilePath, toWrite);

    toWrite.clear();

    //==================================================================================================
    // now to write the .cpp
    QString cppContents;

    status = Utilities::getContentsOfFile(":/Framework/swShaderCpp",&cppContents);
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
    Utilities::replaceInStringVector(&incFetch,"%_#_SWINCLUDE_#_%",swHeaderName);
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

    // now to do some replacing if necessary for the objects
    if (m_addObjs)
    {
        // here we simply need to only collect the OBJECT types
        std::vector<std::string> objs;
        objs.clear();

        for (int i = 0; i < getNumExtraArguments(); i++)
        {
            if (getExtraArgumentAt(i)._vType == "OBJECT") // cannot accept arguments here
            {
                objs.push_back(Utilities::createObjectCppDecString(m_swName, getExtraArgumentAt(i)._name));
            }
        }
        Utilities::replaceInStringVectorWithVector(&fnFetch,"%_#_OBJDEC_#_%",objs);
        objs.clear();

        Utilities::replaceInStringVectorWithVector(&fnFetch,"%_#_OBJINIT_#_%",objInitCode());
    }
    else
    {
        Utilities::replaceInStringVector(&fnFetch,"%_#_OBJDEC_#_%","");
        Utilities::replaceInStringVector(&fnFetch,"%_#_OBJINIT_#_%","");
    }

    // now replace all instances of the class name with the right value
    Utilities::replaceInStringVector(&fnFetch,"%_#_CLASSNAME_#_%",m_swName);

    Utilities::writeVectorToVector(fnFetch,&toWrite);

    fnFetch.clear();

    Utilities::writeVectorToFile(swSrcFilePath,toWrite);

    toWrite.clear();
    temp.clear();

    //==================================================================================================
    // finally we will write the .mel ui script

    status = createNodeScriptTemplateFile("swShaderUIScript",m_swName,swUIScriptPath);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    //==================================================================================================

    genMakefiles(m_swName);

    return WizardError::NO_ERROR;
}
