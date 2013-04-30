#-------------------------------------------------
#
# Project created by QtCreator 2013-04-14T07:53:34
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = ZMQtNetwork
TEMPLATE = lib

DEFINES += ZMQTNETWORK_LIBRARY

SOURCES += ZMQtNetwork.cpp \
    ZMQtSocket.cpp \
    ZMQtMessage.cpp \
    ZMQtContext.cpp

HEADERS += ZMQtNetwork.h\
        zmqtnetwork_global.h \
    ZMQtSocket.h \
    ZMQtMessage.h \
    ZMQtContext.h \
    ZMQtType.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
