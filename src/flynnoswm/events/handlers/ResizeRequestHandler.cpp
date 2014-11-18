/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  ResizeRequestHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "ResizeRequestHandler.h"
#include "src/flynnoswm/xwindows/TaskBar.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ResizeRequestHandler::ResizeRequestHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //
//Window needs ResizeRedirectMask, only systray icons have it for now
bool ResizeRequestHandler::processEvent(XEvent* event)
{
    AtomList* al = AtomList::getInstance();
    Window windowID = event->xproperty.window;
    qDebug() << "[+] ResizeRequest notify event 0x" << hex << windowID << " Atom name: " << XGetAtomName(QX11Info::display(),event->xproperty.atom);
    if(this->wl->existClient(windowID)) {
        qDebug() << "\tLa ventana es un cliente, configurándolo...";
        XWindow* xwindow = this->wl->getXWindowByClientID(windowID);
        if (TaskBar::getInstance()->isSystrayWindow(xwindow))
        {
            //don't know why, but this fixes some icons, to set it before changing the size
            XResizeWindow(QX11Info::display(),windowID,event->xresizerequest.width,event->xresizerequest.height);

            //we set the size
            xwindow->setWidth(18);
            xwindow->setHeight(18);

            //send hints
            XSizeHints h;
            h.min_width = h.max_width = h.min_height = h.max_height = 18;
            h.flags = PMinSize | PMaxSize;
            XSetWMNormalHints(QX11Info::display(), xwindow->getClientID(), &h);
        }

    }
    return true;
}
