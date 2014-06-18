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

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

/**
  @mainpage MayaAPIWizard for Linux and Mac
  @section intro_sec Introduction
  Welcome to the MayaAPIWizard for Linux and Mac. This wizard will help you get started with the development
  of Maya plugins by generating the core framework for you. Currently, the number of supported plugins is
  limited. However it is very simple to add support for new plugin types. A description of how to do this
  can be found further down this page. You are encouraged to extend and improve the code and add support
  for any new plugin types in Maya. Any modifications, changes or extensions, please email me at calj.james@btinternet.com.

  @section install_sec Installation
  To build this wizard, there a few pre-requisites you will need before beginning. You will need to make sure
  you have installed on your machine the following:
    - The NodeGraph Library built for your platform and in the ext-src/nodegraph/lib
    - The NodeGraph headers in ext-src/nodegraph/include
    - Boost 1.50 or later
    - Qt 5 or later (qmake)
  Once you can tick off this entire list, go to the root directory and run qmake (assuming you have qmake
  set up in your path). Once the make file has been built, run make. The program will build into the
  same directory as you run make from. Dependant on your platform, the executable will be the following:
    - Linux  :   MayaAPIWizard
    - MacOSX :   MayaAPIWizard.app
  Once this has been built, run this executable to get started.

  @section preferences_sec Preferences
  The Wizard has a few configurable options:
    - Check the Maya directory
        - If checked, this will check the supplied Maya directory for validity by checking that MGlobal.h and libOpenMaya exist
    - Generate Qt Project file by default
        - If checked this will set the generate Qt project file option to true when the program is run, unless changed
    - Generate CMakeLists.txt file by default
        - If checked this will set the generate CMake file option to true when the program is run, unless changed
    - Create new directory on generation by default
        - If checked this will set the create new directory option to true when the program is run, unless changed
    - Default Maya directory
        - The default Maya directory
    - Default creation directory
        - The default creation directory
    - Default vendor
        - The default vendor name
  All of these options can be set by opening the Prefrences window (MayaAPIWizard->Preferences : Mac, Edit->Preferences : Linux).
  Preferences are then saved when the save button is clicked.

  @section newplugin_sec Adding New Plugin Types
  To add support for a new plugin type, you need a couple of simple classes. You will need a generator class, where the actual
  generation of the source code is done, a wizard page, where the UI interaction is implemented and a Qt .ui file for
  the wizard page, where the UI is actually laid out.
  The generator class must inherit from SourceGenerator and overwrite the following virtual functions:
    - PLUGIN_TYPE genType()
        - return the plugin type of the new plugin (this will also need to be added to the PLUGIN_TYPE enum in Types.h)
        - the new PLUGIN_TYPE will also need to be added to the pluginTypeName and pluginTypeFromName functions in Utilities
    - WizardError::WIZARD_ERROR_CODE convertAndStoreAttributes()
        - this function should read all values read in from all pages and store them correctly
    - WizardError::WIZARD_ERROR_CODE generate()
        - this function is the meaty one and where the actual generation of source files occur
  The new generator will also need to be added to the getPluginGenerator function in Generators.cpp so that the new generator
  can be called from the plugin type.

  The page must inherit from Wizard page and overwrite the following virtual functions:
    - std::string getAttributes()
        - this function should bring all values from the UI together and return them as one string
        - each value should be delimited by a ;
    - void connectAndInit()
        - function to connect any UI elements to the correct slots and initialise any attributes
    - WizardPage* nextPage(int _id)
        - function to return a pointer to the next page, the id is the value to pass to the next page as its id
    - WizardError::WIZARD_ERROR_CODE gatherInformation()
        - this function should read all UI elements and store their values to appropriate member variables of the class
    - PLUGIN_TYPE defaultType()
        - function to return the default plugin type for this page
    - bool generatorPage()
        - return whether this is a generator page or not
  As long as all of these are overloaded, the WizardPage will run the appropriate functions to pass on the right information.
  The page class must also be added to the PluginTypeChoicePage.h and .cpp. In the defaultSupportedPluginTypes function
  in the .cpp, addSupportedPluginType([plugin_type]) needs to be added. A case for the new plugin type must also be added
  to the nextPage function of the PluginTypeChoicePage.cpp.
  The UI for a new plugin type must be a QWidget that can be added to the main window as a simple widget.

  @section manual_sec User Manual
  For a user manual on how to use the MayaAPIWizard, please find the pdf in the manual folder from the main root directory of the
  wizard.
  **/

/// @file MainWindow.h
/// @brief Main Window class to hold the containers within which all pages are placed
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class MainWindow
/// @brief Main Window class to hold the containers within which all pages are placed. Also
/// handles the stack holding the pages and the running of a generator

#include <QMainWindow>

#include "WizardPage.h"

#include "PreferencesWindow.h"
#include "AboutWindow.h"

#include <stack>

/// @brief Main Window UI
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /// @brief ctr
    /// @param [in] parent QWidget* - parent widget
    explicit MainWindow(QWidget *parent = 0);
    /// @brief dtr
    ~MainWindow();
    /// @brief connect all signals and slots needed and init the class
    bool connectAndInit();
    /// @brief Get the preference window pointer
    PreferencesWindow* getPreferenceWindow() {return &m_preferenceWindow;}

public slots:
    void closeEvent(QCloseEvent *);
    
private:
    /// @brief The UI
    Ui::MainWindow *m_ui;
    /// @brief the Preferences window
    PreferencesWindow m_preferenceWindow;
    /// @brief the About window
    AboutWindow m_aboutWindow;
    /// @brief The current active page number
    int m_currentPageNum;
    /// @brief set all pointer to null - used for init
    void nullifyPointers();
    /// @brief safely deleter a page pointer
    /// @param [in] _pointer WizardPage* - the page to delete
    void safeDeleteWizardPage(WizardPage *_pointer);
    /// @brief Set the back button visibility
    /// @param [in] _enabled bool - visible or not
    void setBackButtonVisible(bool _enabled);

    // pages being used
    /// @brief stack of currently used pages
    std::stack<WizardPage*> m_pages;
    /// @brief add a new page
    /// @param [in] _nextPage WizardPage* - the page to add
    void addPage(WizardPage* _nextPage);
    /// @brief Remove the top page on the stack
    void removePage();

private slots:
    /// @brief Go to the next page
    void nextPage();
    /// @brief Go to the previous page
    void previousPage();
    /// @brief close the wizard
    void closeWizard();
    /// @brief open the preferences dialog
    void openPreferences();
    /// @brief open the about dialog
    void openAbout();
};

#endif /* __MAINWINDOW_H__ */
