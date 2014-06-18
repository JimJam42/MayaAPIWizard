/********************************************************************************
** Form generated from reading UI file 'IntroPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTROPAGE_H
#define UI_INTROPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntroPage
{
public:
    QGridLayout *gridLayout_2;
    QTextBrowser *txt_introMessage;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *lbl_image;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *IntroPage)
    {
        if (IntroPage->objectName().isEmpty())
            IntroPage->setObjectName(QStringLiteral("IntroPage"));
        IntroPage->resize(718, 511);
        gridLayout_2 = new QGridLayout(IntroPage);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        txt_introMessage = new QTextBrowser(IntroPage);
        txt_introMessage->setObjectName(QStringLiteral("txt_introMessage"));
        QFont font;
        font.setFamily(QStringLiteral("Lohit Telugu"));
        font.setPointSize(3);
        txt_introMessage->setFont(font);
        txt_introMessage->setAcceptDrops(false);
        txt_introMessage->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        txt_introMessage->setFrameShape(QFrame::NoFrame);
        txt_introMessage->setFrameShadow(QFrame::Plain);
        txt_introMessage->setTextInteractionFlags(Qt::NoTextInteraction);
        txt_introMessage->setOpenLinks(false);

        gridLayout_2->addWidget(txt_introMessage, 0, 1, 1, 1);

        frame = new QFrame(IntroPage);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lbl_image = new QLabel(frame);
        lbl_image->setObjectName(QStringLiteral("lbl_image"));
        lbl_image->setPixmap(QPixmap(QString::fromUtf8(":/Framework/pageImage")));
        lbl_image->setScaledContents(true);

        gridLayout->addWidget(lbl_image, 0, 0, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);


        retranslateUi(IntroPage);

        QMetaObject::connectSlotsByName(IntroPage);
    } // setupUi

    void retranslateUi(QWidget *IntroPage)
    {
        IntroPage->setWindowTitle(QApplication::translate("IntroPage", "Form", 0));
        txt_introMessage->setHtml(QApplication::translate("IntroPage", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Lohit Telugu'; font-size:3pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'.Lucida Grande UI'; font-size:10pt;\">Welcome to the Maya API Wizard!</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'.Lucida Grande UI'; font-size:10pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'.Lucida Grande UI'; font-size:10pt;\">This Wizard will guide you through some simple steps to"
                        " get you started writing a Maya plugin. </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'.Lucida Grande UI'; font-size:10pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'.Lucida Grande UI'; font-size:10pt;\">The Wizard will let you configure your basic plugin framework to make things as smooth as possible. </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'.Lucida Grande UI'; font-size:10pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'.Lucida Grande UI'; font-size:10pt;\">Click Start to begin.</span></p></body></html>", 0));
        lbl_image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class IntroPage: public Ui_IntroPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTROPAGE_H
