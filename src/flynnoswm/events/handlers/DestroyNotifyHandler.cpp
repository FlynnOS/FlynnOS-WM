/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  DestroyNotifyHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "DestroyNotifyHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

DestroyNotifyHandler::DestroyNotifyHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool DestroyNotifyHandler::processEvent(XEvent* event)
{
    Window windowID = event->xdestroywindow.window;
    qDebug() << "[+] DestroyNotify event 0x" << hex << windowID;

    // Si la ventana es un cliente
    if(this->wl->existClient(windowID))
    {
        qDebug() << "\tLa ventana es un cliente";
        XWindow* xwindow = this->wl->getXWindowByClientID(windowID);

        qDebug() << "\tEliminando la ventana de la lista";
        wl->removeClient(xwindow->getClientID());

        qDebug() << "\tEliminando la ventana de la lista del EWMH";
        this->wl->removeFromManagedWindow(xwindow);


        // Si la ventana no tiene marco la destruimos tal cual
        if(!xwindow->haveFrame())
        {
            qDebug() << "\tLa ventana no tiene marco";

            qDebug() << "\tLiberando memoria";
            delete xwindow;

        // Si la ventana si tiene marco lo destruimos
        }
        else
        {
            //Queremos borrar un cliente, vemos si es dock para actualizar el NET_WORKAREA de los docks
            if (xwindow->needFrame())
            {
                this->wl->updateWorkarea();
            }

            qDebug() << "\tLa ventana tiene marco, destruyéndolo";
            xwindow->removeFrame();

            // Liberamos memoria y quitamos el marco de la lista cuando se
            // destruya el marco
        }

        return true;

    // Si la ventana es un marco
    }
    else if(wl->existFrame(windowID))
    {
        qDebug() << "\tLa ventana es un marco";
        XWindow* xwindow = this->wl->getXWindowByFrameID(windowID);
        if(event->xdestroywindow.event == event->xdestroywindow.window || xwindow == 0)
        {
            qDebug() << "\tevent != window";
            return true;
        }

        qDebug() << "\tEliminando el marco de la lista";
        this->wl->removeFrame(xwindow->getFrameID());

        qDebug() << "\tLiberando memoria";
        delete xwindow;
        return true;

    // Si no es ni un marco ni un cliente
    }
    else
    {
        qDebug() << "\tLa ventana no es ni un cliente ni un marco";
        return false;
    }
}
