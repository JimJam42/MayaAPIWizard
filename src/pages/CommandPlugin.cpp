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

#include "CommandPlugin.h"
#include "ui_CommandPlugin.h"

#include "LinkLibrariesPage.h"
#include "NodeGraphPage.h"

#include "MainWindow.h"

#include "Utilities.h"

CommandPlugin::CommandPlugin(int _id, std::string _name, PLUGIN_TYPE _type, MainWindow *_parentWindow, QWidget *_parent) :
    WizardPage(_name, _type, _id, _parent, _parentWindow), m_ui(new Ui::CommandPlugin)
{
    m_ui->setupUi(this);

    connectAndInit();
}

CommandPlugin::~CommandPlugin()
{
    delete m_ui;
}

std::string CommandPlugin::getAttributes()
{
    std::string returnString = "";
    returnString += std::string(m_commandName + ATTRIB_DELIM);
    returnString += std::string(m_commandClassName + ATTRIB_DELIM);
    returnString += std::string(Utilities::boolToString(m_redoable) + ATTRIB_DELIM);
    returnString += std::string(Utilities::boolToString(m_addArgs) + ATTRIB_DELIM);
    return returnString;
}

void CommandPlugin::connectAndInit()
{

}

WizardPage* CommandPlugin::nextPage(int _id)
{
    // the intro page will always lead on into the plugin choice page
    if (m_addArgs)
    {
        return new NodeGraphPage(_id,"AddArgs",pluginType(),ND_NOTYPE,getParentMainWindow());
    }
    return new LinkLibrariesPage(_id,"LinkLibraries",pluginType(),ND_NOTYPE,getParentMainWindow());
}

WizardError::WIZARD_ERROR_CODE CommandPlugin::gatherInformation()
{
    // need to make sure all required information has been entered before storing and continuing
    QString commandName = m_ui->line_commandName->text();
    QString className = m_ui->line_className->text();

    // test the command name first
    if (commandName.isEmpty())
    {
        return WizardError::ERR_NO_NAME_SPECIFIED;
    }
    if(commandName.contains(' '))
    {
        return WizardError::ERR_INVALID_CHAR;
    }

    // now test the class name
    if (className.isEmpty())
    {
        return WizardError::ERR_NO_NAME_SPECIFIED;
    }
    if(className.contains(' '))
    {
        return WizardError::ERR_INVALID_CHAR;
    }
    // if we have reached this point then all information has been entered and is correct
    // can now gather information
    m_commandName = commandName.toStdString();
    m_commandClassName = className.toStdString();
    m_redoable = m_ui->cbx_redoable->isChecked();
    m_addArgs = m_ui->cbx_defineCmdLineArgs->isChecked();
    return WizardError::NO_ERROR;
}
