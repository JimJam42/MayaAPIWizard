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

#include "FileTranslatorPlugin.h"
#include "ui_FileTranslatorPlugin.h"

#include "LinkLibrariesPage.h"
#include "NodeGraphPage.h"

#include "MainWindow.h"

#include "Utilities.h"

FileTranslatorPlugin::FileTranslatorPlugin(int _id, std::string _name, PLUGIN_TYPE _type, MainWindow* _parentWindow, QWidget *_parent) :
    WizardPage(_name, _type, _id, _parent, _parentWindow), m_ui(new Ui::FileTranslatorPlugin)
{
    m_ui->setupUi(this);

    setID(_id);

    connectAndInit();
}

FileTranslatorPlugin::~FileTranslatorPlugin()
{
    delete m_ui;
}

std::string FileTranslatorPlugin::getAttributes()
{
    std::string returnString = "";
    returnString += std::string(m_ftClassName + ATTRIB_DELIM);
    returnString += std::string(m_ftName + ATTRIB_DELIM);
    returnString += std::string(m_uiScriptName + ATTRIB_DELIM);
    returnString += std::string(m_impExp + ATTRIB_DELIM);
    returnString += std::string(m_defaultFileExtension + ATTRIB_DELIM);
    returnString += std::string(Utilities::boolToString(m_addPrivAttribs) + ATTRIB_DELIM);
    return returnString;
}

void FileTranslatorPlugin::connectAndInit()
{
    m_ftClassName = "";
    m_ftName = "";
    m_uiScriptName = "";
    m_impExp = "";
    m_defaultFileExtension = "";
    m_addPrivAttribs = false;
}

WizardPage* FileTranslatorPlugin::nextPage(int _id)
{
    if (m_addPrivAttribs)
    {
        return new NodeGraphPage(_id,"AddAttribs",pluginType(),ND_NOTYPE,getParentMainWindow());
    }
    return new LinkLibrariesPage(_id,"LinkLibraries",pluginType(),ND_NOTYPE,getParentMainWindow());
}

WizardError::WIZARD_ERROR_CODE FileTranslatorPlugin::gatherInformation()
{
    // need to make sure that all the required fields have been filled in and that the FT Name does not match the class name
    // I have found form experiance that this can cause issues
    QString className = m_ui->line_className->text();
    QString ftName = m_ui->line_transName->text();
    QString uiName = m_ui->line_uiScriptName->text();
    QString fileExt = m_ui->line_fileExt->text();

    // check first to see if the class name and translator name are different
    if (className == ftName)
    {
        return WizardError::ERR_CONFLICTING_NAMES;
    }
    // also check if any of them are empty
    if (className.isEmpty() || ftName.isEmpty() || uiName.isEmpty() || fileExt.isEmpty())
    {
        return WizardError::ERR_NO_NAME_SPECIFIED;
    }

    // check there are no spaces in the ftName
    if (className.contains(" "))
    {
        return WizardError::ERR_INVALID_NAME;
    }

    // if we have reached here then none of the names are empty so we can now check them for invalid characters
    // the ui script cannot contain any '.'
    if (uiName.contains('.'))
    {
        return WizardError::ERR_INVALID_NAME;
    }

    // check the file extension
    if (fileExt.contains('.') || fileExt.contains('/') || fileExt.contains('\\') || fileExt.contains('-') || fileExt.contains('_'))
    {
        return WizardError::ERR_INVALID_FILEEXT;
    }

    // if we have reached this stage, all is dandy and so we can store data
    m_ftClassName = className.toStdString();
    m_ftName = ftName.toStdString();
    m_uiScriptName = uiName.toStdString();
    m_defaultFileExtension = fileExt.toStdString();

    if (m_ui->rdio_Import->isChecked())
    {
        m_impExp = "import";
    }
    else if (m_ui->rdio_export->isChecked())
    {
        m_impExp = "export";
    }
    else
    {
        m_impExp = "importexport";
    }

    m_addPrivAttribs = m_ui->cbx_addPrivAttribs->isChecked();

    return WizardError::NO_ERROR;
}
