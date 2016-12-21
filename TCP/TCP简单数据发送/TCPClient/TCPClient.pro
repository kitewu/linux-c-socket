TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.c \
    Socket.c

HEADERS += \
    Socket.h

LIBS += -lpthread

