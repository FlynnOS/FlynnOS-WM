/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  EventFactory
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "EventFactory.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

EventFactory* EventFactory::instance = NULL;

EventFactory* EventFactory::getInstance() {
    if(EventFactory::instance == NULL)
        EventFactory::instance = new EventFactory();

    return EventFactory::instance;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

void EventFactory::initialize(XWindowList* windowList) {

    // MapRequest
    this->eventHandlerHash.insert(MapRequest, new MapRequestHandler(
            windowList));

    // ConfigureRequest
    this->eventHandlerHash.insert(ConfigureRequest,new ConfigureRequestHandler(
            windowList));

    //--------------------------------------------------------------------------

    // CreateNotify
    this->eventHandlerHash.insert(CreateNotify, new CreateNotifyHandler(
            windowList));

    // DestroyNotify
    this->eventHandlerHash.insert(DestroyNotify, new DestroyNotifyHandler(
            windowList));

    // UnmapNotify
    this->eventHandlerHash.insert(UnmapNotify, new UnmapNotifyHandler(
            windowList));

    //--------------------------------------------------------------------------

    // ButtonPress
    this->eventHandlerHash.insert(ButtonPress, new ButtonPressHandler(
            windowList));

    //--------------------------------------------------------------------------

    // ClientMessage
    this->eventHandlerHash.insert(ClientMessage, new ClientMessageHandler(
            windowList));

    // PropertyNotify
    this->eventHandlerHash.insert(PropertyNotify, new PropertyNotifyHandler(
            windowList));

    // EnterNotify
    this->eventHandlerHash.insert(EnterNotify, new EnterNotifyRequestHandler(
            windowList));

    // KeyPress
    this->eventHandlerHash.insert(KeyPress, new KeyPressHandler(
            windowList));

    // Motion Notify
    this->eventHandlerHash.insert(MotionNotify, new MotionNotifyHandler(
            windowList));


    windowList_ = windowList;
}

EventHandler* EventFactory::getEventHandler(int eventType) const
{
    if(this->eventHandlerHash.contains(eventType))
    {
        return this->eventHandlerHash.value(eventType);
    }
    else
    {
        return NULL;
    }
}
