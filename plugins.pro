TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    plugtypes.c \
    plugins/alpha.c \
    plugins/beta.c

HEADERS += \
    plugtypes.h \
    plugins/alpha.h \
    plugins/beta.h

