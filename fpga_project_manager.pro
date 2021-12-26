QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hdlfile.cpp \
    hdlfiletreewidgetitem.cpp \
    hdlparserarchitecturedefinition.cpp \
    hdlparsercomments.cpp \
    hdlparserentitydefinition.cpp \
    hdlparsergenericdefinition.cpp \
    hdlparserlibrary.cpp \
    hdlparsermoduleinstantiation.cpp \
    hdlparserpackagebodydefinition.cpp \
    hdlparserpackageheaderdefinition.cpp \
    hdlparserportdefinition.cpp \
    hdlparserportdirection.cpp \
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
    texteditorwidget.cpp \
    unittesthdlparserdialog.cpp

HEADERS += \
    hdlfile.h \
    hdlfiletreewidgetitem.h \
    hdlparserarchitecturedefinition.h \
    hdlparsercomments.h \
    hdlparserentitydefinition.h \
    hdlparsergenericdefinition.h \
    hdlparserlibrary.h \
    hdlparsermoduleinstantiation.h \
    hdlparserpackagebodydefinition.h \
    hdlparserpackageheaderdefinition.h \
    hdlparserportdefinition.h \
    hdlparserportdirection.h \
    hdlparsersignaldefinition.h \
    hdlparsertypedefinition.h \
    hdlparseruseclause.h \
    mainwindow.h \
    preferencesmanager.h \
    project.h \
    projectmanager.h \
    projectsummarywidget.h \
    semanticversion.h \
    texteditorwidget.h \
    unittesthdlparserdialog.h

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

RESOURCES += \
    assets.qrc
