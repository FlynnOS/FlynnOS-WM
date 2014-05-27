/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  MotionNotifyHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "MotionNotifyHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MotionNotifyHandler::MotionNotifyHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool MotionNotifyHandler::processEvent(XEvent* event)
{
    if (this->wl->moveResizeWindow != 0 && this->wl->moveResizeAction == 8) //move window
    {
        int diffx = this->wl->moveResizeStartX-this->wl->moveResizeWindow->getX();
        int diffy = this->wl->moveResizeStartY-this->wl->moveResizeWindow->getY();
        this->wl->moveResizeWindow->setX(event->xmotion.x_root-diffx);
        this->wl->moveResizeWindow->setY(event->xmotion.y_root-diffy);
        this->wl->moveResizeStartX = event->xmotion.x_root;
        this->wl->moveResizeStartY = event->xmotion.y_root;
    }

    return false;
}
