QT       += core
QT       -= gui

TARGET = OpenCV-Ex1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

win32 {
    INCLUDEPATH += C:/opencv-build-2.4.11/install/include

    LIBS += -LC:/opencv-build-2.4.11/install/x64/mingw/lib \
        -llibopencv_core2411 \
        -llibopencv_highgui2411 \
        -llibopencv_imgproc2411 \
        -llibopencv_features2d2411 \
        -llibopencv_calib3d2411 \
        -llibopencv_ml2411 \
        -llibopencv_features2d2411
}


unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv

}

HEADERS +=

FORMS +=
