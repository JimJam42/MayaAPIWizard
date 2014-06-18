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

#include "HWShaderPage.h"
#include "ui_HWShaderPage.h"

#include "NodeGraphPage.h"
#include "LinkLibrariesPage.h"

#include "MainWindow.h"

#include "Utilities.h"

HWShaderPage::HWShaderPage(int _id, std::string _name, PLUGIN_TYPE _type, MainWindow* _parentWindow, QWidget *_parent) :
    WizardPage(_name, _type, _id, _parent, _parentWindow), m_ui(new Ui::HWShaderPage)
{
    m_ui->setupUi(this);

    connectAndInit();
}

HWShaderPage::~HWShaderPage()
{
    delete m_ui;
}

std::string HWShaderPage::getAttributes()
{
    std::string returnString = "";
    returnString += std::string(m_hwName + ATTRIB_DELIM);
    returnString += std::string(m_hwNameOR + ATTRIB_DELIM);
    returnString += std::string(Utilities::boolToString(m_addObjs) + ATTRIB_DELIM);
    return returnString;
}

void HWShaderPage::connectAndInit()
{
    m_hwName = "";
    m_hwNameOR = "";
    m_addObjs = false;
}

WizardPage* HWShaderPage::nextPage(int _id)
{
    if (m_addObjs)
    {
        return new NodeGraphPage(_id,"AddObjs",pluginType(),ND_NOTYPE,getParentMainWindow());
    }
    return new LinkLibrariesPage(_id,"LinkLibraries",pluginType(),ND_NOTYPE,getParentMainWindow());
}

WizardError::WIZARD_ERROR_CODE HWShaderPage::gatherInformation()
{
    // not a very busy UI this one just like the SWShader
    // just need to check and get the value from the className
    QString name = m_ui->line_className->text();

    // check the name isnt empty
    if (name.isEmpty())
    {
        return WizardError::ERR_NO_NAME_SPECIFIED;
    }

    // check that it does not contain any spaces
    if (name.contains(" "))
    {
        return WizardError::ERR_INVALID_NAME;
    }

    // ok so everything has gone without hitch to this point so simply store data
    m_hwName = name.toStdString();
    m_hwNameOR = std::string(m_hwName+"Override");
    m_addObjs = m_ui->cbx_addObjs->isChecked();

    return WizardError::NO_ERROR;
}
