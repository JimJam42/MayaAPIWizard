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

#include "CommandPluginGenerator.h"

#include "Utilities.h"

#include <iostream>

#include <QMessageBox>

CommandPluginGenerator::CommandPluginGenerator() : SourceGenerator(COMMAND_PLUGIN_EXTRA_ATTRIB_COUNT)
{

}

CommandPluginGenerator::~CommandPluginGenerator()
{

}

WizardError::WIZARD_ERROR_CODE CommandPluginGenerator::convertAndStoreAttributes()
{
    /* this function is unique to this generator and will be different (yet similar)
       on every generator type
       the order of attributes passed to this generator are
            ** Generic Default attribs **
            *****************************
            ** Plugin Specific Attribs **
            -Command name
            -Command class name
            -If the command is redoable
            -Whether to add your own arguments
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
    m_commandName = getUseableAttribAt(currentInd);
    currentInd++;
    m_commandClassName = getUseableAttribAt(currentInd) + "Command";
    currentInd++;
    m_redoable = Utilities::stringToBool(getUseableAttribAt(currentInd));
    currentInd++;
    m_addArgs = Utilities::stringToBool(getUseableAttribAt(currentInd));
    currentInd++;

    // set the last of the generic common attributes
    status = storeSecondHalfOfDefaultAttributes(&currentInd);

    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    return WizardError::NO_ERROR;
}

WizardError::WIZARD_ERROR_CODE CommandPluginGenerator::generate()
{
    // generate files from here
    WizardError::WIZARD_ERROR_CODE status = WizardError::NO_ERROR;

    // create file structure
    createFileStructure(m_commandName);
    // file structure created

    // create files
    std::string mainSrcFileName = "main.cpp";
    std::string commandHeaderName = m_commandClassName + "Plugin.h";
    std::string commandSrcName = m_commandClassName + "Plugin.cpp";

    addIncludeFile(commandHeaderName);
    addSrcFile(mainSrcFileName);
    addSrcFile(commandSrcName);

    std::string mainSrcFilePath = std::string(getSrcPath() + "/" + mainSrcFileName);
    std::string commandIncFilePath = std::string(getIncPath() + "/" + commandHeaderName);
    std::string commandSrcFilePath = std::string(getSrcPath() + "/" + commandSrcName);

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
    // now it is needed to write the default framework to these files whilt replacing the variable names
    // lets first do the main.cpp to init and deinit the plugin
    // need to first open the file
    QString mainSrcContents;
    status = Utilities::getContentsOfFile(":/Framework/melCmdMain",&mainSrcContents);
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
    // in this string, the variable to be replaced is %_#_CMDINCLUDE_#_% which is the name of the include file for the new class file
    Utilities::replaceInStringVector(&incFetch,std::string("%_#_CMDINCLUDE_#_%"), commandHeaderName);
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
    //  %_#_CMDNAME_#_%
    //  %_#_CMDCLASS_#_%
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_VENDOR_#_%"), getVendorName());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_VERSION_#_%"), getPluginVersion());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_REQAPIVER_#_%"), getReqAPIVersion());
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_CMDNAME_#_%"), m_commandName);
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_CMDCLASS_#_%"), m_commandClassName);
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
    //  %_#_CMDNAME_#_%
    Utilities::replaceInStringVector(&fnFetch,std::string("%_#_CMDNAME_#_%"), m_commandName);
    // ******************************************************************

    Utilities::writeVectorToVector(fnFetch,&toWrite);
    // now clear the noticeFetch ready for next time
    fnFetch.clear();

    Utilities::writeVectorToFile(mainSrcFilePath,toWrite);

    //==================================================================================================

    // clear the write vector to start again
    toWrite.clear();

    // now get information for the header file for this command
    QString hContents;
    QString classContents;
    status = Utilities::getContentsOfFile(":/Framework/melCmdH",&hContents);
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

    status = replaceIncludeGuards(&grdFetch,m_commandClassName,obj);
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
    // write the temp to the fnFetch vector to build up all required functions
    Utilities::writeVectorToVector(temp,&fnFetch);
    // fetch the extra functions
    status = Utilities::findInJsonObj("optFns",obj,&temp);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }
    // now check if the user wanst the command to be redoable
    // if so write them to the fnFetch
    if (m_redoable)
    {
        Utilities::writeStringToVector(temp.at(0),&fnFetch);
        Utilities::writeStringToVector(temp.at(1),&fnFetch);
    }

    // remove all data in the temp vector
    temp.clear();
    // now I have fetched the functions to write, need to replace attributes in those
    // will test for all possible attributes to swap
    //  %_#_UNDOABLEBOOL_#_%
    //  %_#_SYNTAXBOOL_#_%
    Utilities::replaceInStringVector(&fnFetch,"%_#_UNDOABLEBOOL_#_%",Utilities::boolToString(m_redoable));
    Utilities::replaceInStringVector(&fnFetch,"%_#_SYNTAXBOOL_#_%",Utilities::boolToString(m_addArgs));
    // now I need to replace the attributes within the classDef
    //  %_#_CLASSNAME_#_%
    //  %_#_INHERITFROM_#_%
    //  %_#_FNSPECFN_#_%
    //  %_#_FNSPECATTRIBS_#_%
    Utilities::replaceInStringVector(&classFetch,"%_#_CLASSNAME_#_%",m_commandClassName);
    Utilities::replaceInStringVector(&classFetch,"%_#_INHERITFROM_#_%","MPxCommand");
    Utilities::replaceInStringVectorWithVector(&classFetch, "%_#_FNSPECFN_#_%",fnFetch);
    if (m_addArgs)
    {
        // build up a vector of the arguments as member attributes
        std::vector<std::string> tempArgs;
        tempArgs.clear();

        for (int i = 0; i < getNumExtraArguments(); i++)
        {
            if (getExtraArgumentAt(i)._vType != "OBJECT") // commands will not accept objects
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

    Utilities::writeVectorToFile(commandIncFilePath, toWrite);

    toWrite.clear();

    //==================================================================================================

    QString cppContents;

    status = Utilities::getContentsOfFile(":/Framework/melCmdCpp",&cppContents);
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
    Utilities::replaceInStringVector(&incFetch,"%_#_CMDINCLUDE_#_%",commandHeaderName);
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

    Utilities::findInJsonObj("optFns",obj,&temp);
    if (status != WizardError::NO_ERROR)
    {
        return status;
    }

    if (m_redoable)
    {
        Utilities::writeStringToVector(temp.at(0),&fnFetch);
        Utilities::writeStringToVector(temp.at(1),&fnFetch);
    }

    // now we have the functions to be written, parse out any attributes
    // in this case it is
    //  %_#_CLASSNAME_#_%
    //  %_#_DOITFNCONT_#_%
    //  %_#_CMDNAME_#_%
    //  "%_#_PARSER_#_%"
    //  %_#_DOITRTRN_#_% (if m_redoable)
    //  %_#_NSYNCONT_#_% (if m_addArgs)
    //  %_#_ADDFLAGS_#_% (if m_addArgs)
    Utilities::replaceInStringVector(&fnFetch,"%_#_CLASSNAME_#_%",m_commandClassName);
    Utilities::replaceInStringVector(&fnFetch,"%_#_CMDNAME_#_%",m_commandName);

    if (m_redoable)
    {
        Utilities::replaceInStringVector(&fnFetch,"%_#_DOITRTRN_#_%","redoIt()");
    }
    else
    {
        Utilities::replaceInStringVector(&fnFetch,"%_#_DOITRTRN_#_%","MStatus::kSuccess");
    }

    // for the %_#_DOITFNCONT_#_% I need to first get doItFnCont out of the json file
    std::vector<std::string> doItFnCont;
    doItFnCont.clear();
    Utilities::findInJsonObj("doItFnCont",obj,&doItFnCont);

    std::vector<std::string> newSyn;
    newSyn.clear();
    Utilities::findInJsonObj("newSyn",obj,&newSyn);
    // now in newSyn, need to replace %_#_ADDFLAGS_#_%

    // in here need to replace "%_#_PARSER_#_%" with either nothing is not extra args or the args if extra args
    if (m_addArgs)
    {
        // here we will only be needing the argument types and so only do anything if the extra argument is a command line argument type specified
        std::vector<std::string> parseDec;
        parseDec.clear();
        for (int j =0; j < getNumExtraArguments(); j++)
        {
            if (getExtraArgumentAt(j)._vType == "ARGUMENT")
            {
                parseDec.push_back(parserFlagSetFromArgument(getExtraArgumentAt(j)));
            }
        }
        Utilities::replaceInStringVectorWithVector(&doItFnCont,"%_#_PARSER_#_%",parseDec);

        // now replace %_#_NSYNCONT_#_% - first need to get newSyn

        // first build up the vector to replace it
        std::vector<std::string> argSynDec;
        argSynDec.clear();
        for (int i =0; i < getNumExtraArguments(); i++)
        {
            if (getExtraArgumentAt(i)._vType == "ARGUMENT")
            {
                argSynDec.push_back(getAddFlagFromArgument(getExtraArgumentAt(i)));
            }
        }
        Utilities::replaceInStringVectorWithVector(&newSyn,"%_#_ADDFLAGS_#_%",argSynDec);
    }
    else
    {
        Utilities::replaceInStringVector(&doItFnCont,"%_#_PARSER_#_%","");
        Utilities::replaceInStringVector(&newSyn,"%_#_ADDFLAGS_#_%","");
    }

    // then replace %_#_NSYNCONT_#_% with newSyn
    Utilities::replaceInStringVectorWithVector(&fnFetch,"%_#_NSYNCONT_#_%",newSyn);

    // now replace  %_#_DOITFNCONT_#_% with this string vector
    Utilities::replaceInStringVectorWithVector(&fnFetch,"%_#_DOITFNCONT_#_%",doItFnCont);

    Utilities::writeVectorToVector(fnFetch,&toWrite);

    Utilities::writeVectorToFile(commandSrcFilePath,toWrite);

    //==================================================================================================

    genMakefiles(m_commandName);

    return WizardError::NO_ERROR;
}


std::string CommandPluginGenerator::getAddFlagFromArgument(AddedArgument _arg)
{
    // the MSyntax here will always be syn
    std::string build = "\tsyn.addFlag(\"-";
    build += _arg._shortName;
    build += "\", \"-";
    build += _arg._name;
    build += "\", ";
    build += Utilities::argTypeToMayaTypeString(_arg._type);
    build += ");";
    return build;
}

std::string CommandPluginGenerator::parserFlagSetFromArgument(AddedArgument _arg)
{
    std::string parse = "\tif(parser.isFlagSet(\"-";
    parse += _arg._shortName;
    parse += "\"))\n\t{\n\t\tparser.getFlagArgument(\"-";
    parse += _arg._shortName;
    parse += "\", 0, m_";
    parse += _arg._name;
    parse += ");\n\t}\n";
    return parse;
}
