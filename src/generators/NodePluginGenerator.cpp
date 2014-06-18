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

#include "NodePluginGenerator.h"
#include "Utilities.h"

NodePluginGenerator::NodePluginGenerator() : SourceGenerator(NODE_PLUGIN_EXTRA_ATTRIB_COUNT)
{

}

NodePluginGenerator::~NodePluginGenerator()
{

}

WizardError::WIZARD_ERROR_CODE NodePluginGenerator::convertAndStoreAttributes()
{
    /* this function is unique to this generator and will be different (yet similar)
       on every generator type
       the order of attributes passed to this generator are
            ** Generic Default attribs **
            *****************************
            ** Plugin Specific Attribs **
            -Node name
            -Chosen Node Type
            -The class which it will inherit from
            -The corresponding MPxNode type
            -Whether to add objects
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
    m_nodePluginName = getUseableAttribAt(currentInd);
    currentInd++;
    m_chosenType = Utilities::nodePluginTypeFromName(getUseableAttribAt(currentInd));
    currentInd++;
    m_inheritsFrom = getUseableAttribAt(currentInd);
    currentInd++;
    m_mayaNodeType = getUseableAttribAt(currentInd);
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

WizardError::WIZARD_ERROR_CODE NodePluginGenerator::generate()
{
    WizardError::WIZARD_ERROR_CODE status = WizardError::NO_ERROR;
    // first we need to generate the file structure
    createFileStructure(m_nodePluginName);
    // file structure created

    std::string mainSrcFileName = "main.cpp";
    std::string nodeHeaderName = m_nodePluginName + "Plugin.h";
    std::string nodeSrcName = m_nodePluginName + "Plugin.cpp";
    std::string nodeUIScriptName = "AE" + m_nodePluginName + "Template.mel";

    addSrcFile(mainSrcFileName);
    addSrcFile(nodeSrcName);
    addIncludeFile(nodeHeaderName);
    addScript(nodeUIScriptName);

    std::string mainSrcFilePath = std::string(getSrcPath() + "/" + mainSrcFileName);
    std::string nodeIncFilePath = std::string(getIncPath() + "/" + nodeHeaderName);
    std::string nodeSrcFilePath = std::string(getSrcPath() + "/" + nodeSrcName);
    std::string nodeUIScriptPath = std::string(getScriptPath() + "/" + nodeUIScriptName);

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
    status = Utilities::getContentsOfFile(":/Framework/nodeMain",&mainSrcContents);
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
    // in this string, the variable to be replaced is %_#_NODEINCLUDE_#_% which is the name of the include file for the new class file
    Utilities::replaceInStringVector(&incFetch,std::string("%_#_NODEINCLUDE_#_%"), nodeHeaderName);
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
    //  %_#_MPXNODETYPE_#_%
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_VENDOR_#_%"), getVendorName());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_VERSION_#_%"), getPluginVersion());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_REQAPIVER_#_%"), getReqAPIVersion());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_CLASSNAME_#_%"), m_nodePluginName);
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_MPXNODETYPE_#_%"), m_mayaNodeType);
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
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_CLASSNAME_#_%"), m_nodePluginName);
    // ******************************************************************

    Utilities::writeVectorToVector(fnFetch,&toWrite);
    // now clear the noticeFetch ready for next time
    fnFetch.clear();

    Utilities::writeVectorToFile(mainSrcFilePath,toWrite);

    // clear the write vector to start again
    toWrite.clear();

    //==================================================================================================
    // now lets write out the .h file for this node - there will be a lot of node specific
    // stuff going on within this procedure
    QString hContents;
    QString classContents;
    status = Utilities::getContentsOfFile(":/Framework/nodeH",&hContents);
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

    status = replaceIncludeGuards(&grdFetch,m_nodePluginName,obj);
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
    // need to replace %_#_NODETYPEINCLUDE_#_% with the class it inherits from
    Utilities::replaceInStringVector(&incFetch,"%_#_NODETYPEINCLUDE_#_%",m_inheritsFrom);
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
    Utilities::replaceInStringVector(&classFetch,"%_#_INHERITFROM_#_%",m_inheritsFrom);

    // now lets get the required functions for all node types
    status = Utilities::findInJsonObj("reqFns",obj,&temp);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    // now we need to write these to the fnFetch so we can use temp again
    Utilities::writeVectorToVector(temp,&fnFetch);
    temp.clear();

    // ok now comes the tricky bit, need to get the right extra functions for each node type
    status = getNodeTypeSpecificFns(m_chosenType,obj,&temp);
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
    Utilities::replaceInStringVector(&classFetch,"%_#_CLASSNAME_#_%",m_nodePluginName);

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

    Utilities::writeVectorToFile(nodeIncFilePath, toWrite);

    toWrite.clear();

    //==================================================================================================
    // time to write out the .cpp file
    QString cppContents;

    status = Utilities::getContentsOfFile(":/Framework/nodeCpp",&cppContents);
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
    Utilities::replaceInStringVector(&incFetch,"%_#_NODEINCLUDE_#_%",nodeHeaderName);
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

    status = getNodeTypeSpecificFns(m_chosenType,obj,&temp);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    // now we need to write these to the fnFetch so we can use temp again
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
                objs.push_back(Utilities::createObjectCppDecString(m_nodePluginName, getExtraArgumentAt(i)._name));
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
    Utilities::replaceInStringVector(&fnFetch,"%_#_CLASSNAME_#_%",m_nodePluginName);

    Utilities::writeVectorToVector(fnFetch,&toWrite);

    fnFetch.clear();

    Utilities::writeVectorToFile(nodeSrcFilePath,toWrite);

    toWrite.clear();
    temp.clear();

    //==================================================================================================
    // finally is the .mel script for the plugin

    status = createNodeScriptTemplateFile("nodeUITemplateScript",m_nodePluginName,nodeUIScriptPath);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    //==================================================================================================

    genMakefiles(m_nodePluginName);

    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE NodePluginGenerator::getNodeTypeSpecificFns(ND_TYPE _type, QJsonObject _obj,
                                                                       std::vector<std::string> *_vec)
{
    WizardError::WIZARD_ERROR_CODE status = WizardError::NO_ERROR;
    switch(_type)
    {
        case(ND_BASIC_NODE):
        {
            status = Utilities::findInJsonObj("dependNodeFns",_obj,_vec);
            if (status != WizardError::NO_ERROR)
            {
                return status;
            }
        }break;
        case(ND_LOCATOR_NODE):
        {
            status = Utilities::findInJsonObj("locatorNodeFns",_obj,_vec);
            if (status != WizardError::NO_ERROR)
            {
                return status;
            }
        }break;
        case(ND_DEFORMER_NODE):
        {
            status = Utilities::findInJsonObj("deformerNodeFns",_obj,_vec);
            if (status != WizardError::NO_ERROR)
            {
                return status;
            }
        }break;
        case(ND_MANIP_CONTAIN):
        {
            status = Utilities::findInJsonObj("manipContainNodeFns",_obj,_vec);
            if (status != WizardError::NO_ERROR)
            {
                return status;
            }
        }break;
        case(ND_IK_SOLVER):
        {
            status = Utilities::findInJsonObj("ikSolveNodeFns",_obj,_vec);
            if (status != WizardError::NO_ERROR)
            {
                return status;
            }
        }break;
        case(ND_HW_SHADER_NODE):
        {
            status = Utilities::findInJsonObj("hwShaderNodeFns",_obj,_vec);
            if (status != WizardError::NO_ERROR)
            {
                return status;
            }
        }break;
        case(ND_TRANSFORM):
        {
            status = Utilities::findInJsonObj("transformNodeFns",_obj,_vec);
            if (status != WizardError::NO_ERROR)
            {
                return status;
            }
        }break;
        case(ND_OBJECT):
        {
            // there are no specific functions for an object set node
            // so we will do nothing at all here, happy days
            // lets just make sure the vec is empty
            _vec->clear();
        }break;
        case(ND_IMAGE_PLANE):
        {
            status = Utilities::findInJsonObj("imagePlaneNodeFns",_obj,_vec);
            if (status != WizardError::NO_ERROR)
            {
                return status;
            }
        }break;
        case(ND_PARTICLE_ATTRIB_MAPPER):
        {
            // there are no specific functions for a particle attribute mapper node
            // so we will do nothing at all here, happy days
            // lets just make sure the vec is empty
            _vec->clear();
        }break;
        case(ND_CONSTRAINT):
        {
            status = Utilities::findInJsonObj("constraintNodeFns",_obj,_vec);
            if (status != WizardError::NO_ERROR)
            {
                return status;
            }
        }break;
        case(ND_MANIP):
        {
            status = Utilities::findInJsonObj("manipNodeFns",_obj,_vec);
            if (status != WizardError::NO_ERROR)
            {
                return status;
            }
        }break;
        default: return WizardError::ERR_GENERATOR_QUIT; break;
    }
    return status;
}
