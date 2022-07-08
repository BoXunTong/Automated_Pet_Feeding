QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera_precess.cpp \
    detect_pet_thread.cpp \
    main.cpp \
    mainwindow.cpp \
    motor_control.cpp

HEADERS += \
    camera_precess.h \
    detect_pet_thread.h \
    mainwindow.h \
    motor_control.h

FORMS += \
    mainwindow.ui



#  raspberry
INCLUDEPATH += /usr/local/include/opencv4 \
               /usr/local/include/opencv4/opencv2 \
               #/usr/local/include/flatbuffers \
               /home/pi/tensorflow \
               /home/pi/tensorflow/tensorflow/lite/tools/make/downloads/flatbuffers/include
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

DISTFILES += \
    README
