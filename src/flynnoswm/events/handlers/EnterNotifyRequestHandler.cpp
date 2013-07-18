/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class EnterNotifyRequestHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "EnterNotifyRequestHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

EnterNotifyRequestHandler::EnterNotifyRequestHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool EnterNotifyRequestHandler::processEvent(XEvent* event) {
    Window windowID = event->xcrossing.window;
    qDebug() << "[+] EnterNotify vent 0x" << hex << windowID;

    // Si la ventana es un cliente
    if(this->wl->existClient(windowID))
    {
        qDebug() << "\t EnterNotify: Entramos a la ventana";
        XWindow* xwindow = this->wl->getXWindowByClientID(windowID);

        // Si el cliente bypassea el WM
        if(xwindow->bypassWM())
        {
            qDebug() << "\tEl cliente bypassea el WM";
            return false;

        // Si no lo bypassea
        }
        else
        {
            //XDefineCursor(QX11Info::display(), windowID, QCursor(Qt::ClosedHandCursor).handle());

            return true;
        }

    // Si no es un cliente
    } else {
        qDebug() << "\tLa ventana no es un cliente";
        return false;
    }
}
