/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class EventFactory
 * @authors José Expósito, Vicente Benavent
 *
 */
#ifndef EVENTFACTORY_H
#define EVENTFACTORY_H

#include "src/flynnoswm/util/Include.h"
#include "src/flynnoswm/events/handlers/EventHandler.h"
#include "src/flynnoswm/events/handlers/MapRequestHandler.h"
#include "src/flynnoswm/events/handlers/ConfigureRequestHandler.h"
#include "src/flynnoswm/events/handlers/CreateNotifyHandler.h"
#include "src/flynnoswm/events/handlers/DestroyNotifyHandler.h"
#include "src/flynnoswm/events/handlers/UnmapNotifyHandler.h"
#include "src/flynnoswm/events/handlers/ButtonPressHandler.h"
#include "src/flynnoswm/events/handlers/ClientMessageHandler.h"
#include "src/flynnoswm/events/handlers/PropertyNotifyHandler.h"
#include "src/flynnoswm/events/handlers/EnterNotifyRequestHandler.h"
#include "src/flynnoswm/events/handlers/KeyPressHandler.h"
#include "src/flynnoswm/events/handlers/MotionNotifyHandler.h"

/**
 * @~spanish
 * Factoría para obtener los distintos manejadores de eventos.
 *
 * @~english
 * Factory for get the differents event handlers.
 */
class EventFactory {

    private:

        /**
         * @~spanish
         * Tabla hash que asocia a cada evento la clase que lo tratará, siendo
         * event->type la clave y el handler del evento el valor.
         *
         * @~english
         * Hash table that associates each event with the class that will treat
         * it, being event->type the key and the event handler the value.
         */
        QHash<int, EventHandler*> eventHandlerHash;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static EventFactory* instance;

        // Ocultamos las constructoras
        EventFactory(){}
        EventFactory(const EventFactory&){}
        const EventFactory& operator = (const EventFactory& ef){return ef;}

    public:

        /**
         * @~spanish
         * Único método para obtener una instancia de la clase.
         * @return La única instancia de la clase.
         * @see EventFactory::initialize().
         *
         * @~english
         * Only method to get an instance of the class.
         * @return The single instance of the class.
         * @see EventFactory::initialize().
         */
        static EventFactory* getInstance();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Inicializa la factoría de eventos.
         * @param windowList Lista de ventanas que usarán los handlers.
         *
         * @~english
         * Initializes the event factory.
         * @param windowList Window list that will use the event handlers.
         */
        void initialize(XWindowList* windowList);

        /**
         * @~spanish
         * Devuelve el manejador de eventos especificado, NULL si FlynnOSwm no trata
         * el tipo de evento especificado.
         * @return Dicho evento o NULL.
         *
         * @~english
         * Returns the specified event handler, NULL if FlynnOSwm not treated the
         * event.
         * @return The event handler or NULL.
         */
        EventHandler* getEventHandler(int eventType) const;

        /**
         * @~spanish
         * Un puntero hacia la lista de ventanas, como esta clase es un singleton
         * la ponemos aqui para accesarla desde otras clases
         * TODO: moverla a una clase de recursos globales
         *
         * @~english
         * A pointer to the window list, because this is a singleton class
         * we put it here so we can access it from other classes
         */
        XWindowList* windowList_;

};

#endif // EVENTFACTORY_H
