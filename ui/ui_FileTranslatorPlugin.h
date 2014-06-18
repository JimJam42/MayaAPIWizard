/********************************************************************************
** Form generated from reading UI file 'FileTranslatorPlugin.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILETRANSLATORPLUGIN_H
#define UI_FILETRANSLATORPLUGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileTranslatorPlugin
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *lbl_fileTransTitle;
    QGroupBox *gbx_fileTransOptions;
    QGridLayout *gridLayout;
    QLabel *lbl_className;
    QLineEdit *line_uiScriptName;
    QLabel *lbl_transName;
    QLineEdit *line_transName;
    QLineEdit *line_className;
    QLabel *lbl_uiScriptName;
    QLineEdit *line_fileExt;
    QLabel *lbl_impExp;
    QLabel *lbl_defExt;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *rdio_Import;
    QRadioButton *rdio_export;
    QRadioButton *rdio_impExp;
    QGroupBox *gbx_addPribAttribs;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *cbx_addPrivAttribs;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *FileTranslatorPlugin)
    {
        if (FileTranslatorPlugin->objectName().isEmpty())
            FileTranslatorPlugin->setObjectName(QStringLiteral("FileTranslatorPlugin"));
        FileTranslatorPlugin->resize(661, 499);
        verticalLayout_2 = new QVBoxLayout(FileTranslatorPlugin);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbl_fileTransTitle = new QLabel(FileTranslatorPlugin);
        lbl_fileTransTitle->setObjectName(QStringLiteral("lbl_fileTransTitle"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lbl_fileTransTitle->setFont(font);

        verticalLayout->addWidget(lbl_fileTransTitle);

        gbx_fileTransOptions = new QGroupBox(FileTranslatorPlugin);
        gbx_fileTransOptions->setObjectName(QStringLiteral("gbx_fileTransOptions"));
        gridLayout = new QGridLayout(gbx_fileTransOptions);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lbl_className = new QLabel(gbx_fileTransOptions);
        lbl_className->setObjectName(QStringLiteral("lbl_className"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lbl_className->setFont(font1);

        gridLayout->addWidget(lbl_className, 0, 0, 1, 3);

        line_uiScriptName = new QLineEdit(gbx_fileTransOptions);
        line_uiScriptName->setObjectName(QStringLiteral("line_uiScriptName"));

        gridLayout->addWidget(line_uiScriptName, 5, 0, 1, 3);

        lbl_transName = new QLabel(gbx_fileTransOptions);
        lbl_transName->setObjectName(QStringLiteral("lbl_transName"));
        lbl_transName->setFont(font1);

        gridLayout->addWidget(lbl_transName, 2, 0, 1, 3);

        line_transName = new QLineEdit(gbx_fileTransOptions);
        line_transName->setObjectName(QStringLiteral("line_transName"));

        gridLayout->addWidget(line_transName, 3, 0, 1, 3);

        line_className = new QLineEdit(gbx_fileTransOptions);
        line_className->setObjectName(QStringLiteral("line_className"));

        gridLayout->addWidget(line_className, 1, 0, 1, 3);

        lbl_uiScriptName = new QLabel(gbx_fileTransOptions);
        lbl_uiScriptName->setObjectName(QStringLiteral("lbl_uiScriptName"));
        lbl_uiScriptName->setFont(font1);

        gridLayout->addWidget(lbl_uiScriptName, 4, 0, 1, 3);

        line_fileExt = new QLineEdit(gbx_fileTransOptions);
        line_fileExt->setObjectName(QStringLiteral("line_fileExt"));

        gridLayout->addWidget(line_fileExt, 9, 0, 1, 1);

        lbl_impExp = new QLabel(gbx_fileTransOptions);
        lbl_impExp->setObjectName(QStringLiteral("lbl_impExp"));
        lbl_impExp->setFont(font1);

        gridLayout->addWidget(lbl_impExp, 6, 0, 1, 3);

        lbl_defExt = new QLabel(gbx_fileTransOptions);
        lbl_defExt->setObjectName(QStringLiteral("lbl_defExt"));
        lbl_defExt->setFont(font1);

        gridLayout->addWidget(lbl_defExt, 8, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 9, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        rdio_Import = new QRadioButton(gbx_fileTransOptions);
        rdio_Import->setObjectName(QStringLiteral("rdio_Import"));
        rdio_Import->setChecked(true);

        horizontalLayout_2->addWidget(rdio_Import);

        rdio_export = new QRadioButton(gbx_fileTransOptions);
        rdio_export->setObjectName(QStringLiteral("rdio_export"));

        horizontalLayout_2->addWidget(rdio_export);

        rdio_impExp = new QRadioButton(gbx_fileTransOptions);
        rdio_impExp->setObjectName(QStringLiteral("rdio_impExp"));

        horizontalLayout_2->addWidget(rdio_impExp);


        gridLayout->addLayout(horizontalLayout_2, 7, 0, 1, 2);

        gbx_addPribAttribs = new QGroupBox(gbx_fileTransOptions);
        gbx_addPribAttribs->setObjectName(QStringLiteral("gbx_addPribAttribs"));
        verticalLayout_3 = new QVBoxLayout(gbx_addPribAttribs);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        cbx_addPrivAttribs = new QCheckBox(gbx_addPribAttribs);
        cbx_addPrivAttribs->setObjectName(QStringLiteral("cbx_addPrivAttribs"));

        verticalLayout_3->addWidget(cbx_addPrivAttribs);


        gridLayout->addWidget(gbx_addPribAttribs, 10, 0, 1, 2);


        verticalLayout->addWidget(gbx_fileTransOptions);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        QWidget::setTabOrder(line_className, line_transName);
        QWidget::setTabOrder(line_transName, line_uiScriptName);
        QWidget::setTabOrder(line_uiScriptName, rdio_Import);
        QWidget::setTabOrder(rdio_Import, rdio_export);
        QWidget::setTabOrder(rdio_export, rdio_impExp);
        QWidget::setTabOrder(rdio_impExp, line_fileExt);
        QWidget::setTabOrder(line_fileExt, cbx_addPrivAttribs);

        retranslateUi(FileTranslatorPlugin);

        QMetaObject::connectSlotsByName(FileTranslatorPlugin);
    } // setupUi

    void retranslateUi(QWidget *FileTranslatorPlugin)
    {
        FileTranslatorPlugin->setWindowTitle(QApplication::translate("FileTranslatorPlugin", "Form", 0));
        lbl_fileTransTitle->setText(QApplication::translate("FileTranslatorPlugin", "Create a File Translator Plugin", 0));
        gbx_fileTransOptions->setTitle(QApplication::translate("FileTranslatorPlugin", "File Translator Options", 0));
        lbl_className->setText(QApplication::translate("FileTranslatorPlugin", "Class Name", 0));
        lbl_transName->setText(QApplication::translate("FileTranslatorPlugin", "File Translator Name", 0));
        lbl_uiScriptName->setText(QApplication::translate("FileTranslatorPlugin", "UI Script Name", 0));
        lbl_impExp->setText(QApplication::translate("FileTranslatorPlugin", "Import/Export", 0));
        lbl_defExt->setText(QApplication::translate("FileTranslatorPlugin", "Default File Extension", 0));
        rdio_Import->setText(QApplication::translate("FileTranslatorPlugin", "Import", 0));
        rdio_export->setText(QApplication::translate("FileTranslatorPlugin", "Export", 0));
        rdio_impExp->setText(QApplication::translate("FileTranslatorPlugin", "Import/Export", 0));
        gbx_addPribAttribs->setTitle(QApplication::translate("FileTranslatorPlugin", "Private Attributes", 0));
        cbx_addPrivAttribs->setText(QApplication::translate("FileTranslatorPlugin", "Add private class attributes", 0));
    } // retranslateUi

};

namespace Ui {
    class FileTranslatorPlugin: public Ui_FileTranslatorPlugin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILETRANSLATORPLUGIN_H
