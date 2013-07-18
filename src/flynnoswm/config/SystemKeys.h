/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class SystemKeys
 * @authors Vicente Benavent
 *
 */
#ifndef SYSTEMKEYS_H
#define SYSTEMKEYS_H

#include "src/flynnoswm/util/Include.h"
#include <map>


enum key_events {KEY_CLOSE_WINDOW,KEY_OPEN_TERMINAL, KEY_ALT_TAB, KEY_END_EVENTS};

/**
 * @~spanish
 * Singleton que facilita el acceso a la configuración del WM.
 *
 * @~english
 * Singleton that provides access to the configuration of WM.
 */
class SystemKeys
{

    private:

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static SystemKeys* instance;


        void createModifiers(Display * display);

        void addKey(int keycode, unsigned int mask);


        // Ocultamos las constructoras
        SystemKeys()
        {
            NumberLockMask = 0;
            ScrollLockMask = 0;
            CapsLockMask = 0;
        }
        SystemKeys(const SystemKeys&)
        {
            NumberLockMask = 0;
            ScrollLockMask = 0;
            CapsLockMask = 0;
        }
        const SystemKeys& operator = (const SystemKeys& c){return c;}

        unsigned int NumberLockMask;
        unsigned int ScrollLockMask;
        unsigned int CapsLockMask;

        //this is the key list
        //First parameter is key_code, second is mask
        //[key_code][mask]
        std::map<unsigned int, std::map<unsigned int, key_events> > key_list;



    public:

        /**
         * @~spanish
         * Único método para obtener una instancia de la clase.
         * @return La única instancia de la clase.
         *
         * @~english
         * Only method to get an instance of the class.
         * @return The single instance of the class.
         */
        static SystemKeys* getInstance();

        /**
         * @~spanish
         * (Re)carga la configuración.
         *
         * @~english
         * (Re)load the config.
         */
        void configureSystemKeys();

        void ProcessKey(unsigned int keycode, unsigned int mask);

        void insertKey(unsigned int keycode, unsigned int mask,key_events _e);
};

#endif // CONFIG_H
