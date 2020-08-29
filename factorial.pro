TARGET = factorial
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x
LIBS += -lstdc++fs

message("PLATFORM  IDENTITY: " $$QMAKE_HOST.arch)

###### Qt directories
PLATFORM = 0
contains(QMAKE_HOST.arch, x86_64):{
    # for PC
    PLATFORM = 1
    message("PLATFORM: x86_64")
    COMMON_LIBS_DIR = /usr/lib/x86_64-linux-gnu
}
contains(QMAKE_HOST.arch, aarch64):{
    # for Tegras
    PLATFORM = 2
    message("PLATFORM: aarch")
    COMMON_LIBS_DIR = /usr/lib/aarch64-linux-gnu
}

# Build properties

DESTDIR = $$PWD/bin

#Отключить "теневую сборку" в криейторе!
CONFIG(release, debug|release) {

message(Project $$TARGET (Release))

OBJECTS_DIR = build/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/
}
CONFIG(debug, debug|release) {

message(Project $$TARGET (Debug))

OBJECTS_DIR = build/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/
DEFINES += DEBUG_BUILD
}

# GUI files
INCLUDEPATH += $$PWD/include
HEADERS += \
        include/itask.h \
        include/itask_control.h \
        include/logger.h \
        include/main_window.h

SOURCES += \
        src/itask.cpp \
        src/itask_control.cpp \
        src/logger.cpp \
        src/main.cpp \
        src/main_window.cpp

FORMS += \
        forms/main_window.ui

