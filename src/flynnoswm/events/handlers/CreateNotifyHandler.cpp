/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  CreateNotifyHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "CreateNotifyHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

CreateNotifyHandler::CreateNotifyHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool CreateNotifyHandler::processEvent(XEvent* event) {
    Window windowID = event->xcreatewindow.window;
    qDebug() << "[+] CreateNotify event 0x" << hex << windowID;

    // Si la ventana no es un marco
    if(!this->wl->existFrame(windowID)) {
        qDebug() << "\tLa ventana es un cliente";
        XWindow* xwindow = new XWindow(windowID);

        qDebug() << "\tAñadiendo el cliente a la lista";
        this->wl->addClient(windowID, xwindow);

        xwindow = this->wl->getXWindowByClientID(windowID);

        return false;

    // Si la ventana es un marco
    } else {
        // Podemos saber que la ventana es un marco en el momento de crearla
        // porque el marco se añade en MapRequestHandler, guardando su ID en la
        // lista
        qDebug() << "\tLa ventana es un marco";
        return false;
    }
}
