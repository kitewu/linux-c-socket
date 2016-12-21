TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    PassiveServer.c \
    main_select.c \
    main_process.c \
    main_thread.c

LIBS += -lpthread

HEADERS += \
    PassiveServer.h

