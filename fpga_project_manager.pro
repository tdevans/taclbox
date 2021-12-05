QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hdlparserarchitecturedefinition.cpp \
    hdlparsercomments.cpp \
    hdlparserentitydefinition.cpp \
    hdlparsergenericdefinition.cpp \
    hdlparsermoduleinstantiation.cpp \
    hdlparserpackagebodydefinition.cpp \
    hdlparserpackageheaderdefinition.cpp \
    hdlparserportdefinition.cpp \
    hdlparsersignaldefinition.cpp \
    hdlparsertypedefinition.cpp \
    hdlparseruseclause.cpp \
    main.cpp \
    mainwindow.cpp \
    preferencesmanager.cpp \
    project.cpp \
    projectmanager.cpp \
    projectsummarywidget.cpp \
    semanticversion.cpp \
    sourcemanager.cpp \
    unittesthdlparserdialog.cpp \
    vhdldependencyparser.cpp

HEADERS += \
    hdlparserarchitecturedefinition.h \
    hdlparsercomments.h \
    hdlparserentitydefinition.h \
    hdlparsergenericdefinition.h \
    hdlparsermoduleinstantiation.h \
    hdlparserpackagebodydefinition.h \
    hdlparserpackageheaderdefinition.h \
    hdlparserportdefinition.h \
    hdlparsersignaldefinition.h \
    hdlparsertypedefinition.h \
    hdlparseruseclause.h \
    mainwindow.h \
    preferencesmanager.h \
    project.h \
    projectmanager.h \
    projectsummarywidget.h \
    semanticversion.h \
    sourcemanager.h \
    unittesthdlparserdialog.h \
    vhdldependencyparser.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui \
    unittesthdlparserdialog.ui

test_data.path = $${OUT_PWD}/test
test_data.files += test/*
INSTALLS += test_data

RESOURCES +=
