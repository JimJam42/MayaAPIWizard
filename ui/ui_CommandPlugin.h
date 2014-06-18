/********************************************************************************
** Form generated from reading UI file 'CommandPlugin.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMANDPLUGIN_H
#define UI_COMMANDPLUGIN_H

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

class Ui_CommandPlugin
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *lbl_cmdPlugTitle;
    QGroupBox *gbox_commandOptions;
    QGridLayout *gridLayout;
    QLabel *lbl_thisIsWhatYouCall;
    QLabel *lbl_command;
    QSpacerItem *horizontalSpacer;
    QLineEdit *line_commandName;
    QLineEdit *line_className;
    QCheckBox *cbx_redoable;
    QLabel *lbl_className;
    QGroupBox *gbox_addAttributesOption;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *cbx_defineCmdLineArgs;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *CommandPlugin)
    {
        if (CommandPlugin->objectName().isEmpty())
            CommandPlugin->setObjectName(QStringLiteral("CommandPlugin"));
        CommandPlugin->resize(614, 451);
        verticalLayout_2 = new QVBoxLayout(CommandPlugin);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbl_cmdPlugTitle = new QLabel(CommandPlugin);
        lbl_cmdPlugTitle->setObjectName(QStringLiteral("lbl_cmdPlugTitle"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lbl_cmdPlugTitle->setFont(font);

        verticalLayout->addWidget(lbl_cmdPlugTitle);

        gbox_commandOptions = new QGroupBox(CommandPlugin);
        gbox_commandOptions->setObjectName(QStringLiteral("gbox_commandOptions"));
        gridLayout = new QGridLayout(gbox_commandOptions);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lbl_thisIsWhatYouCall = new QLabel(gbox_commandOptions);
        lbl_thisIsWhatYouCall->setObjectName(QStringLiteral("lbl_thisIsWhatYouCall"));
        QFont font1;
        font1.setItalic(true);
        lbl_thisIsWhatYouCall->setFont(font1);

        gridLayout->addWidget(lbl_thisIsWhatYouCall, 0, 2, 1, 1);

        lbl_command = new QLabel(gbox_commandOptions);
        lbl_command->setObjectName(QStringLiteral("lbl_command"));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        lbl_command->setFont(font2);

        gridLayout->addWidget(lbl_command, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        line_commandName = new QLineEdit(gbox_commandOptions);
        line_commandName->setObjectName(QStringLiteral("line_commandName"));

        gridLayout->addWidget(line_commandName, 1, 1, 1, 3);

        line_className = new QLineEdit(gbox_commandOptions);
        line_className->setObjectName(QStringLiteral("line_className"));

        gridLayout->addWidget(line_className, 3, 1, 1, 3);

        cbx_redoable = new QCheckBox(gbox_commandOptions);
        cbx_redoable->setObjectName(QStringLiteral("cbx_redoable"));

        gridLayout->addWidget(cbx_redoable, 4, 1, 1, 2);

        lbl_className = new QLabel(gbox_commandOptions);
        lbl_className->setObjectName(QStringLiteral("lbl_className"));
        lbl_className->setFont(font2);

        gridLayout->addWidget(lbl_className, 2, 1, 1, 2);


        verticalLayout->addWidget(gbox_commandOptions);

        gbox_addAttributesOption = new QGroupBox(CommandPlugin);
        gbox_addAttributesOption->setObjectName(QStringLiteral("gbox_addAttributesOption"));
        verticalLayout_3 = new QVBoxLayout(gbox_addAttributesOption);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        cbx_defineCmdLineArgs = new QCheckBox(gbox_addAttributesOption);
        cbx_defineCmdLineArgs->setObjectName(QStringLiteral("cbx_defineCmdLineArgs"));

        verticalLayout_3->addWidget(cbx_defineCmdLineArgs);


        verticalLayout->addWidget(gbox_addAttributesOption);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(CommandPlugin);

        QMetaObject::connectSlotsByName(CommandPlugin);
    } // setupUi

    void retranslateUi(QWidget *CommandPlugin)
    {
        CommandPlugin->setWindowTitle(QApplication::translate("CommandPlugin", "Form", 0));
        lbl_cmdPlugTitle->setText(QApplication::translate("CommandPlugin", "Create a Command Plugin", 0));
        gbox_commandOptions->setTitle(QApplication::translate("CommandPlugin", "Command Options", 0));
        lbl_thisIsWhatYouCall->setText(QApplication::translate("CommandPlugin", "(this is what you will call from Maya)", 0));
        lbl_command->setText(QApplication::translate("CommandPlugin", "Command Name", 0));
        cbx_redoable->setText(QApplication::translate("CommandPlugin", "Command is redoable/undoable", 0));
        lbl_className->setText(QApplication::translate("CommandPlugin", "Command Class Name", 0));
        gbox_addAttributesOption->setTitle(QApplication::translate("CommandPlugin", "Command Line Attributes", 0));
        cbx_defineCmdLineArgs->setText(QApplication::translate("CommandPlugin", "Define Command Line Arguments", 0));
    } // retranslateUi

};

namespace Ui {
    class CommandPlugin: public Ui_CommandPlugin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMANDPLUGIN_H
