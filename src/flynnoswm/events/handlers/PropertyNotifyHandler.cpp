/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class PropertyNotifyHandler
 * @authors Vicente Benavent
 *
 */
#include "PropertyNotifyHandler.h"
#include "src/flynnoswm/xwindows/TaskBar.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

PropertyNotifyHandler::PropertyNotifyHandler(XWindowList* wl)
        : EventHandler(wl)
{
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool PropertyNotifyHandler::processEvent(XEvent* event)
{
    AtomList* al = AtomList::getInstance();
    Window windowID = event->xproperty.window;
    //qDebug() << "[+] Property notify event 0x" << hex << windowID << " Atom name: " << XGetAtomName(QX11Info::display(),event->xproperty.atom);
    // Si la ventana es un cliente
    if(this->wl->existClient(windowID))
    {
        if (event->xproperty.atom == XA_WM_NAME)
        {
            XWindow* xwindow = this->wl->getXWindowByClientID(windowID);
            xwindow->updateTitle();
        }
        else if(event->xclient.message_type == al->getAtom("_NET_WM_USER_TIME")) //Como esta definido en el estandard, cuando se hace request con este mensaje es porque quiere focus
        {
            if (TaskBar::getInstance()->isTaskWindow(windowID)) //don't send focus to task list items
            {
                return true;
            }
            qDebug() << "\tLa ventana es un marco";
            XWindow* xwindow = wl->getXWindowByClientID(windowID);

            qDebug() << "\tModificando la lista del EWMH";
            this->wl->restackManagedWindow(xwindow);

            qDebug() << "\tActualizando la ventana activa";
            this->wl->setActiveWindow(xwindow);
        }
        else if(event->xclient.message_type == al->getAtom("_NET_WM_STRUT_PARTIAL") || event->xclient.message_type == al->getAtom("_NET_WM_STRUT")) //Como esta definido en el estandard, cuando se hace request con este mensaje es porque quiere focus
        {
            this->wl->updateWorkarea();
        }
        else if (event->xclient.message_type == al->getAtom("_NET_WM_WINDOW_TYPE")) //we have changed the window type maybe it is a dock!
        {
            XWindow* xwindow = this->wl->getXWindowByClientID(windowID);
            this->wl->restackManagedWindow(xwindow);
            this->wl->setActiveWindow(xwindow);
        }
        else if (event->xclient.message_type == al->getAtom("_FLYNNOSWM_WIDGET")) //we got hints change request
        {

            XWindow* xwindow = this->wl->getXWindowByClientID(windowID);

            Atom type;
            int format;
            unsigned long nitems=0;
            unsigned long extra=0;
            unsigned char *data=NULL;
            XGetWindowProperty(QX11Info::display(), windowID, al->getAtom("_FLYNNOSWM_WIDGET"), 0, 32, false, AnyPropertyType, &type, &format, &nitems, &extra, &data);
            if(data != NULL)
            {
                //quitamos el marco
                xwindow->dontRemoveAfterFrame = true;
                if ((int)*data > 0)
                    xwindow->removeFrame();

                XReparentWindow(QX11Info::display(), windowID,
                        QX11Info::appRootWindow(),
                        0,
                        0);

                xwindow->setX(100);
                xwindow->setY(100);
                xwindow->setWidth(400);
                xwindow->setHeight(400);
                xwindow->layout = true;
                this->wl->restackManagedWindow(xwindow);

                delete data;
            }
        }
        else
        {
        }
        return false;
    }
    else // Si la ventana no es un cliente
    {
        //qDebug() << "\tLa ventana no es un cliente";
        return false;
    }
}
