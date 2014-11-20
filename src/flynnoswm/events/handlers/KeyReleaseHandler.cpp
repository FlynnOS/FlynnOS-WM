/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class KeyReleaseHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "KeyReleaseHandler.h"
#include "src/flynnoswm/config/SystemKeys.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

KeyReleaseHandler::KeyReleaseHandler(XWindowList* wl)
        : EventHandler(wl)
{

}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool KeyReleaseHandler::processEvent(XEvent* event)
{
    //unsigned int key_pressed = event->xkey.keycode;
    //unsigned int mask = event->xkey.state;
    //qDebug() << "[+] KeyyRelease event Key: " << key_pressed << " Mask: " << mask;
    //qDebug() << XKeysymToString(XKeycodeToKeysym(QX11Info::display(), event->xkey.keycode, 0));

    return true;
}
