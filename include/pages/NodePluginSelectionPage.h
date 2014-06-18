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

#ifndef __NODE_PLUGIN_SELECTION_PAGE_H__
#define __NODE_PLUGIN_SELECTION_PAGE_H__

/// @file NodePluginSelectionPage.h
/// @brief UI Page to allow the user to choose what type of node they would like to make
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class NodePluginSelectionPage
/// @brief UI Page to allow the user to choose what type of node they would like to make

#include <QWidget>

#include "WizardPage.h"

#include "NodeGraphPage.h"
#include "LinkLibrariesPage.h"

/// @brief The ui for this page
namespace Ui
{
    class NodePluginSelectionPage;
}

class NodePluginSelectionPage : public WizardPage
{
    Q_OBJECT

public:
    /// @brief ctr
    /// @param [in] _id int - the id to set to this page
    /// @param [in] _name std::string - name for this page
    /// @param [in] _type PLUGIN_TYPE - plugin type for this page
    /// @param [in] _parentWindow MainWindow* - the parent MainWindow controlling the page
    /// @param [in] _parent QWidget* - parent widget
    explicit NodePluginSelectionPage(int _id, std::string _name, PLUGIN_TYPE _type, MainWindow* _parentWindow = 0, QWidget *_parent = 0);
    /// @brief dtr
    ~NodePluginSelectionPage();

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
    PLUGIN_TYPE defaultType() {return NODE;}
    /// @brief Overriden function to return if this is a generate page or not
    /// @returns bool
    bool generatorPage() {return false;}

private:
    /// @brief The UI
    Ui::NodePluginSelectionPage *m_ui;

    /// @brief The name of the node plugin
    std::string m_nodePluginName;
    /// @brief The chosen type of node to make
    ND_TYPE m_chosenType;
    /// @brief The class from which the ndoe inherits
    std::string m_inheritsFrom;
    /// @brief The type of node as a Maya type (string)
    std::string m_mayaNodeType;
    /// @brief Whether to add objects or not
    bool m_addObjs;

    /// @brief Supported node types for populating the dropdown
    std::vector<ND_TYPE> *m_supportedNodePluginTypes;
    /// @brief Number of supported node types
    int m_numSuportedNodeTypes;
    /// @brief Add a supported node type
    /// @param [in] _type ND_TYPE - the type to be supported
    void addSupportedNodeType(ND_TYPE _type);
    /// @brief Set the default supported node types
    void setDefaultSupportedNodeTypes();
    /// @brief populate the dropdown selection with all supported nodes
    void populateNodeTypeSelection();

    /// @brief Get the string that the ndoe type inherits from
    /// @param [in] _type ND_TYPE - the type to check
    /// @returns std::string
    std::string nodePluginTypeInheritsFrom(ND_TYPE _type);
    /// @brief Get the string of the Maya type to create
    /// @param [in] _type ND_TYPE - the type to check
    /// @returns std::string
    std::string nodePluginTypeToMPxNodeType(ND_TYPE _type);
};

#endif /* __NODE_PLUGIN_SELECTION_PAGE_H__ */
