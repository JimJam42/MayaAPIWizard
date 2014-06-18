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

#ifndef __WIZARDPAGE_H__
#define __WIZARDPAGE_H__

/// @file WizardPage.h
/// @brief Pure virtual class that is a base function for all pages
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class WizardPage
/// @brief Pure virtual class that is a base function for all pages

#include <QWidget>
#include <stdlib.h>
#include <string>

#include "Types.h"
#include "ErrorCodes.h"

#define ATTRIB_DELIM ";"

class MainWindow;

class WizardPage : public QWidget
{
public:
    /// @brief ctr
    /// @param [in] _name std::string - the name to set the page to
    /// @param [in] _type PLUGIN_TYPE - the type for the page to take on
    /// @param [in] _id int - the id for the page
    /// @param [in] parent QWidget* - parent widget for this page
    /// @param [in] _parentWindow MainWindow* - the parent MainWindow controlling the page
    /// @param [in] _final bool - whether this is the final page or not
    WizardPage(std::string _name, PLUGIN_TYPE _type, int _id, QWidget *parent = 0, MainWindow* _parentWindow = 0, bool _final = false);
    /// @brief dtr
    virtual ~WizardPage();

    // virtual function to be overloaded by all classes inherating this one to return their particular information from their page
    // to do this all the attributes on a page will be built into a single string delimited by ; and then returned
    // this string will then be parsed by the correct generator which will know of the order of the attributes and so can
    // store them to the correct attribute locations
    /// @brief Pure virtual function to get the attributes from the page and return as a string
    /// @returns std::string
    virtual std::string getAttributes() = 0;
    // virtual function to init and connect signals and slots for the widget
    /// @brief Virtual function for connecting all signals and alots and initialising the page
    virtual void connectAndInit();
    // function to overload to return a pointer to the next page class
    // if there are multiple routes possible, it is within this function that this will be calculated
    /// @brief Pure virtual function to procedd and return a pointer to the next page
    /// @returns WizardPage*
    virtual WizardPage* nextPage(int _id) = 0;
    // virtual function to store all information from page fields when the user moves to the next page
    // these can then be used to load back if they return to this page and also quickly pass them to the generator
    // the storing of data within each of the overidden functions will be unique to that page
    // returns true or false dependant on whether the gatherInformation succeeded or failed (possibly due to invalid value)
    /// @brief Pure virtual function for gathering and string the pages information
    /// @returns WizardError::WIZARD_ERROR_CODE
    virtual WizardError::WIZARD_ERROR_CODE gatherInformation() = 0;
    // virtual function to get the default plugin type of the page
    /// @brief Pure virtual function of getting the plugin type for this page
    /// @returns PLUGIN_TYPE
    virtual PLUGIN_TYPE defaultType() = 0;
    // virtual function to return if this page is a generator page or not
    /// @brief Pure virtual function of whether this is a generator page or not
    /// @returns bool
    virtual bool generatorPage() = 0;
    /// @brief Get the widget of this page
    /// @returns QWidget*
    QWidget* getWidget() {return this;}
    /// @brief set the id of this page
    /// @param [in] _id int - the id to set to this page
    inline void setID(int _id) {m_id = _id;}
    /// @brief Set the name of this page
    /// @param [in] _name std::string - name to set to this page
    inline void setName(std::string _name) {m_name = _name;}
    /// @brief Set this as the final page
    /// @param [in] _final bool - whether this is the final page or not
    inline void setFinalPage(bool _final=false) {m_lastPage=_final;}
    /// @brief Set the plugin type for the page
    /// @param [in] _type PLUGIN_TYPE - the type to set
    inline void setPluginType(PLUGIN_TYPE _type) {m_pluginType = _type;}
    /// @brief Get the Id if the page
    /// @returns int
    inline int getID() {return m_id;}

    /// @brief Get the name fo the page
    /// @returns std::string
    inline std::string getName() {return m_name;}

    /// @brief Get the text from the next button
    /// @returns std::string
    inline std::string getNextButtonText() {return m_nextButtonText;}
    /// @brief Get the text from the back button
    /// @returns std::string
    inline std::string getBackButtonText() {return m_backButtonText;}

    /// @brief Get whether this is the last page or not
    /// @returns bool
    inline bool lastPage() {return m_lastPage;}

    /// @brief Get the plugin type for this page
    /// @returns PLUGIN_TYPE
    inline PLUGIN_TYPE pluginType() {return m_pluginType;}

    /// @brief Set the text for the next button on the UI if you wish it to be different
    /// @param [in] _text std::string - text to set
    void setNextButtonText(std::string _text="Next");
    /// @brief Set the text for the back button on the UI if you wish it to be different
    /// @param [in] _text std::string - text to set
    void setBackButtonText(std::string _text="Back");
    /// @brief set parent main window
    /// @param [in] _parent MainWindow* - parent main window
    void setParentMainWindow(MainWindow *_parent);
    /// @brief return the parent main window
    MainWindow* getParentMainWindow() {return m_parentWindow;}

private:
    /// @brief The id of this page
    int m_id;
    /// @brief The name of this page
    std::string m_name;

    // boolean flag to specify if this is the last page. This will only be true for the finished page
    /// @brief Flag of whether this is the last page or not
    bool m_lastPage;

    // strings to hold the text for the next and back buttons for this page
    /// @brief Text to set to the next button
    std::string m_nextButtonText;
    /// @brief Text to set to the back button on the UI
    std::string m_backButtonText;
    /// @brief The plugin type
    PLUGIN_TYPE m_pluginType;
    /// @brief The parent main window
    MainWindow *m_parentWindow;

};

#endif /* __WIZARDPAGE_H__ */
