/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionPreferences;
    QAction *actionAbout_MayaAPIWizard;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *lay_pageArea;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hrzLay_ctrlButtons;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_Back;
    QPushButton *btn_Next;
    QPushButton *btn_Cancel;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuEdit;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionPreferences = new QAction(MainWindow);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionPreferences->setMenuRole(QAction::PreferencesRole);
        actionAbout_MayaAPIWizard = new QAction(MainWindow);
        actionAbout_MayaAPIWizard->setObjectName(QStringLiteral("actionAbout_MayaAPIWizard"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lay_pageArea = new QHBoxLayout();
        lay_pageArea->setObjectName(QStringLiteral("lay_pageArea"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        lay_pageArea->addItem(verticalSpacer);


        verticalLayout->addLayout(lay_pageArea);

        hrzLay_ctrlButtons = new QHBoxLayout();
        hrzLay_ctrlButtons->setObjectName(QStringLiteral("hrzLay_ctrlButtons"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hrzLay_ctrlButtons->addItem(horizontalSpacer);

        btn_Back = new QPushButton(centralwidget);
        btn_Back->setObjectName(QStringLiteral("btn_Back"));
        btn_Back->setFlat(false);

        hrzLay_ctrlButtons->addWidget(btn_Back);

        btn_Next = new QPushButton(centralwidget);
        btn_Next->setObjectName(QStringLiteral("btn_Next"));

        hrzLay_ctrlButtons->addWidget(btn_Next);

        btn_Cancel = new QPushButton(centralwidget);
        btn_Cancel->setObjectName(QStringLiteral("btn_Cancel"));

        hrzLay_ctrlButtons->addWidget(btn_Cancel);


        verticalLayout->addLayout(hrzLay_ctrlButtons);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 25));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuEdit->addAction(actionPreferences);
        menuHelp->addAction(actionAbout_MayaAPIWizard);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Maya API Wizard", 0));
        actionPreferences->setText(QApplication::translate("MainWindow", "Preferences", 0));
        actionAbout_MayaAPIWizard->setText(QApplication::translate("MainWindow", "About MayaAPIWizard", 0));
        btn_Back->setText(QApplication::translate("MainWindow", "Back", 0));
        btn_Next->setText(QApplication::translate("MainWindow", "Next", 0));
        btn_Cancel->setText(QApplication::translate("MainWindow", "Cancel", 0));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
