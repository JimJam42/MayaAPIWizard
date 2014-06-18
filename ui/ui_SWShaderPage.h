/********************************************************************************
** Form generated from reading UI file 'SWShaderPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SWSHADERPAGE_H
#define UI_SWSHADERPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SWShaderPage
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *lbl_title;
    QGroupBox *gbx_swOptions;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_className;
    QLineEdit *line_className;
    QGroupBox *gbx_extraObjs;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *cbx_addObjs;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SWShaderPage)
    {
        if (SWShaderPage->objectName().isEmpty())
            SWShaderPage->setObjectName(QStringLiteral("SWShaderPage"));
        SWShaderPage->resize(577, 398);
        verticalLayout = new QVBoxLayout(SWShaderPage);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lbl_title = new QLabel(SWShaderPage);
        lbl_title->setObjectName(QStringLiteral("lbl_title"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lbl_title->setFont(font);

        gridLayout->addWidget(lbl_title, 0, 0, 1, 1);

        gbx_swOptions = new QGroupBox(SWShaderPage);
        gbx_swOptions->setObjectName(QStringLiteral("gbx_swOptions"));
        verticalLayout_2 = new QVBoxLayout(gbx_swOptions);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lbl_className = new QLabel(gbx_swOptions);
        lbl_className->setObjectName(QStringLiteral("lbl_className"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lbl_className->setFont(font1);

        verticalLayout_2->addWidget(lbl_className);

        line_className = new QLineEdit(gbx_swOptions);
        line_className->setObjectName(QStringLiteral("line_className"));

        verticalLayout_2->addWidget(line_className);


        gridLayout->addWidget(gbx_swOptions, 1, 0, 1, 1);

        gbx_extraObjs = new QGroupBox(SWShaderPage);
        gbx_extraObjs->setObjectName(QStringLiteral("gbx_extraObjs"));
        verticalLayout_3 = new QVBoxLayout(gbx_extraObjs);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        cbx_addObjs = new QCheckBox(gbx_extraObjs);
        cbx_addObjs->setObjectName(QStringLiteral("cbx_addObjs"));

        verticalLayout_3->addWidget(cbx_addObjs);


        gridLayout->addWidget(gbx_extraObjs, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(SWShaderPage);

        QMetaObject::connectSlotsByName(SWShaderPage);
    } // setupUi

    void retranslateUi(QWidget *SWShaderPage)
    {
        SWShaderPage->setWindowTitle(QApplication::translate("SWShaderPage", "Form", 0));
        lbl_title->setText(QApplication::translate("SWShaderPage", "Create Software Shader Node", 0));
        gbx_swOptions->setTitle(QApplication::translate("SWShaderPage", "Software Shader Options", 0));
        lbl_className->setText(QApplication::translate("SWShaderPage", "Class Name", 0));
        line_className->setPlaceholderText(QApplication::translate("SWShaderPage", "Enter a class name for the Software Shader", 0));
        gbx_extraObjs->setTitle(QApplication::translate("SWShaderPage", "Extra Objects", 0));
        cbx_addObjs->setText(QApplication::translate("SWShaderPage", "Add objects", 0));
    } // retranslateUi

};

namespace Ui {
    class SWShaderPage: public Ui_SWShaderPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SWSHADERPAGE_H
