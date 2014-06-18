/********************************************************************************
** Form generated from reading UI file 'FinishPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINISHPAGE_H
#define UI_FINISHPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FinishPage
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *lbl_image;
    QHBoxLayout *horizontalLayout;
    QTextBrowser *txt_finishMessage;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *FinishPage)
    {
        if (FinishPage->objectName().isEmpty())
            FinishPage->setObjectName(QStringLiteral("FinishPage"));
        FinishPage->resize(664, 509);
        gridLayout = new QGridLayout(FinishPage);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame = new QFrame(FinishPage);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbl_image = new QLabel(frame);
        lbl_image->setObjectName(QStringLiteral("lbl_image"));
        lbl_image->setPixmap(QPixmap(QString::fromUtf8(":/Framework/pageImage")));
        lbl_image->setScaledContents(true);

        verticalLayout->addWidget(lbl_image);


        gridLayout->addWidget(frame, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        txt_finishMessage = new QTextBrowser(FinishPage);
        txt_finishMessage->setObjectName(QStringLiteral("txt_finishMessage"));
        txt_finishMessage->setAcceptDrops(false);
        txt_finishMessage->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        txt_finishMessage->setFrameShape(QFrame::NoFrame);
        txt_finishMessage->setFrameShadow(QFrame::Plain);
        txt_finishMessage->setTextInteractionFlags(Qt::NoTextInteraction);
        txt_finishMessage->setOpenLinks(false);

        horizontalLayout->addWidget(txt_finishMessage);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);


        retranslateUi(FinishPage);

        QMetaObject::connectSlotsByName(FinishPage);
    } // setupUi

    void retranslateUi(QWidget *FinishPage)
    {
        FinishPage->setWindowTitle(QApplication::translate("FinishPage", "Form", 0));
        lbl_image->setText(QString());
        txt_finishMessage->setHtml(QApplication::translate("FinishPage", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'.Lucida Grande UI';\">Your source files and framework for your Maya plugin have now been generated.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'.Lucida Grande UI';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'.Lucida Grande UI';\">Click Finish to close the wizard!</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class FinishPage: public Ui_FinishPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINISHPAGE_H
