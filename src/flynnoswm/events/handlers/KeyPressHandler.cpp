/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class KeyPressHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "KeyPressHandler.h"
#include "src/flynnoswm/config/SystemKeys.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

KeyPressHandler::KeyPressHandler(XWindowList* wl)
        : EventHandler(wl)
{

}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool KeyPressHandler::processEvent(XEvent* event)
{
    unsigned int key_pressed = event->xkey.keycode;
    unsigned int mask = event->xkey.state;
    qDebug() << "[+] KeyPress event Key: " << key_pressed << " Mask: " << mask;
    SystemKeys::getInstance()->ProcessKey(key_pressed,mask);
    //qDebug() << "Bit is set? " << (mask & (Mod1Mask));

    return true;
}
