/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "src/flynnoswm/FlynnOSwm.h"
#include "src/DeathHandler/death_handler.h"

//Log all qt output to a file,
void logToFile(QtMsgType type, const char *msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;

    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
    break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
    break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
        abort();
    }


    QFile outFile(QDir::homePath() + "/.flynnoswm/flynnwm.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}


/**
 * @~spanish
 * Función de inicio de FlynnOSwm.
 * @param argc Número de argumentos recibidos por consola.
 * @param argv Lista de argumentos.
 *
 * @~english
 * Start function for FlynnOSwm.
 * @param argc Number of arguments received by console.
 * @param argv Argument list.
 */
int main(int argc, char *argv[])
{

    Debug::DeathHandler dh;

    //we delete the previous log file
    if (QFile::exists(QDir::homePath() + "/.flynnoswm/flynnwm.log"))
    {
        QFile::remove(QDir::homePath() + "/.flynnoswm/flynnwm.log");
    }

    //qInstallMsgHandler(logToFile); //install : set the callback
    FlynnOSwm flynnOSwm(argc, &argv);
    return flynnOSwm.exec();
}

/*
 * Para debuggear:
 *
 * $ Xephyr :1 -ac -screen 900x700 &
 * En "Proyectos -> Entorno de construcción -> DISPLAY" poner ":1" o lanzar con
 * la opción "-display :1".
 *
 * Para ver el árbol de ventanas:
 * $ xwininfo -display :1 -tree -root
 *
 * Ver propiedades de una ventana:
 * $ xwininfo -display :1
 *
 * Se le puede añadir una composición muy simple con xcompmg:
 * $ xcompmgr -cf -d :1
 *
 * Para debugear el estándar EWMH/NetWM:
 * La herramienta wmctrl nos proporciona diversa información:
 * $ man wmctrl
 * Para ver las propiedades que va estableciendo el WM sobre la root window:
 * $ xprop -root -display :1
 *
 * NOTA -> Mirar QStyle para ver como crear un estilo para los widgets
 */
