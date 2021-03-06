/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  EventHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "src/flynnoswm/util/Include.h"
#include "src/flynnoswm/xwindows/XWindowList.h"
#include "src/flynnoswm/xwindows/XWindow.h"
#include "src/flynnoswm/standards/EWMHRoot.h"


/**
 * @~spanish
 * Interfaz que deben implementar todos los manejadores de eventos.
 *
 * @~english
 * Interface that must implement all event handlers.
 */
class EventHandler {

    protected:

        /**
         * @~spanish
         * Lista de ventanas.
         *
         * @~english
         * Window list.
         */
        XWindowList* wl;

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
        EventHandler(XWindowList* wl) {
            this->wl = wl;
        }

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
        virtual bool processEvent(XEvent* event) = 0;

};

#endif // EVENTHANDLER_H
