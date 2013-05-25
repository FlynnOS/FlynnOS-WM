/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class AtomList
 * @authors José Expósito, Vicente Benavent
 *
 */
#ifndef ATOMLIST_H
#define ATOMLIST_H

#include "src/flynnoswm/util/Include.h"


/**
 * @~spanish
 * Singleton que mantiene una lista de todos los Atoms usados por FlynnOSwm.
 *
 * @~english
 * Singleton that maintains a list of all Atoms used by FlynnOSwm.
 */
class AtomList {

    private:

        /**
         * @~spanish
         * Hash que contiene los atoms, siendo su nombre la clave y el propio
         * atom el valor.
         *
         * @~english
         * Hash that contains the atoms, where the name is the key and the atom
         * is the value.
         */
        QHash<const char*, Atom>* atomHash;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static AtomList* instance;

        // Ocultamos las constructoras
        AtomList();
        AtomList(const AtomList&){}
        const AtomList& operator = (const AtomList& al){return al;}

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
        static AtomList* getInstance();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el atom especificado.
         * @param atomName El nombre del atom que se quiere obtener, por ejemplo
         *        "_NET_SUPPORTED".
         *
         * @~english
         * Returns the specified atom.
         * @param atomName The name of the atom to get, for example
         *        "_NET_SUPPORTED".
         *
         */
        Atom getAtom(const char* atomName);
};

#endif // ATOMLIST_H
