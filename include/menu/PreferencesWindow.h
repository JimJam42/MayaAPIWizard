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

#ifndef __PREFERENCESWINDOW_H__
#define __PREFERENCESWINDOW_H__

/// @file PreferencesWindow.h
/// @brief Window to allow the user to set certain usage preferences about the Wizard
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 15/05/2014
/// @class PreferencesWindow
/// @brief Preferences window that saves a preference file to allow the same preferences to be used next time.
/// Is also accessible by all pages at run time if they need to load any user preferences

#include <QDialog>

class MainWindow;
/// @brief The UI object for the Preferences Window
namespace Ui
{
    class PreferencesWindow;
}

class PreferencesWindow : public QDialog
{
    Q_OBJECT

public:
    /// @brief ctr
    /// @param [in] parent QWidget* - parent widget
    explicit PreferencesWindow(QWidget *parent = 0);
    /// @brief dtr
    ~PreferencesWindow();
    /// @brief function to initialise the window and connect any signals to the correct slots
    void connectAndInit();
    /// @brief function to set the parent window for this window
    /// @param [in] _parent MainWindow* - the parent main window
    void setParentWindow(MainWindow* _parent);
    /// @brief Function to read the preference file if it exists
    void readPreferenceFile();
    /// @brief returns whether or not to check the maya directory
    /// @returns bool
    bool checkMayaDir() {return m_checkMayaDir;}
    /// @brief returns whether or not to generate a qt project file
    /// @returns bool
    bool genQtProject() {return m_genQtProjFile;}
    /// @brief returns whether or not to generate a cmake file
    /// @returns bool
    bool genCMakeFile() {return m_genCMakeFile;}
    /// @brief returns whether or not to create a new directory
    /// @returns bool
    bool createNewDir() {return m_createNewDir;}

    /// @brief returns the default maya directory
    /// @returns std::string
    std::string mayaDir() {return m_mayaDir;}
    /// @brief returns the default creation directory
    /// @returns std::string
    std::string creationDir() {return m_creationDir;}
    /// @brief returns the default vendor
    /// @returns std::string
    std::string vendor() {return m_vendor;}

private slots:
    /// @brief Private slot to save preferences to file
    void savePreferences();
    /// @brief Function to browse for the default maya directory
    void browseForMayaDir();
    /// @brief Function to browse for the default generation directory
    void browseForGenDir();

private:
    /// @brief The UI object for the window
    Ui::PreferencesWindow *m_ui;
    /// @brief MainWindow pointer to the main window of this window
    MainWindow *m_parentWindow;
    /// @brief Boolean of whether or not the parent window has been set
    bool m_parentWindowConnected;
    /// @brief Whether or not to check the maya directorys validity
    bool m_checkMayaDir;
    /// @brief Whether or not to generate a Qt project file by default
    bool m_genQtProjFile;
    /// @brief Whether or not to generate the CMake file by default
    bool m_genCMakeFile;
    /// @brief Whether or not to create a new directory by default
    bool m_createNewDir;
    /// @brief The default maya directory
    std::string m_mayaDir;
    /// @brief The default creation directory
    std::string m_creationDir;
    /// @brief The default vendor
    std::string m_vendor;
    /// @brief Function to store a value in the correct place based on its flag
    ///@param [in] _flag std::string - the flag of the value
    ///@param [in] _value std::string - the value itself
    void storeValueFromFile(std::string _flag, std::string _value);
};

#endif /* __PREFERENCESWINDOW_H__ */
