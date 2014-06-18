/********************************************************************************
** Form generated from reading UI file 'Defaults.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEFAULTS_H
#define UI_DEFAULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Defaults
{
public:

    void setupUi(QDialog *Defaults)
    {
        if (Defaults->objectName().isEmpty())
            Defaults->setObjectName(QStringLiteral("Defaults"));
        Defaults->resize(400, 300);

        retranslateUi(Defaults);

        QMetaObject::connectSlotsByName(Defaults);
    } // setupUi

    void retranslateUi(QDialog *Defaults)
    {
        Defaults->setWindowTitle(QApplication::translate("Defaults", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class Defaults: public Ui_Defaults {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEFAULTS_H
