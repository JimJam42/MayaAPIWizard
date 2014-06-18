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

#include "PreferencesWindow.h"
#include "ui_PreferencesWindow.h"

#include "MainWindow.h"

#include "boost/filesystem.hpp"
#include "boost/foreach.hpp"
#include "boost/tokenizer.hpp"

#include "Utilities.h"

#include "ErrorCodes.h"

#include <fstream>

#include <QFileDialog>

#define NO_PATH_SPECIFIED "_no_path_specified_"

PreferencesWindow::PreferencesWindow(QWidget *parent) : QDialog(parent), m_ui(new Ui::PreferencesWindow)
{
    m_ui->setupUi(this);
}

PreferencesWindow::~PreferencesWindow()
{
    delete m_ui;
}

void PreferencesWindow::connectAndInit()
{
    m_parentWindowConnected = false;

    m_checkMayaDir = true;
    m_genQtProjFile = false;
    m_genCMakeFile = false;
    m_createNewDir = false;

    m_mayaDir = "";
    m_creationDir = "";
    m_vendor = "";

    connect(m_ui->btn_cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(m_ui->btn_save,SIGNAL(clicked(bool)),this,SLOT(savePreferences()));
    connect(m_ui->btn_browseForMayaRootDirectory,SIGNAL(clicked(bool)),this,SLOT(browseForMayaDir()));
    connect(m_ui->btn_browseForGenDir,SIGNAL(clicked(bool)),this,SLOT(browseForGenDir()));
}

void PreferencesWindow::setParentWindow(MainWindow *_parent)
{
    if (_parent)
    {
        m_parentWindow = _parent;
        m_parentWindowConnected = true;
    }
}

void PreferencesWindow::readPreferenceFile()
{
    std::string filePath = Utilities::PLATFORM_FILE_PATH("res/preferences.mwp");

    if (!boost::filesystem::exists(filePath))
    {
        return;
    }

    // if we have reached this stage then the file exists so we just need to read it
    std::ifstream configFile(filePath.c_str());
    std::string content = "";
    if (configFile.is_open())
    {
        content = std::string((std::istreambuf_iterator<char>(configFile)),(std::istreambuf_iterator<char>()));
        configFile.close();
    }
    else
    {
        return;
    }

    std::vector<std::string> fromFile;
    fromFile.clear();

    boost::char_separator<char> delim("\n");
    boost::tokenizer< boost::char_separator<char> > token(content,delim);
    BOOST_FOREACH (const std::string& pref, token)
    {
        boost::char_separator<char> delimSecondPhase("=");
        boost::tokenizer< boost::char_separator<char> > finalToken(pref,delimSecondPhase);

        BOOST_FOREACH (const std::string& value, finalToken)
        {
            fromFile.push_back(value);
        }
    }

    for (int i = 0; i < int(fromFile.size()); i+= 2)
    {
        storeValueFromFile(fromFile.at(i), fromFile.at(i+1));
    }
}

void PreferencesWindow::savePreferences()
{
    // first lets just check to see if the file exists or not
    // if it does exist we shall remove it first, else we will simply create it as normal

    std::string filePath = Utilities::PLATFORM_FILE_PATH("res/preferences.mwp");

    if (boost::filesystem::exists(filePath))
    {
        boost::filesystem::remove(filePath);
    }

    // ok so now we can start afresh, nice and easy
    std::vector<std::string> contents;
    contents.clear();

    // we will simply first build up the string to then write to the preferences file
    // this is as simple as reading through the options on the page and writing the appropriate results
    // start with checking the maya directory
    contents.push_back(std::string("CMD=" + Utilities::boolToString(m_ui->cbx_checkMayaDir->isChecked()) + "\n"));
    // now for qt project as a default
    contents.push_back(std::string("QtP=" + Utilities::boolToString(m_ui->cbx_createQt->isChecked())) + "\n");
    // now  cmakelists.txt as text
    contents.push_back(std::string("CML=" + Utilities::boolToString(m_ui->cbx_createCMake->isChecked())) + "\n");
    // directory creation as default
    contents.push_back(std::string("CND=" + Utilities::boolToString(m_ui->cbx_createNewDir->isChecked())) + "\n");

    // now the path for the maya root directory
    std::string flag = "MRD=";
    std::string path = NO_PATH_SPECIFIED;
    if (m_ui->line_mayaRootDir->text().size() > 0)
    {
        path = m_ui->line_mayaRootDir->text().toStdString();
    }
    contents.push_back(std::string(flag + path + "\n"));
    // now the path for the default generation directory
    path = NO_PATH_SPECIFIED;
    flag = "DGD=";
    if (m_ui->line_genDir->text().size() > 0)
    {
        path = m_ui->line_genDir->text().toStdString();
    }
    contents.push_back(std::string(flag + path + "\n"));
    // now the path for the default vendor
    path = NO_PATH_SPECIFIED;
    flag = "VEN=";
    if (m_ui->line_vendor->text().size() > 0)
    {
        path = m_ui->line_vendor->text().toStdString();
    }
    contents.push_back(std::string(flag + path + "\n"));

    // this is now all the data written to the string
    // and now we need to write it to file
    WizardError::WIZARD_ERROR_CODE error = Utilities::writeVectorToFile(filePath,contents);
    if (error == WizardError::NO_ERROR)
    {
        // now we will read the information back in to try to update some values
        readPreferenceFile();
        close();
    }
    else
    {
        WizardError::checkForError(error);
    }
}

void PreferencesWindow::browseForMayaDir()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,tr("Browse for Maya Root"),tr(""),options);

    if (!directory.isEmpty())
    {
        m_ui->line_mayaRootDir->setText(directory);
    }
}

void PreferencesWindow::browseForGenDir()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(this,tr("Select Generation Directory"),tr(""),options);

    if (!directory.isEmpty())
    {
        m_ui->line_genDir->setText(directory);
    }
}

void PreferencesWindow::storeValueFromFile(std::string _flag, std::string _value)
{
    if (_flag == "CMD")
    {
        bool check = Utilities::stringToBool(_value);
        m_checkMayaDir = check;
        m_ui->cbx_checkMayaDir->setChecked(check);
    }
    else if (_flag == "QtP")
    {
        bool check = Utilities::stringToBool(_value);
        m_genQtProjFile = check;
        m_ui->cbx_createQt->setChecked(check);
    }
    else if (_flag == "CML")
    {
        bool check = Utilities::stringToBool(_value);
        m_genCMakeFile = check;
        m_ui->cbx_createCMake->setChecked(check);
    }
    else if (_flag == "CND")
    {
        bool check = Utilities::stringToBool(_value);
        m_createNewDir = check;
        m_ui->cbx_createNewDir->setChecked(check);
    }
    else if (_flag == "MRD")
    {
        if (_value != NO_PATH_SPECIFIED)
        {
            m_mayaDir = _value;
        }
        else
        {
            m_mayaDir = "";
        }
        m_ui->line_mayaRootDir->setText(QString(m_mayaDir.c_str()));
    }
    else if (_flag == "DGD")
    {
        if (_value != NO_PATH_SPECIFIED)
        {
            m_creationDir = _value;
        }
        else
        {
            m_creationDir = "";
        }
        m_ui->line_genDir->setText(QString(m_creationDir.c_str()));
    }
    else if (_flag == "VEN")
    {
        if (_value != NO_PATH_SPECIFIED)
        {
            m_vendor = _value;
        }
        else
        {
            m_vendor = "";
        }
        m_ui->line_vendor->setText(QString(m_vendor.c_str()));
    }
}
