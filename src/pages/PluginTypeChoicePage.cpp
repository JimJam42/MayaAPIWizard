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

#include "PluginTypeChoicePage.h"
#include "ui_PluginTypeChoicePage.h"

#include "LinkLibrariesPage.h"
#include "Utilities.h"

#include "PageIncludes.h"

#include "MainWindow.h"

#include <QFileDialog>

#include <iostream>

PluginTypeChoicePage::PluginTypeChoicePage(int _id, std::string _name, PLUGIN_TYPE _type, MainWindow* _parentWindow, QWidget *_parent) :
    WizardPage(_name, _type, _id, _parent, _parentWindow), m_ui(new Ui::PluginTypeChoicePage)
{
    m_ui->setupUi(this);

    setID(_id);

    connectAndInit();
}

PluginTypeChoicePage::~PluginTypeChoicePage()
{
    m_supportedPluginTypes->clear();
    delete m_supportedPluginTypes;

    delete m_ui;
}

std::string PluginTypeChoicePage::getAttributes()
{
    std::string returnString = "";
    returnString += std::string(m_mayaDir + ATTRIB_DELIM);
    returnString += std::string(Utilities::pluginTypeName(m_chosenPluginType) + ATTRIB_DELIM);
    returnString += std::string(m_vendorName + ATTRIB_DELIM);
    returnString += std::string(m_pluginVersion + ATTRIB_DELIM);
    returnString += std::string(m_requiredAPIVersion + ATTRIB_DELIM);
    return returnString;
}

void PluginTypeChoicePage::connectAndInit()
{
    m_supportedPluginTypes = new std::vector<PLUGIN_TYPE>;
    m_supportedPluginTypes->clear();

    m_numSupportedPlugins = 0;

    defaultSupportedPluginTypes();

    populatePluginChoice();

    // initialise the information to gather from this page
    // this will finally be set when the gatherInformation function is called and successfully passes
    m_chosenPluginType = NO_PLUGIN_TYPE; // default NULL plugin type
    m_mayaDir = getParentMainWindow()->getPreferenceWindow()->mayaDir();
    m_vendorName = getParentMainWindow()->getPreferenceWindow()->vendor();
    m_pluginVersion = "";
    m_requiredAPIVersion = "";

    connect(m_ui->btn_browseForMayaLoc,SIGNAL(clicked(bool)),this,SLOT(browseForMayaDir()));

    m_ui->line_mayaLoc->setText(QString(m_mayaDir.c_str()));
    m_ui->line_vendorName->setText(QString(m_vendorName.c_str()));
}

WizardPage* PluginTypeChoicePage::nextPage(int _id)
{
    // this page has multiple options and routes
    // here it will detect which type of plugin to start creating and create the appropriate page    

    switch(m_chosenPluginType)
    {
        case(CMD)       : return new CommandPlugin(_id,"CommandPlugin_pg1",CMD,getParentMainWindow()); break;
        case(FILE_TRANS): return new FileTranslatorPlugin(_id,"FileTranslatorPlugin_pg1",FILE_TRANS,getParentMainWindow()); break;
        case(NODE)      : return new NodePluginSelectionPage(_id,"NodePluginChoice_pg1",NODE,getParentMainWindow()); break;
        case(SHADER_SW) : return new SWShaderPage(_id,"SWShader_pg1",SHADER_SW,getParentMainWindow()); break;
        case(SHADER_HW) : return new HWShaderPage(_id,"HWShader_pg1",SHADER_HW,getParentMainWindow()); break;
        case(EMITTER)   : return new EmitterPluginPage(_id,"EmitterPlugin_pg1",EMITTER,getParentMainWindow()); break;
        default         : return new FinishPage(_id,"FinishPageTypeError",NO_PLUGIN_TYPE,getParentMainWindow()); break;
    }
}

