/********************************************************************************
** Form generated from reading UI file 'GeneratePage.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEPAGE_H
#define UI_GENERATEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneratePage
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_image;
    QVBoxLayout *verticalLayout;
    QLabel *lbl_srcGenTitle;
    QFrame *line;
    QGroupBox *gbox_generateMakeFiles;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *cbx_genQtProject;
    QCheckBox *cbx_genCMake;
    QFrame *line_2;
    QGroupBox *gbox_fileCreation;
    QGridLayout *gridLayout_2;
    QLineEdit *line_creationDir;
    QCheckBox *cbx_createDir;
    QPushButton *btn_browseForCreationDir;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *GeneratePage)
    {
        if (GeneratePage->objectName().isEmpty())
            GeneratePage->setObjectName(QStringLiteral("GeneratePage"));
        GeneratePage->resize(642, 518);
        gridLayout = new QGridLayout(GeneratePage);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame = new QFrame(GeneratePage);
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
        lbl_srcGenTitle = new QLabel(GeneratePage);
        lbl_srcGenTitle->setObjectName(QStringLiteral("lbl_srcGenTitle"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        lbl_srcGenTitle->setFont(font);

        verticalLayout->addWidget(lbl_srcGenTitle);

        line = new QFrame(GeneratePage);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        gbox_generateMakeFiles = new QGroupBox(GeneratePage);
        gbox_generateMakeFiles->setObjectName(QStringLiteral("gbox_generateMakeFiles"));
        verticalLayout_3 = new QVBoxLayout(gbox_generateMakeFiles);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        cbx_genQtProject = new QCheckBox(gbox_generateMakeFiles);
        cbx_genQtProject->setObjectName(QStringLiteral("cbx_genQtProject"));

        verticalLayout_3->addWidget(cbx_genQtProject);

        cbx_genCMake = new QCheckBox(gbox_generateMakeFiles);
        cbx_genCMake->setObjectName(QStringLiteral("cbx_genCMake"));

        verticalLayout_3->addWidget(cbx_genCMake);


        verticalLayout->addWidget(gbox_generateMakeFiles);

        line_2 = new QFrame(GeneratePage);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        gbox_fileCreation = new QGroupBox(GeneratePage);
        gbox_fileCreation->setObjectName(QStringLiteral("gbox_fileCreation"));
        gridLayout_2 = new QGridLayout(gbox_fileCreation);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        line_creationDir = new QLineEdit(gbox_fileCreation);
        line_creationDir->setObjectName(QStringLiteral("line_creationDir"));

        gridLayout_2->addWidget(line_creationDir, 0, 0, 1, 1);

        cbx_createDir = new QCheckBox(gbox_fileCreation);
        cbx_createDir->setObjectName(QStringLiteral("cbx_createDir"));

        gridLayout_2->addWidget(cbx_createDir, 1, 0, 1, 1);

        btn_browseForCreationDir = new QPushButton(gbox_fileCreation);
        btn_browseForCreationDir->setObjectName(QStringLiteral("btn_browseForCreationDir"));

        gridLayout_2->addWidget(btn_browseForCreationDir, 0, 1, 1, 1);


        verticalLayout->addWidget(gbox_fileCreation);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);


        retranslateUi(GeneratePage);

        QMetaObject::connectSlotsByName(GeneratePage);
    } // setupUi

    void retranslateUi(QWidget *GeneratePage)
    {
        GeneratePage->setWindowTitle(QApplication::translate("GeneratePage", "Form", 0));
        lbl_image->setText(QString());
        lbl_srcGenTitle->setText(QApplication::translate("GeneratePage", "Source Generation", 0));
        gbox_generateMakeFiles->setTitle(QApplication::translate("GeneratePage", "Generate Project Files", 0));
        cbx_genQtProject->setText(QApplication::translate("GeneratePage", "Qt Project File (.pro)", 0));
        cbx_genCMake->setText(QApplication::translate("GeneratePage", "CMake (CMakeLists.txt)", 0));
        gbox_fileCreation->setTitle(QApplication::translate("GeneratePage", "File Creation", 0));
        cbx_createDir->setText(QApplication::translate("GeneratePage", "Create Directory", 0));
        btn_browseForCreationDir->setText(QApplication::translate("GeneratePage", "Browse", 0));
    } // retranslateUi

};

namespace Ui {
    class GeneratePage: public Ui_GeneratePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEPAGE_H
