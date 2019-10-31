#-------------------------------------------------
#
# Project created by QtCreator 2019-02-26T18:52:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Filters
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    awidget.cpp \
    bwidget.cpp \
    cwidget.cpp \
    filedriver.cpp \
    imageresizer.cpp \
    rotationdialog.cpp \
    imatrixfilter.cpp \
    blurfilter.cpp \
    effect.cpp \
    bweffect.cpp \
    negativeeffect.cpp \
    orderdithereffect.cpp \
    errordiffeffect.cpp \
    aboutdialog.cpp \
    robertseffect.cpp \
    sobel.cpp \
    duplicateaction.cpp \
    rotateaction.cpp \
    gammaeffect.cpp \
    sharpfilter.cpp \
    stampfilter.cpp \
    watercolorfilter.cpp \
    expansionfilter.cpp

HEADERS += \
        mainwindow.h \
    bwidget.h \
    cwidget.h \
    awidget.h \
    filedriver.h \
    imageresizer.h \
    rotationdialog.h \
    imatrixfilter.h \
    blurfilter.h \
    effect.h \
    bweffect.h \
    negativeeffect.h \
    orderdithereffect.h \
    errordiffeffect.h \
    aboutdialog.h \
    robertseffect.h \
    sobel.h \
    duplicateaction.h \
    rotateaction.h \
    gammaeffect.h \
    sharpfilter.h \
    stampfilter.h \
    watercolorfilter.h \
    expansionfilter.h

FORMS += \
        mainwindow.ui \
    rotationdialog.ui \
    aboutdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/rrr.qrc
