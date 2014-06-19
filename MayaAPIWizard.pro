TARGET=MayaAPIWizard

MOC_DIR=moc
OBJECTS_DIR = obj

UI_DIR=ui
UI_HEADERS_DIR=ui
QT+= opengl gui core

INC_DIR = include
NODE_GRAPH_DIR = ext-src/nodegraph
SRC_DIR = src
FORM_DIR = ui
PAGES_DIR = pages
RESOURCE_DIR = res
GENER_DIR = generators
JSON_DIR = res/templateFramework

DEBUG = 0
NOMAYABUILD = 0

BOOST_INCLUDE_DIR = /usr/local/include
BOOST_LIB_DIR = /usr/local/lib

isEqual(DEBUG,0){
    DEFINES += WIZ_RELEASE
}
isEqual(DEBUG,1){
    DEFINES += WIZ_DEBUG
}

INCLUDEPATH +=  . \
                $$INC_DIR \
                $$FORM_DIR \
                $$INC_DIR/menu \
                $$INC_DIR/core \
                $$INC_DIR/utils \
                $$INC_DIR/$$PAGES_DIR \
                $$INC_DIR/$$GENER_DIR \
                $$NODE_GRAPH_DIR/include \

unix:!macx{
    DEFINES += LINUX
    # include path for boost
    INCLUDEPATH += $$BOOST_INCLUDE_DIR
    # boost filesystem libraries
    isEqual(NOMAYABUILD,1){
        DEFINES += SKIP_MAYA_TEST
    }
    LIBS += -L$$BOOST_LIB_DIR -lboost_filesystem -lboost_system
    LIBS += -L$$NODE_GRAPH_DIR/lib/linux -lNodeGraph
}
macx:{
    DEFINES += DARWIN
    # include path for boost
    INCLUDEPATH += $$BOOST_INCLUDE_DIR
    # add frameworks required
    LIBS += -framework Cocoa
    # boost filesystem libraries
    LIBS += -L$$BOOST_LIB_DIR -lboost_filesystem -lboost_system
    # include the libraries for the NodeGraph
    LIBS += -L$$NODE_GRAPH_DIR/lib/macosx -lNodeGraph
}

HEADERS+=   $$INC_DIR/core/MainWindow.h \
            $$INC_DIR/$$PAGES_DIR/IntroPage.h \
            $$INC_DIR/$$PAGES_DIR/PluginTypeChoicePage.h \
            $$INC_DIR/utils/Utilities.h \
            $$INC_DIR/$$PAGES_DIR/WizardPage.h \
            $$INC_DIR/utils/Types.h \
            $$INC_DIR/$$PAGES_DIR/GeneratePage.h \
            $$INC_DIR/$$PAGES_DIR/FinishPage.h \
            $$INC_DIR/core/PageIncludes.h \
            $$INC_DIR/utils/ErrorCodes.h \
            $$INC_DIR/$$PAGES_DIR/LinkLibrariesPage.h \
            $$INC_DIR/$$GENER_DIR/SourceGenerator.h \
            $$INC_DIR/$$PAGES_DIR/CommandPlugin.h \
            $$INC_DIR/$$GENER_DIR/Generators.h \
            $$INC_DIR/$$GENER_DIR/CommandPluginGenerator.h \
            $$INC_DIR/$$PAGES_DIR/NodeGraphPage.h \
            $$INC_DIR/$$PAGES_DIR/FileTranslatorPlugin.h \
            $$INC_DIR/$$GENER_DIR/FileTranslatorPluginGenerator.h \
            $$INC_DIR/$$PAGES_DIR/NodePluginSelectionPage.h \
            $$INC_DIR/$$GENER_DIR/NodePluginGenerator.h \
            $$INC_DIR/$$PAGES_DIR/SWShaderPage.h \
            $$INC_DIR/$$GENER_DIR/SWShaderPluginGenerator.h \
            $$INC_DIR/$$GENER_DIR/HWShaderPluginGenerator.h \
            $$INC_DIR/$$PAGES_DIR/HWShaderPage.h \
            $$INC_DIR/$$GENER_DIR/EmitterPluginGenerator.h \
            $$INC_DIR/$$PAGES_DIR/EmitterPluginPage.h \
            $$INC_DIR/menu/PreferencesWindow.h \
            $$INC_DIR/menu/AboutWindow.h

