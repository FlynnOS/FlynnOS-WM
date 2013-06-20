/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class TaskBar
 * @authors MinimizeFloat
 *
 */
#ifndef MINIMIZEFLOAT_H
#define MINIMIZEFLOAT_H

#include "src/flynnoswm/util/Include.h"
#include "src/flynnoswm/config/Config.h"
#include "src/flynnoswm/xwindows/XWindow.h"
#include <QTimer>
#include <QTime>

/**
 * @~spanish
 * Cuando le das click al segundo minimizar aqui se crean y manejan
 *
 * @~english
* Here we manage and create the "Small minimized" windows
 */
class MinimizeFloat : public QLabel
{

    Q_OBJECT

    private:

        //----------------------------------------------------------------------

        //The position of mouse used for drag
        QPoint mousePos;

        //The image that we got for the preview
        QPixmap windowPixmap;


    protected:

        /**
         * @~spanish
         * Click izquierdo empieza a hacer el drag del preview
         * Click derecho crea un menu con mas acciones
         * @param MouseEvent El evento de mouse
         *
         * @~english
         * TO TRANSLATE
         */
        void mousePressEvent(QMouseEvent *event);

        /**
         * @~spanish
         * Actualiza la posicion cuando estamos haciendo drag
         * @param MouseEvent El evento de mouse
         *
         * @~english
         * TO TRANSLATE
         */
        void mouseMoveEvent(QMouseEvent *event);

        /**
         * @~spanish
         * Detiene el drag para el movimiento
         * @param MouseEvent El evento de mouse
         *
         * @~english
         * TO TRANSLATE
         */
        void mouseReleaseEvent(QMouseEvent *event);

        /**
         * @~spanish
         * Activa de nuevo la ventana
         * @param MouseEvent El evento de mouse
         *
         * @~english
         * TO TRANSLATE
         */
        void mouseDoubleClickEvent(QMouseEvent *event);

        /**
         * @~spanish
         * Cambia el borde para que veamos que estamos seleccionandolo
         * @param MouseEvent El evento de mouse
         *
         * @~english
         * TO TRANSLATE
         */
        void enterEvent(QEvent *event);

        /**
         * @~spanish
         * Cambia el borde para que veamos que dejamos de seleccionarlo
         * @param MouseEvent El evento de mouse
         *
         * @~english
         * TO TRANSLATE
         */
        void leaveEvent(QEvent *event);


    public:

        //a pointer to the window
        XWindow* window;

        /**
         * @~spanish
         * Crea una nueva ventana mini
         * @param parent        Ventana padre.
         *
         * @~english
         * TO TRANSLATE
         */
        MinimizeFloat(XWindow* window, QWidget* parent = 0);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * TO TRANSLATE
         */
        virtual ~MinimizeFloat();

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
         * Cerramos la ventana y la liberamos de memoria, no sigfinica que
         * la ventana vaya a mostrarse o borrarse, solo quiamos el cuadro
         * de preview
         *
         * @~english
         * TO TRANSLATEw
         */
        void closeWindow();

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

    public slots:
        /**
         * @~spanish
         * Se da click al menu del preview, para cerrar o abrir la ventana
         *
         * @~english
         * TO TRANSLATE
         */
        void menuClick(QAction *act);

};

#endif // MINIMIZEFLOAT_H
