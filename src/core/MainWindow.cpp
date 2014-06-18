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

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "IntroPage.h"

#include "Utilities.h"

#include "Generators.h"

#include <QMenu>
#include <QAction>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    nullifyPointers();

    // make sure the stack is empty
    while (!m_pages.empty())
    {
        m_pages.pop();
    }

    m_currentPageNum = 0;

    m_pages.push(new IntroPage(m_currentPageNum,std::string("IntroPage"),NO_PLUGIN_TYPE,this));
    m_ui->lay_pageArea->addWidget(m_pages.top()->getWidget());
    // set button texts
    m_ui->btn_Next->setText(tr(m_pages.top()->getNextButtonText().c_str()));
    m_ui->btn_Back->setText(tr(m_pages.top()->getBackButtonText().c_str()));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

bool MainWindow::connectAndInit()
{
    setBackButtonVisible(false);

    m_preferenceWindow.connectAndInit();
    m_preferenceWindow.setParentWindow(this);
    m_preferenceWindow.readPreferenceFile();

    m_aboutWindow.connectAndInit();
    m_aboutWindow.setParentWindow(this);

    connect(m_ui->btn_Next,SIGNAL(clicked(bool)),this, SLOT(nextPage()));
    connect(m_ui->btn_Back,SIGNAL(clicked(bool)),this, SLOT(previousPage()));
    connect(m_ui->btn_Cancel,SIGNAL(clicked(bool)),this, SLOT(closeWizard()));
    connect(m_ui->actionPreferences,SIGNAL(triggered()),this,SLOT(openPreferences()));
    connect(m_ui->actionAbout_MayaAPIWizard,SIGNAL(triggered()),this,SLOT(openAbout()));

    return true;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if (m_preferenceWindow.isVisible())
    {
        m_preferenceWindow.close();
    }
    if (m_aboutWindow.isVisible())
    {
        m_aboutWindow.close();
    }
}

void MainWindow::nullifyPointers()
{

}

void MainWindow::safeDeleteWizardPage(WizardPage *_pointer)
{
    if (_pointer != NULL)
    {
        delete _pointer;
        _pointer = NULL;
    }
}

void MainWindow::setBackButtonVisible(bool _enabled)
{
    m_ui->btn_Back->setVisible(_enabled);
}

void MainWindow::addPage(WizardPage* _nextPage)
{
    // hide previous widget
    m_pages.top()->getWidget()->setVisible(false);
    m_pages.push(_nextPage);
    m_ui->lay_pageArea->addWidget(m_pages.top()->getWidget());
    // set button texts
    m_ui->btn_Next->setText(tr(m_pages.top()->getNextButtonText().c_str()));
    m_ui->btn_Back->setText(tr(m_pages.top()->getBackButtonText().c_str()));
}

void MainWindow::removePage()
{
    m_ui->lay_pageArea->removeWidget(m_pages.top());
    safeDeleteWizardPage(m_pages.top());
    m_pages.pop();
    m_ui->lay_pageArea->addWidget(m_pages.top()->getWidget());
    // set button texts
    m_ui->btn_Next->setText(tr(m_pages.top()->getNextButtonText().c_str()));
    m_ui->btn_Back->setText(tr(m_pages.top()->getBackButtonText().c_str()));
    // show previously hidden widget
    m_pages.top()->getWidget()->setVisible(true);
}

void MainWindow::nextPage()
{
    // if the button is clicked and we are on the final page, simply close the wizard
    if (m_pages.top()->lastPage())
    {
        closeWizard();
    }

    // first we need to gather the information from the page that is about to be left
    if(WizardError::checkForError(m_pages.top()->gatherInformation(),true,this))
    {
        SourceGenerator* generator = NULL; // prepare a pointer for a generator so it can be seen in scope
        bool generating = false;
        // now check if this is a generation page before adding a new page
        if (m_pages.top()->generatorPage())
        {
            // if it is, we need to call a generator which can be done by querying the type of plugin with the following
            generator = Generators::getPluginGenerator(m_pages.top()->pluginType());
            // once a generator has been created, need to set the stack so it can read all pages
            WizardError::checkForError(generator->setStack(m_pages));
            // now run the generator which will automtaically parse the data and store correctly
            if (!WizardError::checkForError(generator->run()))
            {
                // remove the generator if failed to allow it to be recreated next time
                delete generator;
                // finish this function if failed
                return;
            }
            // set the generating flag so we know to delete it once done
            generating = true;
        }
        // now we can move on a page if this has succeded
        m_currentPageNum++;

        // if the gatherInformation function has passed, we can load the next page
        // now the information is stored, proceed to the next page
        addPage(m_pages.top()->nextPage(m_currentPageNum));

        if (!m_ui->btn_Back->isVisible())
        {
            setBackButtonVisible(true);
        }

        // if the new page is now the final page, set the back button to hide
        if (m_pages.top()->lastPage())
        {
            setBackButtonVisible(false);
        }

        // if this action has caused a generation to occur, now delete that generator
        if (generator != NULL)
        {
            delete generator;
        }
    }
}

void MainWindow::previousPage()
{
    // if we are returning back from the final page, set the button back to say next
    if (m_pages.top()->lastPage())
    {
        m_ui->btn_Next->setText(tr("Next"));
    }

    removePage();
    m_currentPageNum--;

    if (m_currentPageNum <= 0)
    {
        setBackButtonVisible(false);
        m_currentPageNum = 0;
    }
}

void MainWindow::closeWizard()
{
    exit(EXIT_SUCCESS);
}

void MainWindow::openPreferences()
{
    if (m_preferenceWindow.isVisible())
    {
        m_preferenceWindow.raise();
    }
    else
    {
        // only need to read the preference file when you repopen the window
        // as the preferences can't be changed unless the window is closed
        m_preferenceWindow.readPreferenceFile();
        m_preferenceWindow.show();
    }
}

void MainWindow::openAbout()
{
    if (m_aboutWindow.isVisible())
    {
        m_aboutWindow.raise();
    }
    else
    {
        m_aboutWindow.show();
    }
}
