QT += qml quick

CONFIG += c++11
CONFIG += audio
SOURCES += main.cpp \
    game.cpp \
    music.cpp

RESOURCES += qml.qrc \
    Images.qrc \
    Sounds.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

LIBS += -L.
# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    Readme.txt

HEADERS += \
    audio.h \
    game.h \
    music.h \
    tile.h
win32-g++{
    DEFINES += WIN32
    LIBS += -L"$$_PRO_FILE_PWD_/lib/win/MinGW"
}
linux {
    DEFINES += LINUX
    LIBS += -L"$$_PRO_FILE_PWD_/lib/linux/x64"
}
CONFIG(audio) {
    DEFINES += AUDIO_SUPPORT
    INCLUDEPATH += include/fmod
    CONFIG(debug, debug|release): LIBS+= -lfmodexL
    else:LIBS += -lfmodex
    SOURCES += audio.cpp
}
