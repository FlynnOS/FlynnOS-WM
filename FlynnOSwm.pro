TEMPLATE     = app
TARGET       = bin/flynnoswm
QT          += core gui
OBJECTS_DIR += build
MOC_DIR     += build
LIBS        += -lX11 -lXtst -ldl
//DEFINES      = QT_NO_DEBUG_OUTPUT
QMAKE_CXXFLAGS_RELEASE += -g
QMAKE_CFLAGS_RELEASE += -g

target.path  = /usr/bin
target.files = bin/flynnoswm
targetuser.path  = /usr/local/bin
targetuser.files = bin/flynnoswm
config.path  = /usr/share/flynnoswm
config.files = installation/*
INSTALLS += target targetuser config

include(src/flynnoswm/flynnoswm.pri)
