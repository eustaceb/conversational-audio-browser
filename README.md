# Conversational Data Browser
A research tool I have developed for my dissertation using C++ and the Qt5 framework.

# Compile Instructions
### Prerequisite: QT
1. Download Qt from https://www.qt.io/download/, open source version
2. During the installation uncheck everything except for the most recent version and MinGW (Windows) if it is not already present in your system. None of the options under the most recent version, e.g. "Qt Charts" are needed.
3. Make sure that qmake is on your path

### Prerequisite: libsndfile
The application is shipped with libsndfile source and binaries for linux and win32. It can be found in conversational-data-browser/libs but make sure to rename the appropriate folder to libsndfile if using the default project file. Alternatively, these steps can be taken:
1. Download libsndfile from http://www.mega-nerd.com/libsndfile/#Download and compile (Unix) or install (Windows) it to conversational-data-browser\libs\libsndfile. The 32bit version is necessary if using mingw32 (default).
2. Alternatively, if it's installed elsewhere edit the .pro file to link to the location.
3. Make sure that it is on your PATH by typing PATH (Windows) or $PATH (Unix) in the command prompt. If it is not, run
set PATH=%PATH%;X:\path\to\libsndfile\bin (Windows)
export PATH=$PATH:/path/to/libsndfile/bin (Unix)
to include it.

## Windows steps:
1. Once the installation is finished, either import the project into Qt Creator or run "Qt 5.8 for Desktop"which will run a command promp with all environment variables set up. Alternatively, include qmake in your PATH.
2. Run qmake -makefile in the project folder. This will generate the makefile.
3. Run mingw32-make to compile.
4. Cd to release/ and run conversational-data-browser.exe.

## Unix steps:
1. Once the installation is finished, either import the project into Qt Creator or open the terminal and navigate to the project.
2. Make sure that all required binaries are in the path, both Qt and libsndfile.
3. Create a separate folder for output
4. Run qmake /path/to/conversational-data-browser.pro -makefile in the output folder
5. Run make, ./conversational-data-browser once it builds


## Testing:
In order to run the test suite, add CONFIG+=test when running qmake, e.g. 
``` qmake -makefile CONFIG += test ```


# Troubleshooting:
1. libsndfile is not found: make sure that the conversational-data-browser.pro links to the correct file. The project file has comments for what needs to be set.
2. Missing Qt DLLs: either move them to the release dir or add ```X:\path_to_qt\5.8\mingw53_32\bin``` to path. 
3. Missing libsndfile-1.dll: ```set PATH=%PATH%;X:\path\to\libsndfile\bin``` or move it to the release dir
4. mainwindow.h:13:37: fatal error: QtMultimedia/QMediaPlayer: No such file or directory and similar errors during the make step: likely caused by path misconfiguration caused by some other application. Check where Qt binaries are getting included from. In my case that was ```-I../../../../anaconda2/include/qt/QtCore```, i.e. anacaconda. Removing 
5. Project ERROR: Unknown module(s) in QT: multimedia: fixed by ```sudo apt-get install qtmultimedia5-dev```
6. The QMediaPlayer object does not have a valid service: caused by wrong Qt binaries in the path. E.g. I had ```-isystem /usr/include/x86_64-linux-gnu/qt5/QtCore instead of ../../../Qt/5.7/gcc_64/include/QtGui```
An easy workaround is running ```sudo apt-get install qtmultimedia5-examples``` which will pull all necessary libraries to the default path.


# Tips:
- Most issues are mitigated using Qt Creator.

- Running mingw32-make clean will clean the project. 

- If compiling on windows MinGW must be used due to the library being compiled with this compiler. More info http://www.mega-nerd.com/libsndfile/win32.html

- Removing anaconda from path can be done using ```PATH=$(REMOVE_PART="/home/justas/anaconda2/bin" sh -c 'echo ":$PATH:" | sed "s@:$REMOVE_PART:@:@g;s@^:\(.*\):\$@\1@"')```

- If some unexpected error eccors, it is likely due to unresolved dependencies. http://doc.qt.io/qt-5/linux-requirements.html has all requirements for linux



# Compile output on my system:
```
15:08:22: Running steps for project conversational-data-browser...
15:08:22: Configuration unchanged, skipping qmake step.
15:08:22: Starting: "/usr/bin/make" 
g++ -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_NO_DEBUG -DQT_MULTIMEDIA_LIB -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -I../conversational-data-browser -I. -I../conversational-data-browser/libs/libsndfile/include -I../../../Qt/5.7/gcc_64/include -I../../../Qt/5.7/gcc_64/include/QtMultimedia -I../../../Qt/5.7/gcc_64/include/QtWidgets -I../../../Qt/5.7/gcc_64/include/QtGui -I../../../Qt/5.7/gcc_64/include/QtNetwork -I../../../Qt/5.7/gcc_64/include/QtCore -I. -I. -I../../../Qt/5.7/gcc_64/mkspecs/linux-g++ -o helpers.o ../conversational-data-browser/helpers.cpp
../conversational-data-browser/helpers.cpp: In static member function ‘static Transcription* Helpers::parseTranscript(QIODevice*)’:
../conversational-data-browser/helpers.cpp:49:47: warning: ‘currentSection’ may be used uninitialized in this function [-Wmaybe-uninitialized]
                     currentSection->addTurn(t);
                                               ^
g++ -Wl,-O1 -Wl,-rpath,/home/justas/Qt/5.7/gcc_64/lib -o conversational-data-browser main.o mainwindow.o transcription.o helpers.o section.o speaker.o topic.o turn.o sectiongraphicsitem.o timelinewidget.o speakergraphicsitem.o ruler.o turngraphicsitem.o selectiontreemodel.o selectiontreeitem.o selectable.o filterable.o filtertreeitem.o filtertreemodel.o filemanager.o recording.o multitimelinewidget.o transcriptiongraphicsitem.o statistics.o mspeakergraphicsitem.o mspeakercountgraphicsitem.o slicer.o qrc_res.o moc_mainwindow.o moc_timelinewidget.o moc_selectiontreemodel.o moc_filtertreemodel.o moc_filemanager.o moc_multitimelinewidget.o moc_statistics.o moc_slicer.o   -L/home/justas/Dissertation/project/conversational-data-browser/libs/libsndfile/lib/ -lsndfile -L/home/justas/Qt/5.7/gcc_64/lib -lQt5Multimedia -L/usr/lib64 -lQt5Widgets -lQt5Gui -lQt5Network -lQt5Core -lGL -lpthread 
15:08:26: The process "/usr/bin/make" exited normally.
15:08:26: Elapsed time: 00:04.
```
