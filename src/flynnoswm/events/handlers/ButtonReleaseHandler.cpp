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
#include "ButtonReleaseHandler.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

ButtonReleaseHandler::ButtonReleaseHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool ButtonReleaseHandler::processEvent(XEvent* event)
{
    if (this->wl->moveResizeWindow != 0 && event->xbutton.button == this->wl->moveResizeButton) //we release the button
    {
        this->wl->moveResizeWindow = 0;
    }

    return false;
}
