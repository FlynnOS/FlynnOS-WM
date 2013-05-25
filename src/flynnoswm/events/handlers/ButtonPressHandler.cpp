/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class ButtonPressHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "ButtonPressHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ButtonPressHandler::ButtonPressHandler(XWindowList* wl)
        : EventHandler(wl)
{
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool ButtonPressHandler::processEvent(XEvent* event)
{
    Window windowID = event->xbutton.window;
    qDebug() << "[+] ButtonPress event 0x" << hex << windowID;

    // Si la ventana es un marco
    if(this->wl->existFrame(windowID))
    {
        qDebug() << "\tLa ventana es un marco";
        XWindow* xwindow = wl->getXWindowByFrameID(windowID);

        qDebug() << "\tModificando la lista del EWMH";
        this->wl->restackManagedWindow(xwindow);

        qDebug() << "\tActualizando la ventana activa";
        this->wl->setActiveWindow(xwindow);

        return false;
    }
    else if (this->wl->existClient(windowID))
    {
        //XUngrabButton(QX11Info::display(), AnyButton, AnyModifier, windowID);
        return false;
    }
    else // Si la ventana no es un marco
    {
        // 1 left, 2 middle, 3 right
        //if left button click we lauch a terminator
        /*if (event->xbutton.button == 3)
        {
            std::system("terminator &");
        }*/
        qDebug() << "\tLa ventana no es un marco";
        return false;
    }
}