SOURCES +=  $$SRC_DIR/core/main.cpp \
            $$SRC_DIR/core/MainWindow.cpp \
            $$SRC_DIR/$$PAGES_DIR/IntroPage.cpp \
            $$SRC_DIR/$$PAGES_DIR/PluginTypeChoicePage.cpp \
            $$SRC_DIR/utils/Utilities.cpp \
            $$SRC_DIR/$$PAGES_DIR/WizardPage.cpp \
            $$SRC_DIR/$$PAGES_DIR/GeneratePage.cpp \
            $$SRC_DIR/$$PAGES_DIR/FinishPage.cpp \
            $$SRC_DIR/utils/ErrorCodes.cpp \
            $$SRC_DIR/$$PAGES_DIR/LinkLibrariesPage.cpp \
            $$SRC_DIR/$$GENER_DIR/SourceGenerator.cpp \
            $$SRC_DIR/$$PAGES_DIR/CommandPlugin.cpp \
            $$SRC_DIR/$$GENER_DIR/Generators.cpp \
            $$SRC_DIR/$$GENER_DIR/CommandPluginGenerator.cpp \
            $$SRC_DIR/$$PAGES_DIR/NodeGraphPage.cpp \
            $$SRC_DIR/$$PAGES_DIR/FileTranslatorPlugin.cpp \
            $$SRC_DIR/$$GENER_DIR/FileTranslatorPluginGenerator.cpp \
            $$SRC_DIR/$$PAGES_DIR/NodePluginSelectionPage.cpp \
            $$SRC_DIR/$$GENER_DIR/NodePluginGenerator.cpp \
            $$SRC_DIR/$$PAGES_DIR/SWShaderPage.cpp \
            $$SRC_DIR/$$GENER_DIR/SWShaderPluginGenerator.cpp \
            $$SRC_DIR/$$GENER_DIR/HWShaderPluginGenerator.cpp \
            $$SRC_DIR/$$PAGES_DIR/HWShaderPage.cpp \
            $$SRC_DIR/$$GENER_DIR/EmitterPluginGenerator.cpp \
            $$SRC_DIR/$$PAGES_DIR/EmitterPluginPage.cpp \
            $$SRC_DIR/menu/PreferencesWindow.cpp \
            $$SRC_DIR/menu/AboutWindow.cpp

PREFERENCES +=  res/preferences.mwp

OTHER_FILES +=  $$PREFERENCES

FORMS +=    $$FORM_DIR/MainWindow.ui \
    	    $$FORM_DIR/IntroPage.ui \
            $$FORM_DIR/PluginTypeChoicePage.ui \
            $$FORM_DIR/GeneratePage.ui \
            $$FORM_DIR/FinishPage.ui \
            $$FORM_DIR/LinkLibrariesPage.ui \
            $$FORM_DIR/CommandPlugin.ui \
            $$FORM_DIR/NodeGraphPage.ui \
            $$FORM_DIR/FileTranslatorPlugin.ui \
            $$FORM_DIR/NodePluginSelectionPage.ui \
            $$FORM_DIR/SWShaderPage.ui \
            $$FORM_DIR/HWShaderPage.ui \
            $$FORM_DIR/EmitterPluginPage.ui \
            $$FORM_DIR/PreferencesWindow.ui \
            $$FORM_DIR/AboutWindow.ui

JSON_FILES +=   $$JSON_DIR/plugins/melCommand/main.json \
                $$JSON_DIR/plugins/melCommand/cpp.json \
                $$JSON_DIR/plugins/melCommand/h.json \
                $$JSON_DIR/plugins/fileTranslator/main.json \
                $$JSON_DIR/plugins/fileTranslator/cpp.json \
                $$JSON_DIR/plugins/fileTranslator/h.json \
                $$JSON_DIR/plugins/fileTranslator/uiScript.json \
                $$JSON_DIR/general/coreClassDef.json \
                $$JSON_DIR/general/cmake.json \
                $$JSON_DIR/general/qtproj.json \
                $$JSON_DIR/plugins/node/main.json \
                $$JSON_DIR/plugins/node/cpp.json \
                $$JSON_DIR/plugins/node/h.json \
                $$JSON_DIR/plugins/node/uiTemplateScript.json \
                $$JSON_DIR/plugins/swShader/main.json \
                $$JSON_DIR/plugins/swShader/cpp.json \
                $$JSON_DIR/plugins/swShader/h.json \
                $$JSON_DIR/plugins/swShader/uiScript.json \
                $$JSON_DIR/plugins/hwShader/main.json \
                $$JSON_DIR/plugins/hwShader/cpp.json \
                $$JSON_DIR/plugins/hwShader/h.json \
                $$JSON_DIR/plugins/hwShader/uiScript.json \
                $$JSON_DIR/plugins/hwShader/overrideH.json \
                $$JSON_DIR/plugins/hwShader/overrideCpp.json \
                $$JSON_DIR/plugins/emitter/main.json \
                $$JSON_DIR/plugins/emitter/cpp.json \
                $$JSON_DIR/plugins/emitter/h.json \
                $$JSON_DIR/plugins/emitter/uiTemplateScript.json

OTHER_FILES += $$JSON_FILES

macx:{
    IMG_DIR = res/images
    ICON_DIR = res/icon_0_01.iconset

    IMAGES +=   $$IMG_DIR/intro_logo.png

    ICONS +=    $$ICON_DIR/icon_16x16.png \
                $$ICON_DIR/icon_32x32.png \
                $$ICON_DIR/icon_128x128.png \
                $$ICON_DIR/icon_256x256.png \
                $$ICON_DIR/icon_512x512.png

    APP_IMAGES.path = Contents/Resources/res/images
    APP_IMAGES.files += $$IMAGES

    APP_PREFERENCES.path = Contents/Resources/res
    APP_PREFERENCES.files = $$PREFERENCES

    APP_ICONS.path = Contents/Resources/icon_0_01.iconset
    APP_ICONS.files += $$ICONS

    QMAKE_BUNDLE_DATA +=    APP_IMAGES \
                            APP_ICONS \
                            APP_PREFERENCES
}

RESOURCES +=    $$RESOURCE_DIR/TemplateFramework.qrc

macx:ICON = res/icon_0_01.icns

