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

#include "WizardPage.h"

#include <iostream>

WizardPage::WizardPage(std::string _name, PLUGIN_TYPE _type, int _id, QWidget *parent, MainWindow *_parentWindow, bool _final) :
    QWidget(parent)
{
    setName(_name);
    setPluginType(_type);
    setID(_id);
    setFinalPage(_final);
    setParentMainWindow(_parentWindow);

    connectAndInit();
}

WizardPage::~WizardPage()
{

}

void WizardPage::connectAndInit()
{
    setNextButtonText();
    setBackButtonText();
}

void WizardPage::setNextButtonText(std::string _text)
{
    m_nextButtonText = _text;
}

void WizardPage::setBackButtonText(std::string _text)
{
    m_backButtonText = _text;
}

void WizardPage::setParentMainWindow(MainWindow *_parent)
{
    m_parentWindow = _parent;
}
