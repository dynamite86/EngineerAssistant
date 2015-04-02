#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T11:45:33
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EngineerAssistant
TEMPLATE = app
DESTDIR = $$PWD/test

SOURCES += main.cpp\
           mainWindow.cpp \
           myTableWidget.cpp \
           createNewAttestationDocumentDialog.cpp \
           aboutDialog.cpp \
           createNewCardOfHarmonizationDialog.cpp \
           OneLineTextEdit.cpp \
           machinesManagingDialog.cpp \
           detailManagingDialog.cpp \
           machineEditDialog.cpp \
           detailEditDialog.cpp

HEADERS  += mainWindow.h \
            myTableWidget.h \
            createNewAttestationDocumentDialog.h \
            aboutDialog.h \
            createNewCardOfHarmonizationDialog.h \
            OneLineTextEdit.h \
            machinesManagingDialog.h \
            detailManagingDialog.h \
            machineEditDialog.h \
            detailEditDialog.h

FORMS    += mainWindow.ui \
            createNewAttestationDocumentDialog.ui \
            aboutDialog.ui \
            createNewCardOfHarmonizationDialog.ui \
            machinesManagingDialog.ui \
            detailManagingDialog.ui \
            machineEditDialog.ui \
            detailEditDialog.ui

RESOURCES += resources.qrc

RC_FILE      = win32.rc
OTHER_FILES += win32.rc
