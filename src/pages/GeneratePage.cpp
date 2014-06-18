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

#include "GeneratePage.h"
#include "ui_GeneratePage.h"

#include "FinishPage.h"

#include "Utilities.h"

#include "MainWindow.h"

#include <iostream>
#include <QFileDialog>

GeneratePage::GeneratePage(int _id, std::string _name, PLUGIN_TYPE _type, MainWindow* _parentWindow, QWidget *_parent) :
    WizardPage(_name, _type, _id, _parent, _parentWindow), m_ui(new Ui::GeneratePage)
{
    m_ui->setupUi(this);
    setID(_id);

    connectAndInit();

    setNextButtonText("Generate");
}

GeneratePage::~GeneratePage()
{
    delete m_ui;
}

std::string GeneratePage::getAttributes()
{
    std::string returnString = "";
    returnString += std::string(m_createInDir + ATTRIB_DELIM);
    returnString += std::string(Utilities::boolToString(m_generateQtProject) + ATTRIB_DELIM);
    returnString += std::string(Utilities::boolToString(m_generateCmake) + ATTRIB_DELIM);
    returnString += std::string(Utilities::boolToString(m_makeNewDir) + ATTRIB_DELIM);
    return returnString;
}

void GeneratePage::connectAndInit()
{
    // init all variables used to gather data
    m_createInDir = getParentMainWindow()->getPreferenceWindow()->creationDir();
    m_generateCmake = getParentMainWindow()->getPreferenceWindow()->genCMakeFile();
    m_generateQtProject = getParentMainWindow()->getPreferenceWindow()->genQtProject();
    m_makeNewDir = getParentMainWindow()->getPreferenceWindow()->createNewDir();

    connect(m_ui->btn_browseForCreationDir,SIGNAL(clicked(bool)),this,SLOT(browseForDirectory()));

    m_ui->line_creationDir->setText(QString(m_createInDir.c_str()));
    m_ui->cbx_genQtProject->setChecked(m_generateQtProject);
    m_ui->cbx_genCMake->setChecked(m_generateCmake);
    m_ui->cbx_createDir->setChecked(m_makeNewDir);
}

WizardPage* GeneratePage::nextPage(int _id)
{
    // the intro page will always lead on into the plugin choice page
    return new FinishPage(_id,"Finish",NO_PLUGIN_TYPE,getParentMainWindow());
}

WizardError::WIZARD_ERROR_CODE GeneratePage::gatherInformation()
{
    // do some checks here to make sure a directory has been given to create the files in
    QString dir = m_ui->line_creationDir->text();
    if (dir.isEmpty())
    {
        return WizardError::ERR_NO_PATH_SPECIFIED;
    }
    // if we have got to this point, everything is groovy so continue and gather the information
    m_createInDir = dir.toStdString();
    m_generateQtProject = m_ui->cbx_genQtProject->isChecked();
    m_generateCmake = m_ui->cbx_genCMake->isChecked();
    m_makeNewDir = m_ui->cbx_createDir->isChecked();
    return WizardError::NO_ERROR;
}

void GeneratePage::browseForDirectory()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,tr("Create in"),tr(""),options);

    if (!directory.isEmpty())
    {
        m_ui->line_creationDir->setText(directory);
    }
}
