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
    ffbconditioneffect.cpp \
    rampeffectsettings.cpp \
    ffbrampeffectparameters.cpp \
    ffbrampeffect.cpp \
    globalsettings.cpp \
    rumbleeffectsettings.cpp \
    ffbrumbleeffectparameters.cpp \
    ffbrumbleeffect.cpp

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
    ffbconditioneffect.h \
    rampeffectsettings.h \
    ffbrampeffectparameters.h \
    ffbrampeffect.h \
    globalsettings.h \
    rumbleeffectsettings.h \
    ffbrumbleeffectparameters.h \
    ffbrumbleeffect.h

FORMS    += mainwindow.ui \
    constanteffectsettings.ui \
    envelopesettings.ui \
    periodiceffectsettings.ui \
    conditioneffectsettings.ui \
    rampeffectsettings.ui \
    rumbleeffectsettings.ui

QMAKE_CXXFLAGS += -std=c++11 -Wall
QMAKE_CXXFLAGS_DEBUG += -ggdb3

OTHER_FILES += \
    TODO.txt
