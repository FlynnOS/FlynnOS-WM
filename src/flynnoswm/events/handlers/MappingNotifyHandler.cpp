/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class MappingNotifyHandler
 * @authors Vicente Benavent
 *
 */
#include "MappingNotifyHandler.h"
#include "src/flynnoswm/xwindows/TaskBar.h"
#include "src/flynnoswm/config/SystemKeys.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MappingNotifyHandler::MappingNotifyHandler(XWindowList* wl)
        : EventHandler(wl)
{
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool MappingNotifyHandler::processEvent(XEvent* event)
{
    qDebug() << "[+] MappingNotify event";

    XMappingEvent *ev = &event->xmapping;

    XRefreshKeyboardMapping(ev);
    XUngrabKey(QX11Info::display(), AnyKey, AnyModifier, QX11Info::appRootWindow(QX11Info::appScreen()));
    if(ev->request == MappingKeyboard)
        SystemKeys::getInstance()->configureSystemKeys();

    return true;
}
