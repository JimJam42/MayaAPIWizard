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

#include "LinkLibrariesPage.h"
#include "ui_LinkLibrariesPage.h"

#include "GeneratePage.h"
#include "Utilities.h"

#include "MainWindow.h"

LinkLibrariesPage::LinkLibrariesPage(int _id, std::string _name,  PLUGIN_TYPE _type, ND_TYPE _nodeType, MainWindow* _parentWindow, QWidget *_parent) :
    WizardPage(_name, _type, _id, _parent, _parentWindow), m_ui(new Ui::LinkLibrariesPage)
{
    m_ui->setupUi(this);

    m_nodeType = _nodeType;

    setID(_id);

    connectAndInit();
}

LinkLibrariesPage::~LinkLibrariesPage()
{
    delete m_ui;
}

std::string LinkLibrariesPage::getAttributes()
{
    std::string returnString = "";
    for (unsigned int  i =0; i < m_linkLibraries.size(); i++)
    {
        returnString += std::string(Utilities::libraryTypeName(m_linkLibraries.at(i)) + ATTRIB_DELIM);
    }
    return returnString;
}

void LinkLibrariesPage::connectAndInit()
{
    // ensure the vector for the libraries to link is clear
    m_linkLibraries.clear();
    m_numLibraries = 0;

    // now check and lock all required libraries by the chosen plugin type
    checkAndLockRequiredLibraries();
}

WizardPage* LinkLibrariesPage::nextPage(int _id)
{
    // the intro page will always lead on into the plugin choice page
    return new GeneratePage(_id,"GenerateSource",pluginType(),getParentMainWindow());
}

WizardError::WIZARD_ERROR_CODE LinkLibrariesPage::gatherInformation()
{
    // first ensure the vector of libraries to use is empty so we have only 8 libraries
    m_linkLibraries.clear();
    m_numLibraries = 0;
    // run through all of the check boxes and if checked, store that library to link to
    // if library is not to be linked, store null value to show this but still return 8 values
    pushOnLibrary(m_ui->cbx_foundationLib,LIB_FOUNDATION);
    pushOnLibrary(m_ui->cbx_openMayaLib,LIB_OPEN_MAYA);
    pushOnLibrary(m_ui->cbx_openMayaUILib,LIB_OPEN_MAYA_UI);
    pushOnLibrary(m_ui->cbx_openMayaAnimLib,LIB_OPEN_MAYA_ANIM);
    pushOnLibrary(m_ui->cbx_openMayaFXLib,LIB_OPEN_MAYA_FX);
    pushOnLibrary(m_ui->cbx_openMayaRenderLib,LIB_OPEN_MAYA_RENDER);
    pushOnLibrary(m_ui->cbx_imageLib,LIB_IMAGE);
    pushOnLibrary(m_ui->cbx_mocapLib,LIB_MOCAP);

    return WizardError::NO_ERROR;
}

void LinkLibrariesPage::checkAndLockCbx(QCheckBox *_cbx)
{
    _cbx->setChecked(true);
    _cbx->setEnabled(false);
}

void LinkLibrariesPage::checkAndLockRequiredLibraries()
{
    // every type of plugin should always include the foundation and OpenMaya libraries
    // so check and lock these by default
    checkAndLockCbx(m_ui->cbx_foundationLib);
    checkAndLockCbx(m_ui->cbx_openMayaLib);
    // now check if it is a node plugin
    if (pluginType() == NODE)
    {
        // seeing as this is a node, now we need to check the type of node it is
        // this will have been passed in with the constructor
        if (m_nodeType == ND_LOCATOR_NODE || m_nodeType == ND_MANIP_CONTAIN || m_nodeType == ND_MANIP || m_nodeType == ND_HW_SHADER_NODE)
        {
            checkAndLockCbx(m_ui->cbx_openMayaUILib);
        }
        if (m_nodeType == ND_DEFORMER_NODE || m_nodeType == ND_IK_SOLVER || m_nodeType == ND_CONSTRAINT)
        {
            checkAndLockCbx(m_ui->cbx_openMayaAnimLib);
        }
        if (m_nodeType == ND_PARTICLE_ATTRIB_MAPPER)
        {
            checkAndLockCbx(m_ui->cbx_openMayaFXLib);
        }
    }
    if (pluginType() == SHADER_HW)
    {
        checkAndLockCbx(m_ui->cbx_openMayaUILib);
        checkAndLockCbx(m_ui->cbx_openMayaRenderLib);
    }
    if (pluginType() == EMITTER)
    {
        checkAndLockCbx(m_ui->cbx_openMayaFXLib);
    }
}

void LinkLibrariesPage::pushOnLibrary(QCheckBox *_cbx, MAYA_LIBRARIES _type)
{
    if (_cbx->isChecked())
    {
        m_linkLibraries.push_back(_type);
        m_numLibraries++;
    }
    else
    {
        m_linkLibraries.push_back(NO_LIB_TYPE);
    }
}
