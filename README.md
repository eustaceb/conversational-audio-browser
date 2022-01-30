# Conversational Data Browser
A research tool I have developed for my dissertation using C++ and the Qt5 framework.

A short (1 minute) presentation of the project can be seen at https://youtu.be/gLyyy59sgy0

![CDB Screenshot](http://i.imgur.com/PpX4Gfn.png)

## Abstract
Conversations in the form of audio recordings carry both verbal and non-verbal cues. Most software tools are
only concerned with the former because verbal communication carries more information and is easier to work
with. However, there is a growing need to analyse conversational data that contains multiple layers of both
verbal and non-verbal communication signals. Through the course of this project, a desktop application for
presenting, traversing and analysing such data was developed. The application aims to improve the efficiency of
conversational data investigations in research.


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
