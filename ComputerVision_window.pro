INCLUDEPATH += D:\opencv\opencv-3.2.0\opencv-3.2.0-debug\install\include

CONFIG += c++11
TARGET = ComputerVision_window

QT += widgets
QT += core gui serialport
QT += multimedia multimediawidgets

LIBS += D:\opencv\opencv-3.2.0\opencv-3.2.0-debug\bin\libopencv_core320.dll
LIBS += D:\opencv\opencv-3.2.0\opencv-3.2.0-debug\bin\libopencv_highgui320.dll
LIBS += D:\opencv\opencv-3.2.0\opencv-3.2.0-debug\bin\libopencv_imgcodecs320.dll
LIBS += D:\opencv\opencv-3.2.0\opencv-3.2.0-debug\bin\libopencv_imgproc320.dll

LIBS += D:\opencv\opencv-3.2.0\opencv-3.2.0-debug\bin\libopencv_features2d320.dll
LIBS += D:\opencv\opencv-3.2.0\opencv-3.2.0-debug\bin\libopencv_calib3d320.dll

LIBS += D:\opencv\opencv-3.2.0\opencv-3.2.0-debug\bin\libopencv_videoio320.dll
LIBS += D:\opencv\opencv-3.2.0\opencv-3.2.0-debug\bin\libopencv_videostab320.dll

SOURCES += \
    processcamera.cpp \
    maincamera.cpp \
    main.cpp \
    arduino.cpp \
    objectdetection.cpp \
    colortracking.cpp \
    cameralabel.cpp

HEADERS += \
    processcamera.h \
    maincamera.h \
    arduino.h \
    objectdetection.h \
    colortracking.h \
    cameralabel.h

RESOURCES += \
    File.qrc
