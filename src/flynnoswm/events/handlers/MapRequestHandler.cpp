/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  MapRequestHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "MapRequestHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MapRequestHandler::MapRequestHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool MapRequestHandler::processEvent(XEvent* event) {
    Window windowID = event->xmaprequest.window;
    qDebug() << "[+] MapRequest event 0x" << hex << windowID;

    // Si la ventana es un cliente
    if(this->wl->existClient(windowID)) {
        qDebug() << "\tLa ventana es un cliente";
        XWindow* xwindow = this->wl->getXWindowByClientID(windowID);

        // Si el cliente bypassea el WM
        if(xwindow->bypassWM()) {
            qDebug() << "\tEl cliente bypassea el WM";
            return false;

        // Si no lo bypassea
        } else {

            // Si la ventana se mapea por primera vez
            if(xwindow->getState() == WithdrawnState) {
                qDebug() << "\tEl cliente se mapea por primera vez";

                if(xwindow->needFrame()) {
                    qDebug() << "\tAñadiendo un marco al cliente";
                    xwindow->addFrame();

                    // No hace falta añadir el cliente a la lista por que ya se
                    // añadió en CreateNotifyHandler

                    qDebug() << "\tAñadiendo el marco (0x" << hex
                             << xwindow->getFrameID() << ") a la lista";
                    wl->addFrame(xwindow->getFrameID(), xwindow);
                } else
                    qDebug() << "\tEl cliente no necesita marco";

                qDebug() << "\tMapeando la ventana";
                xwindow->setState(NormalState);

                qDebug() << "\tAñadiendo la ventana de la lista del EWMH";
                this->wl->addToManagedWindows(xwindow);

                qDebug() << "\tActualizando la ventana activa";
                this->wl->setActiveWindow(this->wl->getTopWindow());
            }

            return true;
        }

    // Si la ventana es un marco
    } else if(this->wl->existFrame(windowID)) {
        qDebug() << "\tLa ventana es un marco";
        return false;

    // Si no se ni un marco ni un cliente
    } else {
        qDebug() << "\tLa ventana no es ni un cliente ni un marco";
        return false;
    }

}
