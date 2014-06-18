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

#ifndef __NODEGRAPHPAGE_H__
#define __NODEGRAPHPAGE_H__

/// @file NodeGraphPage.h
/// @brief UI Page to hold a node graph and allow the user to add arguments/objects etc
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class NodeGraphPage
/// @brief UI Page to hold a node graph and allow the user to add arguments/objects etc

#include <QWidget>

#include "WizardPage.h"
#include "GraphScene.h"

/// @brief The ui for this page
namespace Ui
{
    class NodeGraphPage;
}

class NodeGraphPage : public WizardPage
{
    Q_OBJECT

public:
    /// @brief ctr
    /// @param [in] _id int - the id to set to this page
    /// @param [in] _name std::string - name for this page
    /// @param [in] _type PLUGIN_TYPE - plugin type for this page
    /// @param [in] _nodeType ND_TYPE - type of node being passed in if a node is
    /// @param [in] _parentWindow MainWindow* - the parent MainWindow controlling the page
    /// @param [in] _parent QWidget* - parent widget
    explicit NodeGraphPage(int _id, std::string _name, PLUGIN_TYPE _type,
                           ND_TYPE _nodeType=ND_NOTYPE, MainWindow* _parentWindow = 0, QWidget *_parent = 0);
    /// @brief dtr
    ~NodeGraphPage();

    // overloads of the virtual functions within WizardPage
    /// @brief Overriden function to get the attributes from the page and return as string
    /// @returns std::string
    std::string getAttributes();
    /// @brief Overriden function to connect signals and init the page
    void connectAndInit();
    /// @brief Overriden function to return what the next page will be
    /// @param [in] _id int - id to set to the next page
    WizardPage* nextPage(int _id);
    /// @brief Overriden function to get the information off the page and store it
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE gatherInformation();
    /// @brief Overriden function to get the default plugin type for this page
    /// @returns PLUGIN_TYPE
    PLUGIN_TYPE defaultType() {return NO_PLUGIN_TYPE;}
    /// @brief Overriden function to return if this is a generate page or not
    /// @returns bool
    bool generatorPage() {return false;}

private:
    /// @brief The UI
    Ui::NodeGraphPage *m_ui;
    /// @brief The graph scene to add to the widget
    GraphScene *m_graphNodeScene;
    /// @brief The arguments to pass
    std::string m_arguments;
    /// @brief Node type if node
    ND_TYPE m_nodeType;
};

#endif /* __NODEGRAPHPAGE_H__ */
