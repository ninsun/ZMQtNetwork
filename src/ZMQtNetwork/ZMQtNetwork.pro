QT       -= gui
TARGET = ZMQtNetwork
TEMPLATE = lib

DEFINES += ZMQTNETWORK_LIBRARY

INCLUDEPATH += ../../inc

SOURCES += \
    ZMQtSocket.cpp \
    ZMQtMessage.cpp \
    ZMQtContext.cpp

unix|win32: LIBS += -lzmq

HEADERS += \
    ../../inc/ZMQtNetwork/ZMQtType.h \
    ../../inc/ZMQtNetwork/ZMQtSocket.h \
    ../../inc/ZMQtNetwork/zmqtnetwork_global.h \
    ../../inc/ZMQtNetwork/ZMQtMessage.h \
    ../../inc/ZMQtNetwork/ZMQtContext.h
