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
    transcription.cpp \
    helpers.cpp \
    data-models/section.cpp \
    data-models/speaker.cpp \
    data-models/topic.cpp \
    data-models/turn.cpp \
    drawables/regular/sectiongraphicsitem.cpp \
    drawables/regular/timelinewidget.cpp \
    drawables/regular/speakergraphicsitem.cpp \
    drawables/ruler.cpp \
    drawables/regular/turngraphicsitem.cpp \
    trees/selectiontreemodel.cpp \
    trees/selectiontreeitem.cpp \
    data-models/selectable.cpp \
    data-models/filterable.cpp \
    trees/filtertreeitem.cpp \
    trees/filtertreemodel.cpp \
    filemanager.cpp \
    data-models/recording.cpp \
    drawables/multifile/multitimelinewidget.cpp \
    drawables/multifile/transcriptiongraphicsitem.cpp \
    statistics.cpp \
    drawables/multifile/mspeakergraphicsitem.cpp \
    drawables/multifile/mspeakercountgraphicsitem.cpp \
    slicer.cpp

HEADERS  += mainwindow.h \
    helpers.h \
    data-models/section.h \
    data-models/speaker.h \
    data-models/topic.h \
    data-models/turn.h \
    drawables/regular/sectiongraphicsitem.h \
    drawables/regular/timelinewidget.h \
    drawables/regular/speakergraphicsitem.h \
    drawables/ruler.h \
    drawables/regular/turngraphicsitem.h \
    trees/selectiontreeitem.h \
    trees/selectiontreemodel.h \
    data-models/selectable.h \
    data-models/filterable.h \
    trees/filtertreeitem.h \
    trees/filtertreemodel.h \
    filemanager.h \
    data-models/transcription.h \
    data-models/recording.h \
    drawables/multifile/multitimelinewidget.h \
    drawables/multifile/transcriptiongraphicsitem.h \
    statistics.h \
    drawables/multifile/mspeakergraphicsitem.h \
    drawables/multifile/mspeakercountgraphicsitem.h \
    slicer.h

FORMS    += mainwindow.ui \
    filemanager.ui \
    statistics.ui \
    slicer.ui

DISTFILES += \
    ../rand.wav

RESOURCES += \
    res.qrc
