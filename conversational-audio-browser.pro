#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T17:34:31
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = conversational-audio-browser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    participantmanager.cpp \
    topic.cpp \
    speaker.cpp \
    section.cpp \
    turn.cpp \
    transcription.cpp \
    participant.cpp \
    helpers.cpp

HEADERS  += mainwindow.h \
    participantmanager.h \
    topic.h \
    speaker.h \
    section.h \
    turn.h \
    transcription.h \
    participant.h \
    helpers.h

FORMS    += mainwindow.ui \
    participantmanager.ui

DISTFILES += \
    ../rand.wav
