/********************************************************************************
** Form generated from reading UI file 'NodeGraphPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODEGRAPHPAGE_H
#define UI_NODEGRAPHPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NodeGraphPage
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *gbx_graphArea;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *h_graphArea;

    void setupUi(QWidget *NodeGraphPage)
    {
        if (NodeGraphPage->objectName().isEmpty())
            NodeGraphPage->setObjectName(QStringLiteral("NodeGraphPage"));
        NodeGraphPage->resize(595, 432);
        verticalLayout = new QVBoxLayout(NodeGraphPage);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gbx_graphArea = new QGroupBox(NodeGraphPage);
        gbx_graphArea->setObjectName(QStringLiteral("gbx_graphArea"));
        verticalLayout_2 = new QVBoxLayout(gbx_graphArea);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        h_graphArea = new QVBoxLayout();
        h_graphArea->setObjectName(QStringLiteral("h_graphArea"));

        verticalLayout_2->addLayout(h_graphArea);


        verticalLayout->addWidget(gbx_graphArea);


        retranslateUi(NodeGraphPage);

        QMetaObject::connectSlotsByName(NodeGraphPage);
    } // setupUi

    void retranslateUi(QWidget *NodeGraphPage)
    {
        NodeGraphPage->setWindowTitle(QApplication::translate("NodeGraphPage", "Form", 0));
        gbx_graphArea->setTitle(QApplication::translate("NodeGraphPage", "Connect and Add Arguments", 0));
    } // retranslateUi

};

namespace Ui {
    class NodeGraphPage: public Ui_NodeGraphPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEGRAPHPAGE_H
