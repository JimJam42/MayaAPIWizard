/********************************************************************************
** Form generated from reading UI file 'EmitterPluginPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMITTERPLUGINPAGE_H
#define UI_EMITTERPLUGINPAGE_H

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

class Ui_EmitterPluginPage
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *lbl_title;
    QGroupBox *gbx_extraObjs;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *cbx_addObjs;
    QGroupBox *gbx_emOptions;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_className;
    QLineEdit *line_className;
    QGroupBox *gbx_emitFn;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QCheckBox *cbx_createEmit;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *EmitterPluginPage)
    {
        if (EmitterPluginPage->objectName().isEmpty())
            EmitterPluginPage->setObjectName(QStringLiteral("EmitterPluginPage"));
        EmitterPluginPage->resize(667, 471);
        verticalLayout = new QVBoxLayout(EmitterPluginPage);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lbl_title = new QLabel(EmitterPluginPage);
        lbl_title->setObjectName(QStringLiteral("lbl_title"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lbl_title->setFont(font);

        gridLayout->addWidget(lbl_title, 0, 0, 1, 1);

        gbx_extraObjs = new QGroupBox(EmitterPluginPage);
        gbx_extraObjs->setObjectName(QStringLiteral("gbx_extraObjs"));
        verticalLayout_3 = new QVBoxLayout(gbx_extraObjs);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        cbx_addObjs = new QCheckBox(gbx_extraObjs);
        cbx_addObjs->setObjectName(QStringLiteral("cbx_addObjs"));

        verticalLayout_3->addWidget(cbx_addObjs);


        gridLayout->addWidget(gbx_extraObjs, 2, 0, 1, 1);

        gbx_emOptions = new QGroupBox(EmitterPluginPage);
        gbx_emOptions->setObjectName(QStringLiteral("gbx_emOptions"));
        verticalLayout_2 = new QVBoxLayout(gbx_emOptions);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lbl_className = new QLabel(gbx_emOptions);
        lbl_className->setObjectName(QStringLiteral("lbl_className"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        lbl_className->setFont(font1);

        verticalLayout_2->addWidget(lbl_className);

        line_className = new QLineEdit(gbx_emOptions);
        line_className->setObjectName(QStringLiteral("line_className"));

        verticalLayout_2->addWidget(line_className);


        gridLayout->addWidget(gbx_emOptions, 1, 0, 1, 1);

        gbx_emitFn = new QGroupBox(EmitterPluginPage);
        gbx_emitFn->setObjectName(QStringLiteral("gbx_emitFn"));
        verticalLayout_4 = new QVBoxLayout(gbx_emitFn);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label = new QLabel(gbx_emitFn);
        label->setObjectName(QStringLiteral("label"));
        QFont font2;
        font2.setPointSize(8);
        font2.setItalic(true);
        label->setFont(font2);

        verticalLayout_4->addWidget(label);

        cbx_createEmit = new QCheckBox(gbx_emitFn);
        cbx_createEmit->setObjectName(QStringLiteral("cbx_createEmit"));

        verticalLayout_4->addWidget(cbx_createEmit);


        gridLayout->addWidget(gbx_emitFn, 3, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(EmitterPluginPage);

        QMetaObject::connectSlotsByName(EmitterPluginPage);
    } // setupUi

    void retranslateUi(QWidget *EmitterPluginPage)
    {
        EmitterPluginPage->setWindowTitle(QApplication::translate("EmitterPluginPage", "Form", 0));
        lbl_title->setText(QApplication::translate("EmitterPluginPage", "Create Emitter Node", 0));
        gbx_extraObjs->setTitle(QApplication::translate("EmitterPluginPage", "Extra Objects", 0));
        cbx_addObjs->setText(QApplication::translate("EmitterPluginPage", "Add objects", 0));
        gbx_emOptions->setTitle(QApplication::translate("EmitterPluginPage", "Emitter Options", 0));
        lbl_className->setText(QApplication::translate("EmitterPluginPage", "Emitter Name", 0));
        line_className->setPlaceholderText(QApplication::translate("EmitterPluginPage", "Enter a class name for the Emitter", 0));
        gbx_emitFn->setTitle(QApplication::translate("EmitterPluginPage", "Emit Function", 0));
        label->setText(QApplication::translate("EmitterPluginPage", "The Wizard will make an educated guess at a default function that could be useful for emitting particles", 0));
        cbx_createEmit->setText(QApplication::translate("EmitterPluginPage", "Create default Emit function", 0));
    } // retranslateUi

};

namespace Ui {
    class EmitterPluginPage: public Ui_EmitterPluginPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMITTERPLUGINPAGE_H
