TEMPLATE     = app
TARGET       = flynnoswm
QT          += core gui
OBJECTS_DIR += build
MOC_DIR     += build
LIBS        += -lX11
//DEFINES      = QT_NO_DEBUG_OUTPUT


target.path  = /usr/bin
targetuser.path  = /usr/local/bin
targetuser.files = flynnoswm
config.path  = /usr/share/flynnoswm
config.files = installation/*
INSTALLS += target targetuser config


include(src/flynnoswm/flynnoswm.pri)
