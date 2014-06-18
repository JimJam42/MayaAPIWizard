/********************************************************************************
** Form generated from reading UI file 'LinkLibrariesPage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINKLIBRARIESPAGE_H
#define UI_LINKLIBRARIESPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LinkLibrariesPage
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_image;
    QVBoxLayout *verticalLayout;
    QGroupBox *gbox_linkLibraries;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *cbx_foundationLib;
    QCheckBox *cbx_openMayaLib;
    QCheckBox *cbx_openMayaUILib;
    QCheckBox *cbx_openMayaAnimLib;
    QCheckBox *cbx_openMayaFXLib;
    QCheckBox *cbx_openMayaRenderLib;
    QCheckBox *cbx_imageLib;
    QCheckBox *cbx_mocapLib;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *LinkLibrariesPage)
    {
        if (LinkLibrariesPage->objectName().isEmpty())
            LinkLibrariesPage->setObjectName(QStringLiteral("LinkLibrariesPage"));
        LinkLibrariesPage->resize(653, 488);
        gridLayout = new QGridLayout(LinkLibrariesPage);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame = new QFrame(LinkLibrariesPage);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lbl_image = new QLabel(frame);
        lbl_image->setObjectName(QStringLiteral("lbl_image"));
        lbl_image->setPixmap(QPixmap(QString::fromUtf8(":/Framework/pageImage")));
        lbl_image->setScaledContents(true);

        verticalLayout_2->addWidget(lbl_image);


        gridLayout->addWidget(frame, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gbox_linkLibraries = new QGroupBox(LinkLibrariesPage);
        gbox_linkLibraries->setObjectName(QStringLiteral("gbox_linkLibraries"));
        horizontalLayout = new QHBoxLayout(gbox_linkLibraries);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        cbx_foundationLib = new QCheckBox(gbox_linkLibraries);
        cbx_foundationLib->setObjectName(QStringLiteral("cbx_foundationLib"));

        verticalLayout_5->addWidget(cbx_foundationLib);

        cbx_openMayaLib = new QCheckBox(gbox_linkLibraries);
        cbx_openMayaLib->setObjectName(QStringLiteral("cbx_openMayaLib"));

        verticalLayout_5->addWidget(cbx_openMayaLib);

        cbx_openMayaUILib = new QCheckBox(gbox_linkLibraries);
        cbx_openMayaUILib->setObjectName(QStringLiteral("cbx_openMayaUILib"));

        verticalLayout_5->addWidget(cbx_openMayaUILib);

        cbx_openMayaAnimLib = new QCheckBox(gbox_linkLibraries);
        cbx_openMayaAnimLib->setObjectName(QStringLiteral("cbx_openMayaAnimLib"));

        verticalLayout_5->addWidget(cbx_openMayaAnimLib);

        cbx_openMayaFXLib = new QCheckBox(gbox_linkLibraries);
        cbx_openMayaFXLib->setObjectName(QStringLiteral("cbx_openMayaFXLib"));

        verticalLayout_5->addWidget(cbx_openMayaFXLib);

        cbx_openMayaRenderLib = new QCheckBox(gbox_linkLibraries);
        cbx_openMayaRenderLib->setObjectName(QStringLiteral("cbx_openMayaRenderLib"));

        verticalLayout_5->addWidget(cbx_openMayaRenderLib);

        cbx_imageLib = new QCheckBox(gbox_linkLibraries);
        cbx_imageLib->setObjectName(QStringLiteral("cbx_imageLib"));

        verticalLayout_5->addWidget(cbx_imageLib);

        cbx_mocapLib = new QCheckBox(gbox_linkLibraries);
        cbx_mocapLib->setObjectName(QStringLiteral("cbx_mocapLib"));

        verticalLayout_5->addWidget(cbx_mocapLib);


        horizontalLayout->addLayout(verticalLayout_5);


        verticalLayout->addWidget(gbox_linkLibraries);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);


        retranslateUi(LinkLibrariesPage);

        QMetaObject::connectSlotsByName(LinkLibrariesPage);
    } // setupUi

    void retranslateUi(QWidget *LinkLibrariesPage)
    {
        LinkLibrariesPage->setWindowTitle(QApplication::translate("LinkLibrariesPage", "Form", 0));
        lbl_image->setText(QString());
        gbox_linkLibraries->setTitle(QApplication::translate("LinkLibrariesPage", "Link to which libraries:", 0));
        cbx_foundationLib->setText(QApplication::translate("LinkLibrariesPage", "Foundation", 0));
        cbx_openMayaLib->setText(QApplication::translate("LinkLibrariesPage", "OpenMaya", 0));
        cbx_openMayaUILib->setText(QApplication::translate("LinkLibrariesPage", "OpenMayaUI", 0));
        cbx_openMayaAnimLib->setText(QApplication::translate("LinkLibrariesPage", "OpenMayaAnim", 0));
        cbx_openMayaFXLib->setText(QApplication::translate("LinkLibrariesPage", "OpenMayaFX", 0));
        cbx_openMayaRenderLib->setText(QApplication::translate("LinkLibrariesPage", "OpenMayaRender", 0));
        cbx_imageLib->setText(QApplication::translate("LinkLibrariesPage", "Image", 0));
        cbx_mocapLib->setText(QApplication::translate("LinkLibrariesPage", "libMocap", 0));
    } // retranslateUi

};

namespace Ui {
    class LinkLibrariesPage: public Ui_LinkLibrariesPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINKLIBRARIESPAGE_H
