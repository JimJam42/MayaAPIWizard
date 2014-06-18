/********************************************************************************
** Form generated from reading UI file 'HWShaderPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HWSHADERPAGE_H
#define UI_HWSHADERPAGE_H

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

class Ui_HWShaderPage
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *lbl_title;
    QGroupBox *gbx_hwOptions;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_className;
    QLineEdit *line_className;
    QGroupBox *gbx_extraObjs;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *cbx_addObjs;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *HWShaderPage)
    {
        if (HWShaderPage->objectName().isEmpty())
            HWShaderPage->setObjectName(QStringLiteral("HWShaderPage"));
        HWShaderPage->resize(619, 412);
        verticalLayout = new QVBoxLayout(HWShaderPage);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lbl_title = new QLabel(HWShaderPage);
        lbl_title->setObjectName(QStringLiteral("lbl_title"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lbl_title->setFont(font);

        gridLayout->addWidget(lbl_title, 0, 0, 1, 1);

        gbx_hwOptions = new QGroupBox(HWShaderPage);
        gbx_hwOptions->setObjectName(QStringLiteral("gbx_hwOptions"));
        verticalLayout_2 = new QVBoxLayout(gbx_hwOptions);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lbl_className = new QLabel(gbx_hwOptions);
        lbl_className->setObjectName(QStringLiteral("lbl_className"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lbl_className->setFont(font1);

        verticalLayout_2->addWidget(lbl_className);

        line_className = new QLineEdit(gbx_hwOptions);
        line_className->setObjectName(QStringLiteral("line_className"));

        verticalLayout_2->addWidget(line_className);


        gridLayout->addWidget(gbx_hwOptions, 1, 0, 1, 1);

        gbx_extraObjs = new QGroupBox(HWShaderPage);
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


        retranslateUi(HWShaderPage);

        QMetaObject::connectSlotsByName(HWShaderPage);
    } // setupUi

    void retranslateUi(QWidget *HWShaderPage)
    {
        HWShaderPage->setWindowTitle(QApplication::translate("HWShaderPage", "Form", 0));
        lbl_title->setText(QApplication::translate("HWShaderPage", "Create Hardware Shader", 0));
        gbx_hwOptions->setTitle(QApplication::translate("HWShaderPage", "Hardware Shader Options", 0));
        lbl_className->setText(QApplication::translate("HWShaderPage", "Class Name", 0));
        line_className->setPlaceholderText(QApplication::translate("HWShaderPage", "Enter a class name for the Hardware Shader", 0));
        gbx_extraObjs->setTitle(QApplication::translate("HWShaderPage", "Extra Objects", 0));
        cbx_addObjs->setText(QApplication::translate("HWShaderPage", "Add objects", 0));
    } // retranslateUi

};

namespace Ui {
    class HWShaderPage: public Ui_HWShaderPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HWSHADERPAGE_H
