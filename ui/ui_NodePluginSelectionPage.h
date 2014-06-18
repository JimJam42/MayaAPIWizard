/********************************************************************************
** Form generated from reading UI file 'NodePluginSelectionPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODEPLUGINSELECTIONPAGE_H
#define UI_NODEPLUGINSELECTIONPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NodePluginSelectionPage
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *lbl_title;
    QGroupBox *gbx_NodeOptions;
    QGridLayout *gridLayout_2;
    QCheckBox *cbx_addObjs;
    QComboBox *cmbo_nodeType;
    QLabel *lbl_className;
    QLineEdit *line_className;
    QLabel *lbl_nodeType;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *NodePluginSelectionPage)
    {
        if (NodePluginSelectionPage->objectName().isEmpty())
            NodePluginSelectionPage->setObjectName(QStringLiteral("NodePluginSelectionPage"));
        NodePluginSelectionPage->resize(624, 406);
        verticalLayout = new QVBoxLayout(NodePluginSelectionPage);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lbl_title = new QLabel(NodePluginSelectionPage);
        lbl_title->setObjectName(QStringLiteral("lbl_title"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lbl_title->setFont(font);

        gridLayout->addWidget(lbl_title, 0, 0, 1, 1);

        gbx_NodeOptions = new QGroupBox(NodePluginSelectionPage);
        gbx_NodeOptions->setObjectName(QStringLiteral("gbx_NodeOptions"));
        gridLayout_2 = new QGridLayout(gbx_NodeOptions);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        cbx_addObjs = new QCheckBox(gbx_NodeOptions);
        cbx_addObjs->setObjectName(QStringLiteral("cbx_addObjs"));

        gridLayout_2->addWidget(cbx_addObjs, 4, 0, 1, 2);

        cmbo_nodeType = new QComboBox(gbx_NodeOptions);
        cmbo_nodeType->setObjectName(QStringLiteral("cmbo_nodeType"));

        gridLayout_2->addWidget(cmbo_nodeType, 3, 0, 1, 2);

        lbl_className = new QLabel(gbx_NodeOptions);
        lbl_className->setObjectName(QStringLiteral("lbl_className"));

        gridLayout_2->addWidget(lbl_className, 0, 0, 1, 2);

        line_className = new QLineEdit(gbx_NodeOptions);
        line_className->setObjectName(QStringLiteral("line_className"));

        gridLayout_2->addWidget(line_className, 1, 0, 1, 2);

        lbl_nodeType = new QLabel(gbx_NodeOptions);
        lbl_nodeType->setObjectName(QStringLiteral("lbl_nodeType"));

        gridLayout_2->addWidget(lbl_nodeType, 2, 0, 1, 2);


        gridLayout->addWidget(gbx_NodeOptions, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(NodePluginSelectionPage);

        QMetaObject::connectSlotsByName(NodePluginSelectionPage);
    } // setupUi

    void retranslateUi(QWidget *NodePluginSelectionPage)
    {
        NodePluginSelectionPage->setWindowTitle(QApplication::translate("NodePluginSelectionPage", "Form", 0));
        lbl_title->setText(QApplication::translate("NodePluginSelectionPage", "Create a Node Plugin", 0));
        gbx_NodeOptions->setTitle(QApplication::translate("NodePluginSelectionPage", "Node Plugin Options", 0));
        cbx_addObjs->setText(QApplication::translate("NodePluginSelectionPage", "Add objects", 0));
        lbl_className->setText(QApplication::translate("NodePluginSelectionPage", "Class Name", 0));
        line_className->setPlaceholderText(QApplication::translate("NodePluginSelectionPage", "Enter name for Node class", 0));
        lbl_nodeType->setText(QApplication::translate("NodePluginSelectionPage", "Select Node type to make", 0));
    } // retranslateUi

};

namespace Ui {
    class NodePluginSelectionPage: public Ui_NodePluginSelectionPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEPLUGINSELECTIONPAGE_H
