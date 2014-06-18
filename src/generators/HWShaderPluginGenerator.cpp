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

#include "HWShaderPluginGenerator.h"

#include "Utilities.h"

HWShaderPluginGenerator::HWShaderPluginGenerator() : SourceGenerator(HW_SHADER_PLUGIN_EXTRA_ATTRIB_COUNT)
{

}

HWShaderPluginGenerator::~HWShaderPluginGenerator()
{

}

WizardError::WIZARD_ERROR_CODE HWShaderPluginGenerator::convertAndStoreAttributes()
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
    m_hwName = getUseableAttribAt(currentInd);
    currentInd++;
    m_hwNameOR = getUseableAttribAt(currentInd);
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

WizardError::WIZARD_ERROR_CODE HWShaderPluginGenerator::generate()
{
    WizardError::WIZARD_ERROR_CODE status = WizardError::NO_ERROR;
    // first we need to generate the file structure
    createFileStructure(m_hwName);
    // file structure created

    std::string mainSrcFileName = "main.cpp";
    std::string hwHeaderName = m_hwName + "Plugin.h";
    std::string hwSrcName = m_hwName + "Plugin.cpp";
    std::string hwORHeaderName = m_hwNameOR + "Plugin.h";
    std::string hwORSrcName = m_hwNameOR + "Plugin.cpp";
    std::string hwUIScriptName = "AE" + m_hwName + "Template.mel";

    addSrcFile(mainSrcFileName);
    addSrcFile(hwSrcName);
    addIncludeFile(hwHeaderName);
    addSrcFile(hwORSrcName);
    addIncludeFile(hwORHeaderName);
    addScript(hwUIScriptName);

    std::string mainSrcFilePath = std::string(getSrcPath() + "/" + mainSrcFileName);
    std::string hwIncFilePath = std::string(getIncPath() + "/" + hwHeaderName);
    std::string hwSrcFilePath = std::string(getSrcPath() + "/" + hwSrcName);
    std::string hwORIncFilePath = std::string(getIncPath() + "/" + hwORHeaderName);
    std::string hwORSrcFilePath = std::string(getSrcPath() + "/" + hwORSrcName);
    std::string hwUIScriptPath = std::string(getScriptPath() + "/" + hwUIScriptName);

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

    //==================================================================================================
    // first we will write the main.cpp to init and deinit the plugin
    QString mainSrcContents;
    status = Utilities::getContentsOfFile(":/Framework/hwShaderMain",&mainSrcContents);
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
    // in this string, the variable to be replaced is %_#_SWINCLUDE_#_% which is the name of the include file for the new class file
    Utilities::replaceInStringVector(&incFetch,std::string("%_#_HWINCLUDE_#_%"), hwHeaderName);
    Utilities::replaceInStringVector(&incFetch,std::string("%_#_HWOVERRIDEINCLUDE_#_%"), hwORHeaderName);
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
    //  %_#_CLASSNAME_#_%
    //  %_#_OVERRIDECLASSNAME_#_%
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_VENDOR_#_%"), getVendorName());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_VERSION_#_%"), getPluginVersion());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_REQAPIVER_#_%"), getReqAPIVersion());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_CLASSNAME_#_%"), m_hwName);
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_OVERRIDECLASSNAME_#_%"), m_hwNameOR);
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
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_CLASSNAME_#_%"), m_hwName);
    // ******************************************************************

    Utilities::writeVectorToVector(fnFetch,&toWrite);
    // now clear the noticeFetch ready for next time
    fnFetch.clear();

    Utilities::writeVectorToFile(mainSrcFilePath,toWrite);

    // clear the write vector to start again
    toWrite.clear();

    //==================================================================================================
    // next we will write out the UI script file, just to get it done and out of the way

    status = createNodeScriptTemplateFile("hwShaderUIScript",m_hwName,hwUIScriptPath);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    //==================================================================================================
    // now to start on the source, lets first do the header file for the main plugin

    QString hContents;
    QString classContents;
    status = Utilities::getContentsOfFile(":/Framework/hwShaderH",&hContents);
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

    status = replaceIncludeGuards(&grdFetch,m_hwName,obj);
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

    Utilities::replaceInStringVector(&classFetch,"%_#_INHERITFROM_#_%","MPxHardwareShader");

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

    Utilities::replaceInStringVector(&classFetch,"%_#_CLASSNAME_#_%",m_hwName);

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

    Utilities::writeVectorToFile(hwIncFilePath,toWrite);

    // clear the write vector to start again
    toWrite.clear();

    //==================================================================================================
    // now the cpp for the main plugin

    QString cppContents;

    status = Utilities::getContentsOfFile(":/Framework/hwShaderCpp",&cppContents);
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
    Utilities::replaceInStringVector(&incFetch,"%_#_HWINCLUDE_#_%",hwHeaderName);
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
                objs.push_back(Utilities::createObjectCppDecString(m_hwName, getExtraArgumentAt(i)._name));
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
    Utilities::replaceInStringVector(&fnFetch,"%_#_CLASSNAME_#_%",m_hwName);

    Utilities::writeVectorToVector(fnFetch,&toWrite);

    fnFetch.clear();

    Utilities::writeVectorToFile(hwSrcFilePath,toWrite);

    // clear the write vector to start again
    toWrite.clear();
    temp.clear();

    //==================================================================================================
    // next is the header for the override

    // first need to clear the old used stuff to make sure no corrupt data
    incFetch.clear();
    fnFetch.clear();
    classFetch.clear();
    noticeFetch.clear();
    hContents = "";

    status = Utilities::getContentsOfFile(":/Framework/hwShaderOverrideH",&hContents);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    doc = QJsonDocument::fromJson(hContents.toUtf8(), &err);
    classDoc = QJsonDocument::fromJson(classContents.toUtf8(),&err);

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

    status = replaceIncludeGuards(&grdFetch,m_hwNameOR,obj);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    // add the first two guards only, the last element will go at the end of the header
    Utilities::writeStringToVector(grdFetch.at(0),&toWrite);
    Utilities::writeStringToVector(grdFetch.at(1),&toWrite);

    // add a line break to ensure formatting is correct
    toWrite.push_back("\n");

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
    // they will be "const MObject& obj" MHWRender::MPxShaderOverride and "const MObject& obj" respectively
    Utilities::replaceInStringVector(&classFetch,"%_#_CTRPARAMS_#_%","const MObject &_obj");
    Utilities::replaceInStringVector(&classFetch,"%_#_CREATORRETTYPE_#_%","MHWRender::MPxShaderOverride");
    Utilities::replaceInStringVector(&classFetch,"%_#_CREATORPARAMS_#_%","const MObject &_obj");

    obj = doc.object();
    // need a temp vector to build up a vector if chosen options
    temp.clear();

    Utilities::replaceInStringVector(&classFetch,"%_#_PUBLICATTRIBS_#_%","");

    Utilities::replaceInStringVector(&classFetch,"%_#_INHERITFROM_#_%","MHWRender::MPxShaderOverride");

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

    Utilities::replaceInStringVector(&classFetch,"%_#_CLASSNAME_#_%",m_hwNameOR);

    Utilities::replaceInStringVector(&classFetch,"%_#_FNSPECATTRIBS_#_%","");

    Utilities::writeVectorToVector(classFetch,&toWrite);

    classFetch.clear();

    // add a line break to ensure formatting is correct
    toWrite.push_back("\n");

    Utilities::writeStringToVector(grdFetch.at(2),&toWrite);
    // now need to clear the guards
    grdFetch.clear();

    Utilities::writeVectorToFile(hwORIncFilePath,toWrite);

    // clear the write vector to start again
    toWrite.clear();

    //==================================================================================================
    // and finally the cpp for the override

    // first need to clear the old used stuff to make sure no corrupt data
    incFetch.clear();
    fnFetch.clear();
    noticeFetch.clear();
    cppContents = "";

    status = Utilities::getContentsOfFile(":/Framework/hwShaderOverrideCpp",&cppContents);
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
    Utilities::replaceInStringVector(&incFetch,"%_#_HWINCLUDE_#_%",hwHeaderName);
    Utilities::replaceInStringVector(&incFetch,"%_#_HWOVERRIDEINCLUDE_#_%",hwORHeaderName);
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

    // now replace all instances of the class name with the right value
    Utilities::replaceInStringVector(&fnFetch,"%_#_CLASSNAME_#_%",m_hwNameOR);

    Utilities::writeVectorToVector(fnFetch,&toWrite);

    fnFetch.clear();

    Utilities::writeVectorToFile(hwORSrcFilePath,toWrite);

    // clear the write vector to start again
    toWrite.clear();

    //==================================================================================================

    genMakefiles(m_hwName);

    return WizardError::NO_ERROR;
}
