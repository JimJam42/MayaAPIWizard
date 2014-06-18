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

#include "NodeGraphPage.h"
#include "ui_NodeGraphPage.h"

#include "LinkLibrariesPage.h"

#include "Utilities.h"

#include "MainWindow.h"

NodeGraphPage::NodeGraphPage(int _id, std::string _name, PLUGIN_TYPE _type, ND_TYPE _nodeType, MainWindow* _parentWindow, QWidget *_parent) :
    WizardPage(_name, _type, _id, _parent, _parentWindow), m_ui(new Ui::NodeGraphPage)
{
    m_ui->setupUi(this);
    setID(_id);

    m_nodeType = _nodeType;

    connectAndInit();

    m_ui->h_graphArea->addWidget(m_graphNodeScene);
}

NodeGraphPage::~NodeGraphPage()
{
    delete m_ui;
}

std::string NodeGraphPage::getAttributes()
{
    return m_arguments;
}

void NodeGraphPage::connectAndInit()
{
    m_graphNodeScene = new GraphScene(this);
    m_graphNodeScene->init();
    m_graphNodeScene->addEndNode(Utilities::pluginTypeName(pluginType()));

    m_arguments = "";
}

WizardPage* NodeGraphPage::nextPage(int _id)
{
    return new LinkLibrariesPage(_id,"LinkLibraries",pluginType(),m_nodeType,getParentMainWindow());
}

WizardError::WIZARD_ERROR_CODE NodeGraphPage::gatherInformation()
{
    std::string temp = "";
    if(m_graphNodeScene->collectInformation(&temp))
    {
        m_arguments = temp;
        return WizardError::NO_ERROR;
    }
    return WizardError::ERR_INVALID_ARGUMENTS;
}
