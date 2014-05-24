/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class Background
 * @authors Vicente Benavent
 *
 */
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "src/flynnoswm/util/Include.h"
#include "src/flynnoswm/config/Config.h"
#include "src/flynnoswm/xwindows/XWindow.h"
#include "src/flynnoswm/xwindows/XWindowList.h"
#include <QTimer>
/**
 * @~spanish
 * Singleton, Es el fondo, y los botones para cerrar el wm, siempre esta hasta atras de todo
 *
 * @~english
 * Singleton, TODO COMMENT
 */
class Background : public QWidget
{

    Q_OBJECT

    private:

        //----------------------------------------------------------------------

        //This timer sets the loop to update slot
        QTimer *timer;

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static Background* instance;

        // Ocultamos las constructoras
        /**
         * @~spanish
         * Crea el fondo
         * @param parent        Ventana padre.
         *
         * @~english
         * TO TRANSLATE
         */
        Background(QWidget* parent = 0);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * TO TRANSLATE
         */
        virtual ~Background();

        const Background& operator = (const Background& al){return al;}

        void paintEvent(QPaintEvent *a);

    protected:

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
        static Background* getInstance();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Sobreescribimos el método setVisible()
         * al hacerlo visible.
         * @param visible Si se hace visible o invisible.
         *
         * @~english
         * TO TRANSLATE
         */
        void setVisible(bool visible);

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Establece la coordenada X del fondo
         * @param x La coordenada X
         *
         * @~english
         * TO TRANSLATE
         */
        void setX(int x);

        /**
         * @~spanish
         * Establece la coordenada Y del fondo
         * @param y La coordenada Y
         *
         * @~english
         * TO TRANSLATE
         */
        void setY(int y);

        /**
         * @~spanish
         * Obtiene la coorderana X del fondo
         *
         * @~english
         * TO TRANSLATE
         */
        int getX();

        /**
         * @~spanish
         * Obtiene la coorderana Y del fondo
         *
         * @~english
         * TO TRANSLATE
         */
        int getY();

        /**
         * @~spanish
         * Establece el ancho del fondo
         * @param width El ancho del fondo
         *
         * @~english
         * TO TRANSLATE
         */
        void setWidth(unsigned int width);

        /**
         * @~spanish
         * Establece el alto del fondo
         * @param height El alto del fondo
         *
         * @~english
         * TO TRANSLATE
         */
        void setHeight(unsigned int height);

        /**
         * @~spanish
         * Devuelve el ancho del fondo
         * @return El ancho del fondo
         *
         * @~english
         * TO TRANSLATE
         */
        unsigned int getWidth() const;

        /**
         * @~spanish
         * Devuelve el alto del fondo
         * @return El alto del fondo
         *
         * @~english
         * TO TRANSLATE
         */
        unsigned int getHeight() const;

        //----------------------------------------------------------------------

    public slots:
        /**
         * @~spanish
         * Sin implementar
         *
         * @~english
         * TO TRANSLATE
         */
        void update();

        /**
         * @~spanish
         * Cerramos el window manager
         *
         * @~english
         * TO TRANSLATE
         */
        void closeWindowManager();

        /**
         * @~spanish
         * Abrimos una terminal
         *
         * @~english
         * TO TRANSLATE
         */
        void launchTerminal();

};

#endif // BACKGROUND_H
