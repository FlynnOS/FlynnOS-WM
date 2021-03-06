/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class ConfigureRequestHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "ConfigureRequestHandler.h"
#include "src/flynnoswm/xwindows/TaskBar.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ConfigureRequestHandler::ConfigureRequestHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool ConfigureRequestHandler::processEvent(XEvent* event) {
    Window windowID = event->xconfigurerequest.window;
    qDebug() << "[+] ConfigureRequest event 0x" << hex << windowID;

    // Si la ventana es un cliente
    if(this->wl->existClient(windowID)) {
        qDebug() << "\tLa ventana es un cliente, configurándolo...";
        XWindow* xwindow = this->wl->getXWindowByClientID(windowID);

        // Si el cliente bypassea el WM
        if(xwindow->bypassWM())
        {
            qDebug() << "\tEl cliente bypassea el WM";
            return false;

        // Si no lo bypassea
        }
        else if (TaskBar::getInstance()->isSystrayWindow(xwindow))
        {
            //no permitimos cambios de tamaño, mantenemos el tamaño del icono en el tray
            return false;
        }
        else
        {
            if(event->xconfigurerequest.value_mask & CWX)
                xwindow->setX(event->xconfigurerequest.x);

            if(event->xconfigurerequest.value_mask & CWY)
                xwindow->setY(event->xconfigurerequest.y);

            // Hay que comprobar si la ventana tiene o no marco porque si no
            // las ventanas que solo aceptan tamaños múltiplos de un cierto
            // número dan problemas

            Config* cfg = Config::getInstance();

            if(event->xconfigurerequest.value_mask & CWWidth)
            {
                if(xwindow->haveFrame())
                    xwindow->setWidth(event->xconfigurerequest.width
                            + cfg->getLeftBorderWidth()
                            + cfg->getRightBorderWidth());
                else
                    xwindow->setWidth(event->xconfigurerequest.width);
            }

            if(event->xconfigurerequest.value_mask & CWHeight)
            {
                if(xwindow->haveFrame())
                    xwindow->setHeight(event->xconfigurerequest.height
                            + cfg->getTitlebarWidth() + cfg->getTopBorderWidth()
                            + cfg->getBottomBorderWidth());
                else
                    xwindow->setHeight(event->xconfigurerequest.height);
            }

            return true;
        }

    // Si no es un cliente
    }
    else
    {
        qDebug() << "\tLa ventana no es un cliente";
        return false;
    }
}
