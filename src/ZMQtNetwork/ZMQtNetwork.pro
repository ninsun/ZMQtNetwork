QT       -= gui
TARGET = ZMQtNetwork
TEMPLATE = lib

DEFINES += ZMQTNETWORK_LIBRARY

INCLUDEPATH += ../../inc

SOURCES += \
    ZMQtSocket.cpp \
    ZMQtMessage.cpp \
    ZMQtContext.cpp

HEADERS += \
    ../../inc/ZMQtType.h \
    ../../inc/ZMQtSocket.h \
    ../../inc/zmqtnetwork_global.h \
    ../../inc/ZMQtMessage.h \
    ../../inc/ZMQtContext.h

unix|win32: LIBS += -lzmq
