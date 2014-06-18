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

#include "FinishPage.h"
#include "ui_FinishPage.h"

#include "Utilities.h"

#include "MainWindow.h"

#include <iostream>

FinishPage::FinishPage(int _id, std::string _name, PLUGIN_TYPE _type, MainWindow* _parentWindow, QWidget *_parent) :
    WizardPage(_name, _type, _id, _parent, _parentWindow, true), m_ui(new Ui::FinishPage)
{
    m_ui->setupUi(this);

    connectAndInit();

    setNextButtonText("Finish");
}

FinishPage::~FinishPage()
{
    delete m_ui;
}

std::string FinishPage::getAttributes()
{
    // this has no attributes to return so just return an empty string
    // to ensure that the final attributes are not effected
    return "";
}

void FinishPage::connectAndInit()
{

}

WizardPage* FinishPage::nextPage(int _id)
{
    _id = 0; // flatten the warning from the passed in unused attribute
    // as this is the final page for the wizard, return a null pointer so we know to close
    return NULL;
}

WizardError::WIZARD_ERROR_CODE FinishPage::gatherInformation()
{
    // as this is the final page, nothing needs to happen here so return no errors
    return WizardError::NO_ERROR;
}
