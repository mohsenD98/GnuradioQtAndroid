QT += quick core-private

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ViewModels/GFlow.cpp \
        ViewModels/AndroidPermissions.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/src/org/qtproject/example/HandlePermissions.java \
    android/src/org/qtproject/example/JniMessenger.java

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

TOOLCHAIN = /home/mohsen/Android/toolchain_after_build/toolchain/

INCLUDEPATH += $$TOOLCHAIN/armeabi-v7a/include
INCLUDEPATH += $$TOOLCHAIN/armeabi-v7a/include/boost-1_69

LIBS += $$TOOLCHAIN/armeabi-v7a/lib/libgnuradio-runtime.so
LIBS += $$TOOLCHAIN/armeabi-v7a/lib/libgnuradio-pmt.so
LIBS += $$TOOLCHAIN/armeabi-v7a/lib/libgnuradio-blocks.so
LIBS += $$TOOLCHAIN/armeabi-v7a/lib/libhackrf.so
LIBS += $$TOOLCHAIN/armeabi-v7a/lib/libusb1.0.so
LIBS += $$TOOLCHAIN/armeabi-v7a/lib/libgnuradio-osmosdr.so
LIBS += $$TOOLCHAIN/armeabi-v7a/lib/libgnuradio-grand.so
LIBS += $$TOOLCHAIN/armeabi-v7a/lib/libgnuradio-analog.so
LIBS += $$TOOLCHAIN/armeabi-v7a/lib/libgnuradio-filter.so
LIBS += $$TOOLCHAIN/armeabi-v7a/lib/libgnuradio-fft.so

HEADERS += \
    ViewModels/AndroidLogger.h \
    ViewModels/GFlow.h \
    ViewModels/AndroidPermissions.h
