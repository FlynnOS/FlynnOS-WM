/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class UnmapNotifyHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "UnmapNotifyHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

UnmapNotifyHandler::UnmapNotifyHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool UnmapNotifyHandler::processEvent(XEvent* event) {
    Window windowID = event->xunmap.window;
    qDebug() << "[+] UnmapNotify event 0x" << hex << windowID;

    // Si la ventana es un cliente
    if(this->wl->existClient(windowID)) {
        qDebug() << "\tLa ventana es un cliente";
        XWindow* xwindow = wl->getXWindowByClientID(windowID);

        // Si el cliente se desmapea porque se minimiza
        if(xwindow->getState() == IconicState) {
            qDebug() << "\tEl cliente se minimiza";

        // Si el cliente se desmapea porque pasa de NormalState a WithdrawnState
        } else {
            qDebug() << "\tEl cliente pasa de NormalState a WithdrawnState";
            xwindow->setState(WithdrawnState);

            qDebug() << "\tEliminando la ventana de la lista del EWMH";
            this->wl->removeFromManagedWindow(xwindow);
        }

        // Ponemos como ventana activa la de la parte superior de la pila
        qDebug() << "\tActualizando la ventana activa";
        this->wl->setActiveWindow(this->wl->getTopWindow());

        return false;

    // Si la ventana no es un cliente
    } else {
        qDebug() << "\tLa ventana no es un cliente";
        return false;
    }
}
