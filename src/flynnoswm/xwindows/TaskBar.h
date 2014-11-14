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
#include "src/flynnoswm/xwindows/XWindow.h"
#include "src/flynnoswm/xwindows/XWindowList.h"
#include <QTimer>
#include <QTime>

/**
 * @~spanish
 * Singleton, Es la barra de tareas que maneja las ventanas, el reloj y los iconos del tray
 *
 * @~english
 * Singleton, This is the taskbar that handles windows, the clock and the tray icons
 */
class TaskBar : public QWidget
{

    Q_OBJECT

    private:


        struct bar_item
        {
            bar_item(XWindow *_win, QPushButton* _btn)
            {
                win_ = _win;
                btn_ = _btn;
            }

            XWindow* win_;
            QPushButton* btn_;
        };


        //----------------------------------------------------------------------

        // Label con la imagen de fondo de la barra de tareas
        QLabel* titlebar;

        // Label con la hora del reloj
        QLabel* clock_text;

        //Boton con el icono de la aplicacion que corre dmenu_run
        QPushButton* launcher;

        //This timer sets the loop to update the clock text
        QTimer *timer;

        QList<bar_item> task_bar_list_;

        /**
         * @~spanish
         * Única instancia de la clase.
         *
         * @~english
         * Single instance of the class.
         */
        static TaskBar* instance;

        // Ocultamos las constructoras
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



        const TaskBar& operator = (const TaskBar& al){return al;}

    protected:

    public:

        static bool ready_to_add;

        //Necesario para manejar las ventanas
        XWindowList* wl;

        /**
         * @~spanish
         * Regresa true si la ventana existe en la barra de tareas, false si no existe
         * @param el id de la vantana
         *
         * @~english
         * TO TRANSLATE
         */
        bool isTaskWindow(Window w);

        /**
         * @~spanish
         * Hace click en la ventana
         * @param el id de la vantana
         *
         * @~english
         * TO TRANSLATE
         */
        void clickTaskItem(Window w);

        /**
         * @~spanish
         * Le da el foco a la ventana en la barra de tareas (le cambia el color)
         * @param el id de la vantana
         *
         * @~english
         * TO TRANSLATE
         */
        void setFocus(XWindow* window);

        /**
         * @~spanish
         * Único método para obtener una instancia de la clase.
         * @return La única instancia de la clase.
         *
         * @~english
         * Only method to get an instance of the class.
         * @return The single instance of the class.
         */
        static TaskBar* getInstance();

        static TaskBar* getRaw(){return instance;};
        static void setRaw(TaskBar* t){instance = t;};

        /**
         * @~spanish
         * Agregamos una vetana a la barra de tareas
         * @param La ventana para agregar
         *
         * @~english
         * We adda  window to the bar
         * @param The window to add to the bar
         */
        void AddTask(XWindow* window_bar_);

        /**
         * @~spanish
         * Quitamos una vetana a la barra de tareas
         * @param La ventana para agregar
         *
         * @~english
         * We remove the window from the bar
         * @param The window to add to the bar
         */
        void RemoveTask(XWindow* window_bar_);

        /**
         * @~spanish
         * Actualizamos la lista y sus tamaños
         *
         * @~english
         * We update the lista and sizes
         */
        void UpdateTitles();

        void UpdateTitlesSizes();

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

        /**
         * @~spanish
         * Es llamado cuando se da click a la barra de tareas a un item
         *
         * @~english
         * TO TRANSLATE
         */
        void click_item();

        /**
         * @~spanish
         * Es llamado cuando se da click al launcher para correr dmenu
         *
         * @~english
         * TO TRANSLATE
         */
        void clickLauncher();

};

#endif // TASKBAR_H
