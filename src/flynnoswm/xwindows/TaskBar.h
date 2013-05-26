/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class TaskBar
 * @authors Vicente Benavent
 *
 */
#ifndef TASKBAR_H
#define TASKBAR_H

#include "src/flynnoswm/util/Include.h"
#include "src/flynnoswm/config/Config.h"
#include <QTimer>
#include <QTime>

/**
 * @~spanish
 * Es la barra de tareas que maneja las ventanas, el reloj y los iconos del tray
 *
 * @~english
* This is the taskbar that handles windows, the clock and the tray icons
 */
class TaskBar : public QWidget {

    Q_OBJECT

    private:

        //----------------------------------------------------------------------

        // Label con la imagen de fondo de la barra de tareas
        QLabel* titlebar;

        // Label con la hora del reloj
        QLabel* clock_text;

        //This timer sets the loop to update the clock text
        QTimer *timer;

    protected:

    public:

        /**
         * @~spanish
         * Crea una barra de tareas
         * @param parent        Ventana padre.
         *
         * @~english
         * TO TRANSLATE
         */
        TaskBar(QWidget* parent = 0);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * TO TRANSLATE
         */
        virtual ~TaskBar();

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
         * Establece la coordenada X de la barra de tareas
         * @param x La coordenada X
         *
         * @~english
         * TO TRANSLATE
         */
        void setX(int x);

        /**
         * @~spanish
         * Establece la coordenada Y de la barra de tareas
         * @param y La coordenada Y
         *
         * @~english
         * TO TRANSLATE
         */
        void setY(int y);

        /**
         * @~spanish
         * Obtiene la coorderana X de la barra de tareas
         *
         * @~english
         * TO TRANSLATE
         */
        int getX();

        /**
         * @~spanish
         * Obtiene la coorderana Y  de la barra de tareas
         *
         * @~english
         * TO TRANSLATE
         */
        int getY();

        /**
         * @~spanish
         * Establece el ancho de la barra de tareas
         * @param width El ancho de la barra de tareas
         *
         * @~english
         * TO TRANSLATE
         */
        void setWidth(unsigned int width);

        /**
         * @~spanish
         * Establece el alto de la barra de tareas
         * @param height El alto de la barra de tareas
         *
         * @~english
         * TO TRANSLATE
         */
        void setHeight(unsigned int height);

        /**
         * @~spanish
         * Devuelve el ancho de la barra de tareas
         * @return El ancho de la barra de tareas
         *
         * @~english
         * TO TRANSLATE
         */
        unsigned int getWidth() const;

        /**
         * @~spanish
         * Devuelve el alto de la barra de tareas
         * @return El alto de la barra de tareas
         *
         * @~english
         * TO TRANSLATE
         */
        unsigned int getHeight() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Cambia el texto a mostrar en el area del reloj
         * @param title El nuevo texto.
         *
         * @~english
         * TO TRANSLATE
         */
        void setClockText(const QString& title);

    public slots:
        /**
         * @~spanish
         * Es llamado cada segudo, cambia el texto a mostrar en el area del reloj automaticamente
         *
         * @~english
         * TO TRANSLATE
         */
        void update();

};

#endif // TASKBAR_H
