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

#include "IntroPage.h"
#include "ui_IntroPage.h"

#include "Utilities.h"

#include "PluginTypeChoicePage.h"

#include "MainWindow.h"

#include <iostream>

IntroPage::IntroPage(int _id, std::string _name, PLUGIN_TYPE _type, MainWindow* _parentWindow, QWidget *_parent) :
    WizardPage(_name, _type, _id, _parent, _parentWindow), m_ui(new Ui::IntroPage)
{
    m_ui->setupUi(this);

    connectAndInit();

    setNextButtonText("Start");
}

IntroPage::~IntroPage()
{
    delete m_ui;
}

std::string IntroPage::getAttributes()
{
    // this has no attributes to return so just return an empty string
    // to ensure that the final attributes are not effected
    return "";
}

void IntroPage::connectAndInit()
{

}

WizardPage* IntroPage::nextPage(int _id)
{
    // the intro page will always lead on into the plugin choice page
    return new PluginTypeChoicePage(_id,"PluginChoice",NO_PLUGIN_TYPE,getParentMainWindow());
}

WizardError::WIZARD_ERROR_CODE IntroPage::gatherInformation()
{
    // as this is the intro page, nothing needs to happen here so return no errors
    return WizardError::NO_ERROR;
}
