/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class ClientMessageHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "ClientMessageHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ClientMessageHandler::ClientMessageHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool ClientMessageHandler::processEvent(XEvent* event)
{
    Window windowID = event->xclient.window;
    qDebug() << "[+] ClientMessage event 0x" << hex << windowID;
    AtomList* al = AtomList::getInstance();

    qDebug() << "\tPropiedad a cambiar: " << XGetAtomName(
            QX11Info::display(), event->xclient.message_type);

    // Si la ventana es un cliente
    if(this->wl->existClient(windowID))
    {
        qDebug() << "\tLa ventana es un cliente";
        XWindow* xwindow = this->wl->getXWindowByClientID(windowID);
        //----------------------------------------------------------------------

        // ICCCM

        if(event->xclient.message_type == al->getAtom("WM_CHANGE_STATE")
                        && event->xclient.format == 32
                        && event->xclient.data.l[0] == IconicState)
        {
                    qDebug() << "\tSe solicita minimizar el cliente";
                    xwindow->setState(IconicState);
                    return true;

        //----------------------------------------------------------------------

        // EWMH

        }
        else if(event->xclient.message_type == al->getAtom("_NET_ACTIVE_WINDOW"))
        {
            EWMHRoot ewmh;
            ewmh.receivedActiveWindow(this->wl, xwindow);

        }
        else if(event->xclient.message_type == al->getAtom("_NET_CLOSE_WINDOW"))
        {
            EWMHRoot ewmh;
            ewmh.receivedCloseWindow(xwindow);
        }

        return false;

    // Si la ventana es un marco
    }
    else if(wl->existFrame(windowID))
    {
        qDebug() << "\tLa ventana es un marco";

        // XdndLeave
        // XdndEnter
        // XdndPosition

        return false;

    // Si no es ni un marco ni un cliente
    }
    else
    {
        qDebug() << "\tLa ventana no es ni un cliente ni un marco";

        // _NET_SHOWING_DESKTOP

        return false;
    }
}
