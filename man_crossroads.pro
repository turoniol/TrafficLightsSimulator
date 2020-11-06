#-------------------------------------------------
#
# Project created by QtCreator 2019-09-20T16:50:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = man_crossroads
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

CONFIG += c++14

SOURCES += \
        main.cpp \
	windows/mainwindow.cpp \
    map/map.cpp \
    traffic_light/trafficlight.cpp \
    cars/carcenter.cpp \
    cars/car.cpp \
    map/block.cpp \
    scene/scene.cpp \
    neural_net/neuron.cpp \
    neural_net/layer.cpp \
    neural_net/net.cpp \
    traffic_light/tlcontrol.cpp \
    traffic_light/trafficlightgroup.cpp \
    scene/graphicsviewzoom.cpp

HEADERS += \
        windows/mainwindow.h \
    map/map.h \
    traffic_light/trafficlight.h \
    cars/carcenter.h \
    cars/car.h \
    map/block.h \
    scene/scene.h \
    neural_net/neuron.h \
    neural_net/layer.h \
    neural_net/net.h \
    traffic_light/tlcontrol.h \
    traffic_light/trafficlightgroup.h \
    scene/graphicsviewzoom.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
