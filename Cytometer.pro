QT       += core gui
QT	 += core bluetooth widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Cytometer

TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11

SOURCES += \
        chatclient.cpp \
        chatserver.cpp \
        loadingactiv.cpp \
        main.cpp \
        mainwindow.cpp \
        qcustomplot.cpp \
        remoteselector.cpp \
        saveactiv.cpp \
        settingactiv.cpp \
        settingconst.cpp \
        startactiv.cpp

HEADERS += \
        chatclient.h \
        chatserver.h \
        loadingactiv.h \
        mainwindow.h \
        qcustomplot.h \
        remoteselector.h \
        saveactiv.h \
        settingactiv.h \
        settingconst.h \
        startactiv.h

FORMS += \
        loadingactiv.ui \
        mainwindow.ui \
        remoteselector.ui \
        saveactiv.ui \
        settingactiv.ui \
        startactiv.ui

CONFIG += mobility
MOBILITY = 

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Cytometer_Mobile.pro.user \
    SS.zip \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}


android {
    SAMPLES_INSTALL_PATH=/assets/Datas/
    SAMPLE_FILES_DATA=asset/DataR.bin
} else {
    SAMPLES_INSTALL_PATH=$$OUT_PWD/Datas
    SAMPLE_FILES_DATA=asset/DataR.bin
}
samples.path = $$SAMPLES_INSTALL_PATH
samples.files += $$SAMPLE_FILES_DATA
samples.depends += FORCE

INSTALLS += samples
