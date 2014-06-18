/********************************************************************************
** Form generated from reading UI file 'PreferencesWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESWINDOW_H
#define UI_PREFERENCESWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PreferencesWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lbl_pref;
    QFrame *line;
    QGroupBox *gbx_genPrefs;
    QGridLayout *gridLayout_2;
    QCheckBox *cbx_checkMayaDir;
    QCheckBox *cbx_createCMake;
    QCheckBox *cbx_createQt;
    QCheckBox *cbx_createNewDir;
    QFrame *line_3;
    QGroupBox *gbx_paths;
    QGridLayout *gridLayout;
    QLineEdit *line_genDir;
    QLabel *lbl_defaultGenDir;
    QLineEdit *line_vendor;
    QLineEdit *line_mayaRootDir;
    QLabel *lbl_mayaDir;
    QLabel *lbl_defaultVendor;
    QPushButton *btn_browseForMayaRootDirectory;
    QPushButton *btn_browseForGenDir;
    QFrame *line_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_save;
    QPushButton *btn_cancel;

    void setupUi(QDialog *PreferencesWindow)
    {
        if (PreferencesWindow->objectName().isEmpty())
            PreferencesWindow->setObjectName(QStringLiteral("PreferencesWindow"));
        PreferencesWindow->resize(522, 418);
        verticalLayout = new QVBoxLayout(PreferencesWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbl_pref = new QLabel(PreferencesWindow);
        lbl_pref->setObjectName(QStringLiteral("lbl_pref"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lbl_pref->setFont(font);

        verticalLayout->addWidget(lbl_pref);

        line = new QFrame(PreferencesWindow);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        gbx_genPrefs = new QGroupBox(PreferencesWindow);
        gbx_genPrefs->setObjectName(QStringLiteral("gbx_genPrefs"));
        gridLayout_2 = new QGridLayout(gbx_genPrefs);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        cbx_checkMayaDir = new QCheckBox(gbx_genPrefs);
        cbx_checkMayaDir->setObjectName(QStringLiteral("cbx_checkMayaDir"));
        cbx_checkMayaDir->setChecked(true);

        gridLayout_2->addWidget(cbx_checkMayaDir, 0, 0, 1, 1);

        cbx_createCMake = new QCheckBox(gbx_genPrefs);
        cbx_createCMake->setObjectName(QStringLiteral("cbx_createCMake"));

        gridLayout_2->addWidget(cbx_createCMake, 2, 0, 1, 1);

        cbx_createQt = new QCheckBox(gbx_genPrefs);
        cbx_createQt->setObjectName(QStringLiteral("cbx_createQt"));

        gridLayout_2->addWidget(cbx_createQt, 1, 0, 1, 1);

        cbx_createNewDir = new QCheckBox(gbx_genPrefs);
        cbx_createNewDir->setObjectName(QStringLiteral("cbx_createNewDir"));

        gridLayout_2->addWidget(cbx_createNewDir, 3, 0, 1, 1);


        verticalLayout->addWidget(gbx_genPrefs);

        line_3 = new QFrame(PreferencesWindow);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        gbx_paths = new QGroupBox(PreferencesWindow);
        gbx_paths->setObjectName(QStringLiteral("gbx_paths"));
        gridLayout = new QGridLayout(gbx_paths);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        line_genDir = new QLineEdit(gbx_paths);
        line_genDir->setObjectName(QStringLiteral("line_genDir"));

        gridLayout->addWidget(line_genDir, 1, 1, 1, 1);

        lbl_defaultGenDir = new QLabel(gbx_paths);
        lbl_defaultGenDir->setObjectName(QStringLiteral("lbl_defaultGenDir"));

        gridLayout->addWidget(lbl_defaultGenDir, 1, 0, 1, 1);

        line_vendor = new QLineEdit(gbx_paths);
        line_vendor->setObjectName(QStringLiteral("line_vendor"));

        gridLayout->addWidget(line_vendor, 2, 1, 1, 1);

        line_mayaRootDir = new QLineEdit(gbx_paths);
        line_mayaRootDir->setObjectName(QStringLiteral("line_mayaRootDir"));

        gridLayout->addWidget(line_mayaRootDir, 0, 1, 1, 1);

        lbl_mayaDir = new QLabel(gbx_paths);
        lbl_mayaDir->setObjectName(QStringLiteral("lbl_mayaDir"));

        gridLayout->addWidget(lbl_mayaDir, 0, 0, 1, 1);

        lbl_defaultVendor = new QLabel(gbx_paths);
        lbl_defaultVendor->setObjectName(QStringLiteral("lbl_defaultVendor"));

        gridLayout->addWidget(lbl_defaultVendor, 2, 0, 1, 1);

        btn_browseForMayaRootDirectory = new QPushButton(gbx_paths);
        btn_browseForMayaRootDirectory->setObjectName(QStringLiteral("btn_browseForMayaRootDirectory"));

        gridLayout->addWidget(btn_browseForMayaRootDirectory, 0, 2, 1, 1);

        btn_browseForGenDir = new QPushButton(gbx_paths);
        btn_browseForGenDir->setObjectName(QStringLiteral("btn_browseForGenDir"));

        gridLayout->addWidget(btn_browseForGenDir, 1, 2, 1, 1);


        verticalLayout->addWidget(gbx_paths);

        line_2 = new QFrame(PreferencesWindow);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_save = new QPushButton(PreferencesWindow);
        btn_save->setObjectName(QStringLiteral("btn_save"));

        horizontalLayout->addWidget(btn_save);

        btn_cancel = new QPushButton(PreferencesWindow);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));

        horizontalLayout->addWidget(btn_cancel);


        verticalLayout->addLayout(horizontalLayout);

        QWidget::setTabOrder(cbx_checkMayaDir, cbx_createQt);
        QWidget::setTabOrder(cbx_createQt, cbx_createCMake);
        QWidget::setTabOrder(cbx_createCMake, cbx_createNewDir);
        QWidget::setTabOrder(cbx_createNewDir, line_mayaRootDir);
        QWidget::setTabOrder(line_mayaRootDir, btn_browseForMayaRootDirectory);
        QWidget::setTabOrder(btn_browseForMayaRootDirectory, line_genDir);
        QWidget::setTabOrder(line_genDir, btn_browseForGenDir);
        QWidget::setTabOrder(btn_browseForGenDir, line_vendor);
        QWidget::setTabOrder(line_vendor, btn_save);
        QWidget::setTabOrder(btn_save, btn_cancel);

        retranslateUi(PreferencesWindow);

        QMetaObject::connectSlotsByName(PreferencesWindow);
    } // setupUi

    void retranslateUi(QDialog *PreferencesWindow)
    {
        PreferencesWindow->setWindowTitle(QApplication::translate("PreferencesWindow", "Preferences", 0));
        lbl_pref->setText(QApplication::translate("PreferencesWindow", "Wizard Preferences", 0));
        gbx_genPrefs->setTitle(QApplication::translate("PreferencesWindow", "Usage Preferences", 0));
        cbx_checkMayaDir->setText(QApplication::translate("PreferencesWindow", "Check Maya directory", 0));
        cbx_createCMake->setText(QApplication::translate("PreferencesWindow", "Create CMakeList.txt as default", 0));
        cbx_createQt->setText(QApplication::translate("PreferencesWindow", "Create Qt Project as default", 0));
        cbx_createNewDir->setText(QApplication::translate("PreferencesWindow", "Create new directory as default", 0));
        gbx_paths->setTitle(QApplication::translate("PreferencesWindow", "Default Paths", 0));
        lbl_defaultGenDir->setText(QApplication::translate("PreferencesWindow", "Default generation directory", 0));
        lbl_mayaDir->setText(QApplication::translate("PreferencesWindow", "Maya root directory", 0));
        lbl_defaultVendor->setText(QApplication::translate("PreferencesWindow", "Default vendor", 0));
        btn_browseForMayaRootDirectory->setText(QApplication::translate("PreferencesWindow", "...", 0));
        btn_browseForGenDir->setText(QApplication::translate("PreferencesWindow", "...", 0));
        btn_save->setText(QApplication::translate("PreferencesWindow", "Save", 0));
        btn_cancel->setText(QApplication::translate("PreferencesWindow", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class PreferencesWindow: public Ui_PreferencesWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESWINDOW_H
