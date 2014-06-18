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

#ifndef __PLUGINTYPECHOICEPAGE_H__
#define __PLUGINTYPECHOICEPAGE_H__

/// @file PluginTypeChoicePage.h
/// @brief UI page to allow the user to choose which type of plugin they would like to use
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class PluginTypeChoicePage
/// @brief UI page to allow the user to choose which type of plugin they would like to use

#include <QWidget>

#include "WizardPage.h"

/// @brief The ui for this page
namespace Ui
{
    class PluginTypeChoicePage;
}

class PluginTypeChoicePage : public WizardPage
{
    Q_OBJECT
public:
    /// @brief ctr
    /// @param [in] _id int - the id to set to this page
    /// @param [in] _name std::string - name for this page
    /// @param [in] _type PLUGIN_TYPE - plugin type for this page
    /// @param [in] _parentWindow MainWindow* - the parent MainWindow controlling the page
    /// @param [in] _parent QWidget* - parent widget
    explicit PluginTypeChoicePage(int _id, std::string _name, PLUGIN_TYPE _type=NO_PLUGIN_TYPE, MainWindow* _parentWindow = 0, QWidget *_parent = 0);
    /// @brief dtr
    ~PluginTypeChoicePage();

    // overloads of the virtual functions within WizardPage
    /// @brief Overriden function to get the attributes from the page and return as string
    /// @returns std::string
    std::string getAttributes();
    /// @brief Overriden function to connect signals and init the page
    void connectAndInit();
    /// @brief Overriden function to return what the next page will be
    /// @param [in] _id int - id to set to the next page
    WizardPage* nextPage(int _id);
    // in this gather information, I will test the given maya directory before continuing to ensure it is valid
    // if it is not valid, I will not allow the user to continue until a valid one has been supplied
    /// @brief Overriden function to get the information off the page and store it
    /// @returns WizardError::WIZARD_ERROR_CODE
    WizardError::WIZARD_ERROR_CODE gatherInformation();
    /// @brief Overriden function to get the default plugin type for this page
    /// @returns PLUGIN_TYPE
    PLUGIN_TYPE defaultType() {return NO_PLUGIN_TYPE;}
    /// @brief Overriden function to return if this is a generate page or not
    /// @returns bool
    bool generatorPage() {return false;}
    /// @brief Add a supported plugin type
    /// @param [in] _type PLUGIN_TYPE -  the type to add
    void addSupportedPluginType(PLUGIN_TYPE _type);

private slots:
    /// @brief Open a browse window to browse for where Maya lives
    void browseForMayaDir();
    
private:
    /// @brief The UI
    Ui::PluginTypeChoicePage *m_ui;
    /// @brief Populate the dropdown for plugin choice
    void populatePluginChoice();
    /// @brief Set default supported plugin types
    void defaultSupportedPluginTypes();
    /// @brief All supported plugin types
    std::vector<PLUGIN_TYPE> *m_supportedPluginTypes;
    /// @brief Number of supported plugin types
    int m_numSupportedPlugins;

    // attributes to gather information to
    /// @brief Maya directory
    std::string m_mayaDir;
    /// @brief Chosen plugin type
    PLUGIN_TYPE m_chosenPluginType;
    /// @brief Name of the vendor
    std::string m_vendorName;
    /// @brief Version of the plugin
    std::string m_pluginVersion;
    /// @brief Required API version for Maya - default Any
    std::string m_requiredAPIVersion;
};

#endif /* __PLUGINTYPECHOICEPAGE_H__ */
