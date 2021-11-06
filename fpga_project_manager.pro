QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    hdlparserarchitecturedefinition.cpp \
    hdlparserentitydefinition.cpp \
    hdlparsergenericdefinition.cpp \
    hdlparserportdefinition.cpp \
    hdlparsersignaldefinition.cpp \
    main.cpp \
    mainwindow.cpp \
    unittestdependencyparserdialog.cpp \
    vhdldependencyparser.cpp

HEADERS += \
    hdlparserarchitecturedefinition.h \
    hdlparserentitydefinition.h \
    hdlparsergenericdefinition.h \
    hdlparserportdefinition.h \
    hdlparsersignaldefinition.h \
    mainwindow.h \
    unittestdependencyparserdialog.h \
    vhdldependencyparser.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui \
    unittestdependencyparserdialog.ui

test_data.path = $${OUT_PWD}/test
test_data.files += test/*
INSTALLS += test_data
