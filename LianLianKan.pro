QT += qml quick

CONFIG += c++11
CONFIG += audio

RESOURCES += qml.qrc \
    Images.qrc \
    Sounds.qrc
win32{
    RC_ICONS = Images\icon.ico
}
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =


CONFIG += precompile_header
PRECOMPILED_HEADER = src/pch.h
DEFINES += USING_PCH

LIBS += -L.

INCLUDEPATH += src


DISTFILES += \
    Readme.txt

unix:!android {
    isEmpty(target.path) {
	qnx {
	    target.path = /tmp/$${TARGET}/bin
	} else {
	    target.path = /opt/$${TARGET}/bin
	}
	export(target.path)
    }
    INSTALLS += target
}


HEADERS += \
    $$PWD/src/game.h \
    $$PWD/src/music.h \
    $$PWD/src/tile.h \
    $$PWD/src/audio.h \
    $$PWD/src/pch.h

SOURCES += \
    $$PWD/src/game.cpp \
    $$PWD/src/main.cpp \
    $$PWD/src/music.cpp
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
    SOURCES +=	src/audio.cpp
    CONFIG(debug, debug|release): LIBS+= -lfmodexL
    else:LIBS += -lfmodex

}
