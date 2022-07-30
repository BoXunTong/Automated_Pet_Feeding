#-------------------------------------------------
#
# Project created by QtCreator 2022-07-29T08:27:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hx711_demo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    hx711_thread.cpp \
    camera_precess.cpp \
    detect_pet_thread.cpp \
    motor_control.cpp \
    globalwrapper.cpp

HEADERS += \
        mainwindow.h \
    hx711_thread.h \
    camera_precess.h \
    detect_pet_thread.h \
    motor_control.h \
    globalwrapper.h

FORMS += \
        mainwindow.ui

LIBS += -llgpio \
        -lhx711

#  raspberry
INCLUDEPATH += /usr/local/include/opencv4 \
               /usr/local/include/opencv4/opencv2 \
               #/usr/local/include/flatbuffers \
               /home/pi/tensorflow \
               /home/pi/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers/include \


# 库文件
LIBS += /usr/local/lib/libopencv_calib3d.so.4.5 \
        /usr/local/lib/libopencv_core.so.4.5 \
        /usr/local/lib/libopencv_features2d.so.4.5 \
        /usr/local/lib/libopencv_highgui.so.4.5 \
        /usr/local/lib/libopencv_imgcodecs.so.4.5 \
        /usr/local/lib/libopencv_imgproc.so.4.5 \
        /usr/local/lib/libopencv_ml.so.4.5 \
        /usr/local/lib/libopencv_objdetect.so.4.5 \
        /usr/local/lib/libopencv_photo.so.4.5 \
        /usr/local/lib/libopencv_stitching.so.4.5 \
        /usr/local/lib/libopencv_video.so.4.5 \
        /usr/local/lib/libopencv_imgcodecs.so.4.5 \
        /usr/local/lib/libopencv_shape.so.4.5 \
        /usr/local/lib/libopencv_videoio.so.4.5 \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/lib/aarch64-linux-gnu/libdl.so \
        /usr/local/lib/libflatbuffers.a \
        -lwiringPi \
        /home/pi/tensorflow/tensorflow/lite/tools/make/gen/linux_aarch64/lib/libtensorflow-lite.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