WizardError::WIZARD_ERROR_CODE PluginTypeChoicePage::gatherInformation()
{
    // first test that the specified maya directory is not valid
    // so lets just make sure there is at least something in the box
    QString mayaLoc = m_ui->line_mayaLoc->text();
    if (mayaLoc.isEmpty())
    {
        return WizardError::ERR_NO_PATH_SPECIFIED;
    }

    // if we have reached here then at least a path has been specified
    // now we need to test that the directory is valid
    // will do this by testing for two things - firstly if include/maya/MGlobal.h (Linux) or devkit/include/maya/MGlobal.h (Mac) exists
    // and also if lib/libOpenMaya.so (linux) or Maya.app/Contents/MacOS/libOpenMaya.dylib (Mac) exists

    // test for MGlobal.h
    QString vendorName = m_ui->line_vendorName->text();
    QString version = m_ui->line_pluginVersion->text();
    QString reqAPIVer = m_ui->line_reqAPIVersion->text();
#ifndef SKIP_MAYA_TEST // for development on Linux machine without a Maya install
    if (getParentMainWindow()->getPreferenceWindow()->checkMayaDir())
    {
        std::string path = mayaLoc.toStdString();

        #ifdef LINUX
            path += "/include/maya/MGlobal.h";
        #endif
        #ifdef DARWIN
            path += "/devkit/include/maya/MGlobal.h";
        #endif

        if (!Utilities::pathExists(path))
        {
            return WizardError::ERR_INVALID_PATH;
        }

        // if we have reached this point then so far it is valid for MGlobal.h, now check for the library
        // reset the path
        path = mayaLoc.toStdString();

        #ifdef LINUX
            path += "/lib/libOpenMaya.so";
        #endif
        #ifdef DARWIN
            path += "/Maya.app/Contents/MacOS/libOpenMaya.dylib";
        #endif

        if (!Utilities::pathExists(path))
        {
            return WizardError::ERR_INVALID_PATH;
        }
    }
#endif

    // if we have reached this point then we are happy that this should be a valid Maya directory
    // next test that a name for the Vendor has been given
    if (vendorName.isEmpty())
    {
        return WizardError::ERR_NO_NAME_SPECIFIED;
    }

    if (vendorName.contains(' '))
    {
        return WizardError::ERR_INVALID_CHAR;
    }

    // check that a plugin version has been specified
    if (version.isEmpty())
    {
        return WizardError::ERR_NO_VERSION_SPECIFIED;
    }

    if (version.contains(' ') || version.contains('/') || version.contains('\\'))
    {
        return WizardError::ERR_INVALID_NAME;
    }

    // check that a valid require API version has been specified
    if (reqAPIVer.isEmpty())
    {
        return WizardError::ERR_NO_NAME_SPECIFIED;
    }

    if (reqAPIVer.contains(' '))
    {
        return WizardError::ERR_INVALID_CHAR;
    }

    // if we have reached here, we are happy everything is at it should be, so proceed
    // store the given information
    m_chosenPluginType = m_supportedPluginTypes->at(m_ui->cmbo_pluginType->currentIndex());
    m_mayaDir = mayaLoc.toStdString();
    m_vendorName = vendorName.toStdString();
    m_pluginVersion = version.toStdString();
    m_requiredAPIVersion = reqAPIVer.toStdString();
    return WizardError::NO_ERROR;
}

void PluginTypeChoicePage::addSupportedPluginType(PLUGIN_TYPE _type)
{
    bool alreadySupported = false;
    int count = 0;
    // check to make sure it hasnt already been added first
    while (!alreadySupported && count < m_numSupportedPlugins)
    {
        if (m_supportedPluginTypes->at(count) == _type)
        {
            alreadySupported = true;
        }
        count++;
    }

    if (!alreadySupported)
    {
        m_supportedPluginTypes->push_back(_type);
    }

    m_numSupportedPlugins = m_supportedPluginTypes->size();
}

void PluginTypeChoicePage::browseForMayaDir()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,tr("Browse for Maya Root"),tr(""),options);

    if (!directory.isEmpty())
    {
        m_ui->line_mayaLoc->setText(directory);
    }
}

void PluginTypeChoicePage::populatePluginChoice()
{
    // first clear the combo box to ensure this is a correct list
    m_ui->cmbo_pluginType->clear();

    // populate drop down box with all supported plugin type names
    for (int i = 0; i < m_numSupportedPlugins; i++)
    {
        m_ui->cmbo_pluginType->addItem(tr(Utilities::pluginTypeName(m_supportedPluginTypes->at(i)).c_str()));
    }
}

void PluginTypeChoicePage::defaultSupportedPluginTypes()
{
    // add all default supported plugin types here
    addSupportedPluginType(CMD);
    addSupportedPluginType(FILE_TRANS);
    addSupportedPluginType(NODE);
    addSupportedPluginType(SHADER_SW);
    addSupportedPluginType(SHADER_HW);
    addSupportedPluginType(EMITTER);
}
