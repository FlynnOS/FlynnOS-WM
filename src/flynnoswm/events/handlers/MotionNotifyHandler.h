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
#ifndef MOTIONNOTIFYHANDLER_H
#define MOTIONNOTIFYHANDLER_H

#include "src/flynnoswm/events/handlers/EventHandler.h"


/**
 * @~spanihs
 * Evento que se llamará cuando el mouse se mueve. El WM se encargará de
 * procesar esto en caso de que la ventana se lo pida por ejemplo NET_WM_MOVERESIZE
 *
 * @~english
 * TODO
 */
class MotionNotifyHandler : public EventHandler {

    public:

        /**
         * @~spanish
         * Constructora por defecto.
         * @param wl La lista de ventanas.
         *
         * @~english
         * Default constructor.
         * @param wl The window list.
         */
        MotionNotifyHandler(XWindowList* wl);

        /**
         * @~spanish
         * Procesa el evento.
         * @param event El evento a procesar.
         * @return true para evitar que el evento sea tratado con normalidad, es
         *         decir, cuando ya lo tratamos nosotros, false para que el
         *         evento se trate con normalidad.
         *
         * @~english
         * Process the event.
         * @param event The event to be processed.
         * @return true if you want to stop the event from being processed, ie
         *         when we treat ourselves, false for normal event dispatching.
         */
        virtual bool processEvent(XEvent* event);
};

#endif // MOTIONNOTIFYHANDLER_H
