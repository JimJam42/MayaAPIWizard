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

#include "EmitterPluginPage.h"
#include "ui_EmitterPluginPage.h"

#include "NodeGraphPage.h"
#include "LinkLibrariesPage.h"

#include "MainWindow.h"

#include "Utilities.h"

EmitterPluginPage::EmitterPluginPage(int _id, std::string _name, PLUGIN_TYPE _type, MainWindow* _parentWindow, QWidget *_parent) :
    WizardPage(_name, _type, _id, _parent, _parentWindow), m_ui(new Ui::EmitterPluginPage)
{
    m_ui->setupUi(this);

    connectAndInit();
}

EmitterPluginPage::~EmitterPluginPage()
{
    delete m_ui;
}

std::string EmitterPluginPage::getAttributes()
{
    std::string returnString = "";
    returnString += std::string(m_emitterName + ATTRIB_DELIM);
    returnString += std::string(Utilities::boolToString(m_addObjs) + ATTRIB_DELIM);
    returnString += std::string(Utilities::boolToString(m_createEmit) + ATTRIB_DELIM);
    return returnString;
}

void EmitterPluginPage::connectAndInit()
{
    m_emitterName = "";
    m_addObjs = false;
    m_createEmit = false;
}

WizardPage* EmitterPluginPage::nextPage(int _id)
{
    if (m_addObjs)
    {
        return new NodeGraphPage(_id,"AddObjs",pluginType(),ND_NOTYPE,getParentMainWindow());
    }
    return new LinkLibrariesPage(_id,"LinkLibraries",pluginType(),ND_NOTYPE,getParentMainWindow());
}

WizardError::WIZARD_ERROR_CODE EmitterPluginPage::gatherInformation()
{
    // test here that the class name is neither empty or contains a space
    // once these have been clarified then we are good to continue
    // to do this need to create a QString from the line edit to then conduct these tests

    QString name = m_ui->line_className->text();

    if (name.isEmpty())
    {
        return WizardError::ERR_NO_NAME_SPECIFIED;
    }
    if (name.contains(" "))
    {
        return WizardError::ERR_INVALID_NAME;
    }

    // everything is sparkly here so we can just store
    m_emitterName = name.toStdString();
    m_addObjs = m_ui->cbx_addObjs->isChecked();
    m_createEmit = m_ui->cbx_createEmit->isChecked();
    return WizardError::NO_ERROR;
}
