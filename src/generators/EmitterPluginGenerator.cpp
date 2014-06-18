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

#include "EmitterPluginGenerator.h"

#include "Utilities.h"

EmitterPluginGenerator::EmitterPluginGenerator() : SourceGenerator(EMITTER_PLUGIN_EXTRA_ATTRIB_COUNT)
{

}

EmitterPluginGenerator::~EmitterPluginGenerator()
{

}

WizardError::WIZARD_ERROR_CODE EmitterPluginGenerator::convertAndStoreAttributes()
{
    /* this function is unique to this generator and will be different (yet similar)
       on every generator type
       the order of attributes passed to this generator are
            ** Generic Default attribs **
            *****************************
            ** Plugin Specific Attribs **
            -Class name
            -Whether to add your own attributes
            -Whether to create a default emit function
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
    m_emitterName = getUseableAttribAt(currentInd);
    currentInd++;
    m_addObjs = Utilities::stringToBool(getUseableAttribAt(currentInd));
    currentInd++;
    m_createEmit = Utilities::stringToBool(getUseableAttribAt(currentInd));
    currentInd++;

    // set the last of the generic common attributes
    status = storeSecondHalfOfDefaultAttributes(&currentInd);

    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE EmitterPluginGenerator::generate()
{
    WizardError::WIZARD_ERROR_CODE status = WizardError::NO_ERROR;
    // first we need to generate the file structure
    createFileStructure(m_emitterName);
    // file structure created

    std::string mainSrcFileName = "main.cpp";
    std::string emitterHeaderName = m_emitterName + "Plugin.h";
    std::string emitterSrcName = m_emitterName + "Plugin.cpp";
    std::string emitterUIScriptName = "AE" + m_emitterName + "Template.mel";

    addSrcFile(mainSrcFileName);
    addSrcFile(emitterSrcName);
    addIncludeFile(emitterHeaderName);
    addScript(emitterUIScriptName);

    std::string mainSrcFilePath = std::string(getSrcPath() + "/" + mainSrcFileName);
    std::string emitterIncFilePath = std::string(getIncPath() + "/" + emitterHeaderName);
    std::string emitterSrcFilePath = std::string(getSrcPath() + "/" + emitterSrcName);
    std::string emitterUIScriptPath = std::string(getScriptPath() + "/" + emitterUIScriptName);

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
    std::vector<std::string> classForwardFetch;
    classForwardFetch.clear();
    std::vector<std::string> fnContFetch;
    fnContFetch.clear();

    QJsonParseError err;
    QJsonDocument doc;
    QJsonObject obj;

    //==================================================================================================
    // lets first write out the main.cpp
    status = createDefaultMainSourceFile("emitterMain",m_emitterName,emitterHeaderName,mainSrcFilePath);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    //==================================================================================================
    // next lets move onto the UI script as this is a nice simple one to do

    status = createNodeScriptTemplateFile("emitterUIScript",m_emitterName,emitterUIScriptPath);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    //==================================================================================================
    // now to write the header file for the plugin
    QString hContents;
    QString classContents;
    status = Utilities::getContentsOfFile(":/Framework/emitterH",&hContents);
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

    status = replaceIncludeGuards(&grdFetch,m_emitterName,obj);
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

    // lets now get the forward declarations of classes used within this header

    status = Utilities::findInJsonObj("forwardDecs",obj,&classForwardFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    Utilities::writeVectorToVector(classForwardFetch,&toWrite);

    // switch obj context back to the class stuff
    obj = classDoc.object();
    status = Utilities::findInJsonObj("classDef",obj,&classFetch);

    // lets just now replace %_#_CTRPARAMS_#_%, %_#_CREATORRETTYPE_#_% and %_#_CREATORPARAMS_#_% as we know here
    // they will be "" void and "" respectively
    Utilities::replaceInStringVector(&classFetch,"%_#_CTRPARAMS_#_%","");
    Utilities::replaceInStringVector(&classFetch,"%_#_CREATORRETTYPE_#_%","void");
    Utilities::replaceInStringVector(&classFetch,"%_#_CREATORPARAMS_#_%","");
    Utilities::replaceInStringVector(&classFetch,"%_#_INHERITFROM_#_%","MPxEmitterNode");

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

    status = Utilities::findInJsonObj("reqFns",obj,&temp);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    // now we need to write these to the fnFetch so we can use temp again
    Utilities::writeVectorToVector(temp,&fnFetch);
    temp.clear();

    // now check if we need to get the emit function
    if (m_createEmit)
    {
        status = Utilities::findInJsonObj("emitFn",obj,&temp);
        if (status != WizardError::NO_ERROR)
        {
            return status;
        }
        Utilities::writeVectorToVector(temp,&fnFetch);
    }

    Utilities::replaceInStringVectorWithVector(&classFetch,"%_#_FNSPECFN_#_%",fnFetch);
    fnFetch.clear();

    // now replace %_#_CLASSNAME_#_% within classFetch with the right name
    Utilities::replaceInStringVector(&classFetch,"%_#_CLASSNAME_#_%",m_emitterName);

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

    Utilities::writeVectorToFile(emitterIncFilePath, toWrite);

    toWrite.clear();

    //==================================================================================================
    // and finally the cpp for the plugin
    // this one will be a little bit different form the others as it will be filling out the contents
    // of two of the functions already when generating
    QString cppContents;

    status = Utilities::getContentsOfFile(":/Framework/emitterCpp",&cppContents);
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
    Utilities::replaceInStringVector(&incFetch,"%_#_EMITTERINCLUDE_#_%",emitterHeaderName);
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
                objs.push_back(Utilities::createObjectCppDecString(m_emitterName, getExtraArgumentAt(i)._name));
            }
        }
        Utilities::replaceInStringVectorWithVector(&fnFetch,"%_#_OBJDEC_#_%",objs);
        objs.clear();

        // we also now need to replace %_#_OBJINIT_#_% with the already calculated code for the objects
        Utilities::replaceInStringVectorWithVector(&fnFetch,"%_#_OBJINIT_#_%",objInitCode());
    }
    else
    {
        Utilities::replaceInStringVector(&fnFetch,"%_#_OBJDEC_#_%","");
        Utilities::replaceInStringVector(&fnFetch,"%_#_OBJINIT_#_%","");
    }

    // now check to see if we need the emit function
    // now check if we need to get the emit function
    if (m_createEmit)
    {
        status = Utilities::findInJsonObj("emitFn",obj,&temp);
        if (status != WizardError::NO_ERROR)
        {
            return status;
        }
        Utilities::writeVectorToVector(temp,&fnFetch);
    }

    // now replace all instances of the class name with the right value
    Utilities::replaceInStringVector(&fnFetch,"%_#_CLASSNAME_#_%",m_emitterName);

    // now we need to do some fetching of function content and simply replacing the parts with this
    status = Utilities::findInJsonObj("gwposcont",obj,&fnContFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    Utilities::replaceInStringVectorWithVector(&fnFetch,"%_#_GWPOSCONT_#_%",fnContFetch);
    fnContFetch.clear(); // clear this vector for the next one

    status = Utilities::findInJsonObj("gwposcontblock",obj,&fnContFetch);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    Utilities::replaceInStringVectorWithVector(&fnFetch,"%_#_GWPOSCONTBLOCK_#_%",fnContFetch);
    fnContFetch.clear();

    Utilities::writeVectorToVector(fnFetch,&toWrite);

    fnFetch.clear();

    Utilities::writeVectorToFile(emitterSrcFilePath,toWrite);

    toWrite.clear();
    temp.clear();

    //==================================================================================================

    genMakefiles(m_emitterName);

    return WizardError::NO_ERROR;
}
