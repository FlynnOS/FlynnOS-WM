/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  WMCheckWindow
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "WMCheckWindow.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

WMCheckWindow::WMCheckWindow() {
    AtomList* al = AtomList::getInstance();

    this->setWindowTitle("Flynn OS WM");

    int id = this->winId();
    XChangeProperty(QX11Info::display(), id,
            al->getAtom("_NET_SUPPORTING_WM_CHECK"),
            al->getAtom("WINDOW"), 32, PropModeReplace,
            (unsigned char*)&id, 1);
}
