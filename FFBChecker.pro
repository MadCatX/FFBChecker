#-------------------------------------------------
#
# Project created by QtCreator 2013-03-28T12:34:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FFBChecker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    deviceprober.cpp \
    ffbdevice.cpp \
    ffbeffect.cpp \
    ffbeffectparameters.cpp \
    ffbconstanteffectparameters.cpp \
    effectsettings.cpp \
    constanteffectsettings.cpp \
    envelopesettings.cpp \
    periodiceffectsettings.cpp \
    ffbconstanteffect.cpp \
    ffbeffectfactory.cpp \
    ffbenvelopeparameters.cpp \
    ffbperiodiceffectparameters.cpp \
    ffbperiodiceffect.cpp \
    ffbnulleffect.cpp \
    conditioneffectsettings.cpp \
    ffbconditioneffectparameters.cpp \
    ffbconditioneffect.cpp

HEADERS  += mainwindow.h \
    deviceprober.h \
    ffbdevice.h \
    helpers.h \
    ffbeffect.h \
    globals.h \
    ffbeffectparameters.h \
    ffbconstanteffectparameters.h \
    effectsettings.h \
    constanteffectsettings.h \
    envelopesettings.h \
    periodiceffectsettings.h \
    ffbconstanteffect.h \
    ffbeffectfactory.h \
    ffbenvelopeparameters.h \
    ffbperiodiceffectparameters.h \
    ffbperiodiceffect.h \
    ffbnulleffect.h \
    conditioneffectsettings.h \
    ffbconditioneffectparameters.h \
    ffbconditioneffect.h

FORMS    += mainwindow.ui \
    constanteffectsettings.ui \
    envelopesettings.ui \
    periodiceffectsettings.ui \
    conditioneffectsettings.ui

QMAKE_CXXFLAGS += -std=c++11 -Wall

OTHER_FILES += \
    TODO.txt
