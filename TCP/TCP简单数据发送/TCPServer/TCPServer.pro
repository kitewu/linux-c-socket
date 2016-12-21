TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    main.c \
    CreateServer.c \
    main_select.c

LIBS += -lpthread

HEADERS += \
    CreateServer.h

