#-------------------------------------------------
#
# Project created by QtCreator 2014-11-13T18:15:50
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarkEdit
TEMPLATE = app
LIBS += -lmarkdown

SOURCES +=   Source/main.cpp                                  \
             Source/markeditwindow.cpp                        \
             Core/MarkdownConverter/markdownconverter.cpp     \
             Dialogs/InsertLinkDialog/insertlinkdialog.cpp    \
             Dialogs/InsertImageDialog/insertimagedialog.cpp  \
             Dialogs/InsertTableDialog/inserttabledialog.cpp \
    Core/DocumentsHandler/documentshandler.cpp \
    Core/DocumentNode/documentnode.cpp \
    Plugins/MarkdownHighlighter/markdownhighlighter.cpp \
    Dialogs/MarkdownDocumentation/markdowndocumentation.cpp \
    Dialogs/AboutDialog/aboutdialog.cpp \
    Dialogs/SettingsDialog/settingsdialog.cpp \
    Dialogs/ExportPDF/exportpdf.cpp \
    Dialogs/ExportHTML/exporthtml.cpp

HEADERS  +=  Source/markeditwindow.h                          \
             Core/MarkdownConverter/markdownconverter.h       \
             Dialogs/InsertLinkDialog/insertlinkdialog.h      \
             Dialogs/InsertImageDialog/insertimagedialog.h    \
             Dialogs/InsertTableDialog/inserttabledialog.h \
    Core/DocumentsHandler/documentshandler.h \
    Core/DocumentNode/documentnode.h \
    Plugins/MarkdownHighlighter/markdownhighlighter.h \
    Dialogs/MarkdownDocumentation/markdowndocumentation.h \
    Dialogs/AboutDialog/aboutdialog.h \
    Dialogs/SettingsDialog/settingsdialog.h \
    Dialogs/ExportPDF/exportpdf.h \
    Dialogs/ExportHTML/exporthtml.h

FORMS    +=  Source/markeditwindow.ui                         \
             Dialogs/InsertLinkDialog/insertlinkdialog.ui     \
             Dialogs/InsertImageDialog/insertimagedialog.ui   \
             Dialogs/InsertTableDialog/inserttabledialog.ui \
    Dialogs/MarkdownDocumentation/markdowndocumentation.ui \
    Dialogs/AboutDialog/aboutdialog.ui \
    Dialogs/SettingsDialog/settingsdialog.ui \
    Dialogs/ExportPDF/exportpdf.ui \
    Dialogs/ExportHTML/exporthtml.ui

RESOURCES += Resources.qrc

TRANSLATIONS += Translations/MarkEdit_ar.ts \
                Translations/MarkEdit_fr.ts \
