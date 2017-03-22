#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T17:34:31
# Author: Justinas Bikulcius, 2095878b
# github.com/eustaceb
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = conversational-data-browser
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    data-models/transcription.cpp \
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
    slicer.cpp \
    tests/test_main.cpp \
    tests/teststatistics.cpp \
    tests/testdatamodels.cpp \
    tests/testhelpers.cpp

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
    slicer.h \
    tests/teststatistics.h \
    tests/testdatamodels.h \
    tests/testhelpers.h

FORMS    += mainwindow.ui \
    filemanager.ui \
    statistics.ui \
    slicer.ui

RESOURCES += \
    res.qrc

test {
    message(Test build)

    QT += testlib

    TARGET = CDBTests

    SOURCES -= main.cpp

} else {
    message(Normal build)
    # Remove all test files to avoid clashing and to speed up build
    HEADERS -= tests/teststatistics.h \
        tests/testdatamodels.h \
        tests/testhelpers.h

    SOURCES -= tests/test_main.cpp \
        tests/teststatistics.cpp \
        tests/testdatamodels.cpp \
        tests/testhelpers.cpp
}

#####################################################
#                  CONFIGURE THIS                   #
#####################################################
# LIBSNDFILE
# Set this to where the compiled library is located
LIBSNDFILE_LOC = $$PWD/libs/libsndfile

# Uncomment this if the build fails due to enums
QMAKE_CXXFLAGS += -std=gnu++11
# QMAKE_CXXFLAGS += -std=c++0x

win32: LIBS += -L$${LIBSNDFILE_LOC}/lib/ -llibsndfile-1
else:unix: LIBS += -L$${LIBSNDFILE_LOC}/lib/ -lsndfile

INCLUDEPATH += $${LIBSNDFILE_LOC}/include
DEPENDPATH += $${LIBSNDFILE_LOC}/

# Depending on version, lib filenames might differ - edit as needed
win32-g++: PRE_TARGETDEPS += $${LIBSNDFILE_LOC}/lib/libsndfile-1.lib
else:win32:!win32-g++: PRE_TARGETDEPS += $${LIBSNDFILE_LOC}/lib/libsndfile-1.lib
else:unix: PRE_TARGETDEPS += $${LIBSNDFILE_LOC}/lib/libsndfile.a
