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

#ifndef __HWSHADERPAGE_H__
#define __HWSHADERPAGE_H__

/// @file HWShaderPage.h
/// @brief UI class to gather information to generate a Hardware shader
/// @author Callum James
/// @version 1.0
/// @date 24/03/2014
/// Revision History:
/// Initial Version 12/03/2014
/// @class HWShaderPage
/// @brief UI class to gather information to generate a Hardware shader

#include <QWidget>

#include "WizardPage.h"

/// @brief The ui for this page
namespace Ui
{
    class HWShaderPage;
}

class HWShaderPage : public WizardPage
{
    Q_OBJECT

public:
    /// @brief ctr
    /// @param [in] _id int - the id to set to this page
    /// @param [in] _name std::string - name for this page
    /// @param [in] _type PLUGIN_TYPE - plugin type for this page
    /// @param [in] _parentWindow MainWindow* - the parent MainWindow controlling the page
    /// @param [in] _parent QWidget* - parent widget
    explicit HWShaderPage(int _id, std::string _name, PLUGIN_TYPE _type=NO_PLUGIN_TYPE, MainWindow* _parentWindow = 0, QWidget *_parent = 0);
    /// @brief dtr
    ~HWShaderPage();

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
    PLUGIN_TYPE defaultType() {return SHADER_HW;}
    /// @brief Overriden function to return if this is a generate page or not
    /// @returns bool
    bool generatorPage() {return false;}

private:
    /// @brief The UI
    Ui::HWShaderPage *m_ui;

    /// @brief Name of the main plugin class
    std::string m_hwName;
    /// @brief Name of the shader override class
    std::string m_hwNameOR;
    /// @brief Whether to add objects or not
    bool m_addObjs;
};

#endif /* __HWSHADERPAGE_H__ */
