/********************************************************************************
** Form generated from reading UI file 'AboutWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWINDOW_H
#define UI_ABOUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_AboutWindow
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_close;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_4;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lbl_image;
    QSpacerItem *horizontalSpacer_4;
    QLabel *lbl_mayaAPIWiz;
    QLabel *lbl_version;
    QLabel *lbl_author;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *AboutWindow)
    {
        if (AboutWindow->objectName().isEmpty())
            AboutWindow->setObjectName(QStringLiteral("AboutWindow"));
        AboutWindow->resize(279, 363);
        gridLayout = new QGridLayout(AboutWindow);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        btn_close = new QPushButton(AboutWindow);
        btn_close->setObjectName(QStringLiteral("btn_close"));

        gridLayout->addWidget(btn_close, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        lbl_image = new QLabel(AboutWindow);
        lbl_image->setObjectName(QStringLiteral("lbl_image"));
        lbl_image->setPixmap(QPixmap(QString::fromUtf8(":/Framework/icon128")));

        gridLayout_2->addWidget(lbl_image, 1, 1, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 3, 1, 1);

        lbl_mayaAPIWiz = new QLabel(AboutWindow);
        lbl_mayaAPIWiz->setObjectName(QStringLiteral("lbl_mayaAPIWiz"));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        lbl_mayaAPIWiz->setFont(font);
        lbl_mayaAPIWiz->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_mayaAPIWiz, 0, 0, 1, 4);

        lbl_version = new QLabel(AboutWindow);
        lbl_version->setObjectName(QStringLiteral("lbl_version"));
        lbl_version->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_version, 2, 0, 1, 4);

        lbl_author = new QLabel(AboutWindow);
        lbl_author->setObjectName(QStringLiteral("lbl_author"));
        lbl_author->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lbl_author, 3, 0, 1, 4);

        textBrowser = new QTextBrowser(AboutWindow);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 0));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        QBrush brush1(QColor(237, 237, 237, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        textBrowser->setPalette(palette);
        textBrowser->setFrameShape(QFrame::NoFrame);
        textBrowser->setFrameShadow(QFrame::Plain);
        textBrowser->setTextInteractionFlags(Qt::NoTextInteraction);

        gridLayout_2->addWidget(textBrowser, 4, 0, 1, 4);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 3);


        retranslateUi(AboutWindow);

        QMetaObject::connectSlotsByName(AboutWindow);
    } // setupUi

    void retranslateUi(QDialog *AboutWindow)
    {
        AboutWindow->setWindowTitle(QApplication::translate("AboutWindow", "About MayaAPIWIzard", 0));
        btn_close->setText(QApplication::translate("AboutWindow", "Close", 0));
        lbl_image->setText(QString());
        lbl_mayaAPIWiz->setText(QApplication::translate("AboutWindow", "MayaAPIWizard", 0));
        lbl_version->setText(QApplication::translate("AboutWindow", "version 1.0.0", 0));
        lbl_author->setText(QApplication::translate("AboutWindow", "Author: Callum James James", 0));
        textBrowser->setHtml(QApplication::translate("AboutWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.Lucida Grande UI'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">For any bug reports, improvements, fixes or anything else, email calj.james@btinternet.com</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class AboutWindow: public Ui_AboutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H
