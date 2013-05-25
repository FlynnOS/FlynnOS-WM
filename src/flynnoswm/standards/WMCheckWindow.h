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
#ifndef WMCHECKWINDOW_H
#define WMCHECKWINDOW_H

#include "src/flynnoswm/util/Include.h"
#include "src/flynnoswm/atoms/AtomList.h"

/**
 * @~spanish
 * Ventana que se usa para implementar el hint _NET_SUPPORTING_WM_CHECK.
 * La propiedad _NET_SUPPORTING_WM_CHECK debe llevar el valor de winId() y la
 * propiedad _NET_WM_NAME el valor "Flynn OS WM".
 *
 * @~english
 * Window used to implement the  _NET_SUPPORTING_WM_CHECK hint.
 * The _NET_SUPPORTING_WM_CHECK must be set to winId() and _NET_WM_NAME must be
 * set to "Flynn OS WM".
 */
class WMCheckWindow : public QWidget {

    public:

        /**
         * @~spanish
         * Crea la ventana.
         *
         * @~english
         * Create the window.
         */
        WMCheckWindow();
};

#endif // WMCHECKWINDOW_H
