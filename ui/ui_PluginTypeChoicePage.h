/********************************************************************************
** Form generated from reading UI file 'PluginTypeChoicePage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINTYPECHOICEPAGE_H
#define UI_PLUGINTYPECHOICEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PluginTypeChoicePage
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_pluginTypeTitle;
    QFrame *line;
    QGroupBox *gbox_pluginType;
    QVBoxLayout *verticalLayout;
    QComboBox *cmbo_pluginType;
    QFrame *line_2;
    QGroupBox *gbox_mayaLoc;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *line_mayaLoc;
    QPushButton *btn_browseForMayaLoc;
    QFrame *line_3;
    QGroupBox *gbox_vendorName;
    QGridLayout *gridLayout_2;
    QLabel *lbl_pluginVersion;
    QLineEdit *line_pluginVersion;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *line_vendorName;
    QFrame *line_4;
    QGroupBox *gbox_reqAPIVersion;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *line_reqAPIVersion;
    QSpacerItem *verticalSpacer;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QLabel *lbl_image;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *PluginTypeChoicePage)
    {
        if (PluginTypeChoicePage->objectName().isEmpty())
            PluginTypeChoicePage->setObjectName(QStringLiteral("PluginTypeChoicePage"));
        PluginTypeChoicePage->resize(692, 510);
        gridLayout = new QGridLayout(PluginTypeChoicePage);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lbl_pluginTypeTitle = new QLabel(PluginTypeChoicePage);
        lbl_pluginTypeTitle->setObjectName(QStringLiteral("lbl_pluginTypeTitle"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lbl_pluginTypeTitle->setFont(font);

        verticalLayout_2->addWidget(lbl_pluginTypeTitle);

        line = new QFrame(PluginTypeChoicePage);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        gbox_pluginType = new QGroupBox(PluginTypeChoicePage);
        gbox_pluginType->setObjectName(QStringLiteral("gbox_pluginType"));
        verticalLayout = new QVBoxLayout(gbox_pluginType);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        cmbo_pluginType = new QComboBox(gbox_pluginType);
        cmbo_pluginType->setObjectName(QStringLiteral("cmbo_pluginType"));

        verticalLayout->addWidget(cmbo_pluginType);


        verticalLayout_2->addWidget(gbox_pluginType);

        line_2 = new QFrame(PluginTypeChoicePage);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        gbox_mayaLoc = new QGroupBox(PluginTypeChoicePage);
        gbox_mayaLoc->setObjectName(QStringLiteral("gbox_mayaLoc"));
        horizontalLayout_4 = new QHBoxLayout(gbox_mayaLoc);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        line_mayaLoc = new QLineEdit(gbox_mayaLoc);
        line_mayaLoc->setObjectName(QStringLiteral("line_mayaLoc"));

        horizontalLayout_4->addWidget(line_mayaLoc);

        btn_browseForMayaLoc = new QPushButton(gbox_mayaLoc);
        btn_browseForMayaLoc->setObjectName(QStringLiteral("btn_browseForMayaLoc"));

        horizontalLayout_4->addWidget(btn_browseForMayaLoc);


        verticalLayout_2->addWidget(gbox_mayaLoc);

        line_3 = new QFrame(PluginTypeChoicePage);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_3);

        gbox_vendorName = new QGroupBox(PluginTypeChoicePage);
        gbox_vendorName->setObjectName(QStringLiteral("gbox_vendorName"));
        gridLayout_2 = new QGridLayout(gbox_vendorName);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lbl_pluginVersion = new QLabel(gbox_vendorName);
        lbl_pluginVersion->setObjectName(QStringLiteral("lbl_pluginVersion"));

        gridLayout_2->addWidget(lbl_pluginVersion, 2, 0, 1, 1);

        line_pluginVersion = new QLineEdit(gbox_vendorName);
        line_pluginVersion->setObjectName(QStringLiteral("line_pluginVersion"));

        gridLayout_2->addWidget(line_pluginVersion, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        line_vendorName = new QLineEdit(gbox_vendorName);
        line_vendorName->setObjectName(QStringLiteral("line_vendorName"));

        gridLayout_2->addWidget(line_vendorName, 0, 0, 1, 3);


        verticalLayout_2->addWidget(gbox_vendorName);

        line_4 = new QFrame(PluginTypeChoicePage);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_4);

        gbox_reqAPIVersion = new QGroupBox(PluginTypeChoicePage);
        gbox_reqAPIVersion->setObjectName(QStringLiteral("gbox_reqAPIVersion"));
        verticalLayout_4 = new QVBoxLayout(gbox_reqAPIVersion);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        line_reqAPIVersion = new QLineEdit(gbox_reqAPIVersion);
        line_reqAPIVersion->setObjectName(QStringLiteral("line_reqAPIVersion"));

        verticalLayout_4->addWidget(line_reqAPIVersion);


        verticalLayout_2->addWidget(gbox_reqAPIVersion);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        frame = new QFrame(PluginTypeChoicePage);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lbl_image = new QLabel(frame);
        lbl_image->setObjectName(QStringLiteral("lbl_image"));
        lbl_image->setPixmap(QPixmap(QString::fromUtf8(":/Framework/pageImage")));
        lbl_image->setScaledContents(true);

        verticalLayout_3->addWidget(lbl_image);


        gridLayout->addWidget(frame, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);


        retranslateUi(PluginTypeChoicePage);

        QMetaObject::connectSlotsByName(PluginTypeChoicePage);
    } // setupUi

    void retranslateUi(QWidget *PluginTypeChoicePage)
    {
        PluginTypeChoicePage->setWindowTitle(QApplication::translate("PluginTypeChoicePage", "Form", 0));
        lbl_pluginTypeTitle->setText(QApplication::translate("PluginTypeChoicePage", "Plugin Type", 0));
        gbox_pluginType->setTitle(QApplication::translate("PluginTypeChoicePage", "Choose Plugin Type", 0));
        gbox_mayaLoc->setTitle(QApplication::translate("PluginTypeChoicePage", "Maya Root Directory", 0));
        btn_browseForMayaLoc->setText(QApplication::translate("PluginTypeChoicePage", "Browse", 0));
        gbox_vendorName->setTitle(QApplication::translate("PluginTypeChoicePage", "Vendor Name for Plugin", 0));
        lbl_pluginVersion->setText(QApplication::translate("PluginTypeChoicePage", "Plugin Version: ", 0));
        line_pluginVersion->setText(QApplication::translate("PluginTypeChoicePage", "1.0", 0));
        gbox_reqAPIVersion->setTitle(QApplication::translate("PluginTypeChoicePage", "Required API Version", 0));
        line_reqAPIVersion->setText(QApplication::translate("PluginTypeChoicePage", "Any", 0));
        lbl_image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PluginTypeChoicePage: public Ui_PluginTypeChoicePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINTYPECHOICEPAGE_H
