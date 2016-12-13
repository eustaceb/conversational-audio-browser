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
    transcription.cpp \
    helpers.cpp \
    data-models/participant.cpp \
    data-models/section.cpp \
    data-models/speaker.cpp \
    data-models/topic.cpp \
    data-models/turn.cpp \
    drawables/regular/audiotrack.cpp \
    drawables/regular/sectiongraphicsitem.cpp \
    drawables/regular/timelinewidget.cpp \
    drawables/regular/speakergraphicsitem.cpp \
    drawables/ruler.cpp

HEADERS  += mainwindow.h \
    participantmanager.h \
    transcription.h \
    helpers.h \
    data-models/participant.h \
    data-models/section.h \
    data-models/speaker.h \
    data-models/topic.h \
    data-models/turn.h \
    drawables/regular/audiotrack.h \
    drawables/regular/sectiongraphicsitem.h \
    drawables/regular/timelinewidget.h \
    drawables/regular/speakergraphicsitem.h \
    drawables/ruler.h

FORMS    += mainwindow.ui \
    participantmanager.ui

DISTFILES += \
    ../rand.wav

RESOURCES += \
    res.qrc
