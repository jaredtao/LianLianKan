QT += qml quick

CONFIG += c++11
#CONFIG += audio

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
    Readme.txt \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

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
    android{
	DEFINES += ANDROID
	ANDROID_LIBPATH = $$_PRO_FILE_PWD_/lib/android/$$ANDROID_ARCHITECTURE/lib
	LIBS += -L"$$ANDROID_LIBPATH"
    } else {
	DEFINES += LINUX
	!contains(QMAKE_HOST.arch, x86_64) {
	    LIBS += -L"$$_PRO_FILE_PWD_/lib/linux/x86"
	    QMAKE_LFLAGS += -Wl,--rpath=lib/linux/x86
	}
	else {
	    LIBS += -L"$$_PRO_FILE_PWD_/lib/linux/x64"
	    QMAKE_LFLAGS += -Wl,--rpath=lib/linux/x64
	}
    }
}
CONFIG(audio) {

    INCLUDEPATH += include/fmod

    android {
#	CONFIG(debug, debug|release):ANDROID_EXTRA_LIBS += $$ANDROID_LIBPATH/libfmodexL.so
#	else:ANDROID_EXTRA_LIBS += $$ANDROID_LIBPATH/libfmodex.so
    } else {
	DEFINES += AUDIO_SUPPORT
	CONFIG(debug, debug|release): LIBS+= -lfmodexL
	else:LIBS += -lfmodex

	SOURCES +=	src/audio.cpp
    }
}

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
