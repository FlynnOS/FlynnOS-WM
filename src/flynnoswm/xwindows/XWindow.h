/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class XWindow
 * @authors José Expósito, Vicente Benavent
 *
 */
#ifndef XWINDOW_H
#define XWINDOW_H

#include "src/flynnoswm/util/Include.h"
#include "src/flynnoswm/xwindows/Client.h"
#include "src/flynnoswm/xwindows/ClientFrame.h"
#include "src/flynnoswm/atoms/AtomList.h"

class MinimizeFloat;


/**
 * @~spanish
 * Representa las ventanas gestionadas o no por el WM.
 * XWindow estará compuesta por un cliente y si este lo requiere también un
 * marco, ofreciendo métodos para gestionarlos.
 *
 * El cliente es una ventana ajena al WM que puede o no ser decorada con un
 * marco. Se representa con la clase "Client".
 *
 * El marco es una ventana, a la que se hará padre del cliente, que sirve para
 * decorar al cliente, mostrar su titulo y permitir gestionarlo fácilemnte
 * (desplazarlo por la pantalla, agrandarlo, cerrarlo...). Se representa con la
 * clase "ClientFrame".
 *
 * @~english
 * TO TRANSLATE
 */
class XWindow : public QObject
{

    Q_OBJECT

    private:

        /**
        * We save the frame position and size, when we click again maximize it will be set back to this sizes
        */
        int old_x_;
        int old_y_;
        int old_width_;
        int old_height_;

        bool maximized_; //if we have maximized atleast once this is set to true, it can happen that a window start maximized, this could be a huge problem

        /**
         * @~spanish
         * El cliente.
         *
         * @~english
         * TO TRANSLATE
         */
        Client* client;

        /**
         * @~spanish
         * Marco del cliente en caso de tener. Si no tiene es NULL.
         *
         * @~english
         * TO TRANSLATE
         */
        ClientFrame* frame;

        MinimizeFloat *minimizeFloat;

        /**
         * @~spanish
         * ID del cliente.
         *
         * @~english
         * TO TRANSLATE
         */
        Window clientID;

        /**
         * @~spanish
         * ID del frame. Es necesario acumularlo por si se quiere obtener este
         * ID tras haber llamado a removeFrame().
         *
         * @~english
         * TO TRANSLATE
         */
        Window frameID;

        /**
         * @~spanish
         * Estado de la ventana. Inicialmente las ventanas se crean con estado
         * WithdrawnState. Los posibles estados son:
         * - WithdrawnState: Ni el cliente ni su icono son visibles.
         * - NormalState:    El cliente es visible.
         * - IconicState:    El cliente está iconificado (minimizado).
         *
         * @~english
         * TO TRANSLATE
         */
        int state;

    public:
        bool full_screen_;
        bool in_taskbar_; //if true this window has to be added to the taskbar, if false not

        /**
         * @~spanish
         * Crea una ventana.
         * @param clientID ID del cliente que encapsula la ventana.
         *
         * @~english
         * TO TRANSLATE
         */
        XWindow(const Window& clientID);

        /**
         * @~spanish
         * Destructor.
         *
         * @~english
         * TO TRANSLATE
         */
        ~XWindow();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Indica si la ventana "bypassea" el WM.
         * @return true si la ventana se salta el WM, false en caso contrario,
         *         es decir, hay que ponerla borde, etc.
         *
         * @~english
         * TO TRANSLATE
         */
        bool bypassWM() const;

        //----------------------------------------------------------------------
        /**
         * @~spanish
         * Añade el valor del dock al tamaño de escritorio para no maximizar ventanas ahi
         *
         * @~english
         * TO TRANSLATE
         */
        void addDock();

        /**
         * @~spanish
         * Añade un marco a la ventana siempre que esta lo necesite y no tenga
         * ya uno.
         *
         * @~english
         * TO TRANSLATE
         */
        void addFrame();

        /**
         * @~spanish
         * Elimina el marco de la ventana, liberando memoria y desencadenando
         * los correspondientes eventos UnmapNotify y DestroyNotify.
         *
         * @~english
         * TO TRANSLATE
         */
        void removeFrame();

        /**
         * @~spanish
         * Indica si la ventana tiene o no marco.
         * @return true si tiene, false en caso contrario.
         *
         * @~english
         * TO TRANSLATE
         */
        bool haveFrame() const;

        /**
         * @~spanish
         * Indica si la ventana necesita o no un marco dependiendo de su tipo,
         * por ejemplo una ventana del tipo menú o del tipo escritorio no lo
         * necesita.
         * @return Si lo necesita o no.
         *
         * @~english
         * TO TRANSLATE
         */
        bool needFrame();

        /**
         * @~spanish
         * Maximiza la ventana tomando en cuenta _NET_WORKSPACE
         *
         * @~english
         * TO TRANSLATE
         */
        void maximizeFrame();

        /**
         * @~spanish
         * Actualiza el espacio de la ventana maximizada cuando _NET_WORKSPACE cambia
         *
         * @~english
         * TO TRANSLATE
         */
        void updateMaximizedWindow();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Cambia el estado de la ventana. Los posibles estados son:
         * - WithdrawnState: Ni el cliente ni su icono son visibles.
         * - NormalState:    El cliente es visible.
         * - IconicState:    El cliente está iconificado (minimizado).
         * @param state El nuevo estado de la ventana.
         *
         * @~english
         * TO TRANSLATE
         */
        void setState(int state);

        /**
         * @~spanish
         * Devuelve el estado actual de la ventana.
         * @return El estado actual de la ventana.
         *
         * @~english
         * TO TRANSLATE
         */
        int getState() const;

        /**
         * @~spanish
         * Devuelve el cliente
         * @return Un aputador al cliente.
         *
         * @~english
         * TO TRANSLATE
         */
        Client* getClient();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el ID del cliente.
         * @return El ID.
         *
         * @~english
         * TO TRANSLATE
         */
        Window getClientID() const;

        /**
         * @~spanish
         * Devuelve el ID del marco de la ventana. Si la ventana nunca ha tenido
         * marco devolverá 0, si la ventana ha tenido o tiene marco dvuelve el
         * ID del último marco creado con addFrame(), pese a haber llamado a
         * removeFrame().
         * @return El ID.
         *
         * @~english
         * TO TRANSLATE
         */
        Window getFrameID() const;

        /**
         * @~spanish
         * Devuelve el grupo al que pertenece la ventana. De no pertenecer a
         * ninguno devuelve 0.
         * @return El grupo.
         *
         * @~english
         * TO TRANSLATE
         */
        XID getWindowGroup() const;

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Asigna el foco a la ventana en caso de que el cliente lo requiera.
         *
         * @~english
         * TO TRANSLATE
         */
        void setFocus() const;

        /**
         * @~spanish
         * Devuelve una lista con los estados del cliente
         * @return Lista de estados.
         *
         * @~english
         * Returns a list with windows state
         * @return The window type list
         */
        QList<Atom> getClientState();

        /**
         * @~spanish
         * Obtienes los estados del cliente y guarda los valores apropiados.
         *
         * @~english
         * TO TRANSLATE
         */
        void setClientState();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Devuelve el tipo del que es la ventana.
         * @return El tipo.
         *
         * @~english
         * TO TRANSLATE
         */
        Atom getWindowType() const;

        /**
         * @~spanish
         * Indica si una ventana debe estar siempre en la cima de la pila.
         * @return Si debe o no estar en la cima de la pila.
         *
         * @~english
         * TO TRANSLATE
         */
        bool isTopWindow() const;

        /**
         * @~spanish
         * Indica si una ventana debe estar siempre en el fondo de la pila.
         * @return Si debe o no estar en el fondo de la pila.
         *
         * @~english
         * TO TRANSLATE
         */
        bool isBottomWindow() const;

        /**
         * @~spanish
         * Revisamos si debo estar en el taskbar o no
         *
         * @~english
         * TO TRANSLATE
         */
        void setTaskBar();

        //----------------------------------------------------------------------

        /**
         * @~spanish
         * Obtine la coordenada X de la ventana. Si tiene marco obtiene
         * la coordenada Y del mismo, si no tiene la de la ventana.
         * @param y La coordenada Y respecto a la ventana madre.
         *
         * @~english
         * TO TRANSLATE
         */
        int getX();

        /**
         * @~spanish
         * Obtine la coordenada X de la ventana. Si tiene marco obtiene
         * la coordenada Y del mismo, si no tiene la de la ventana.
         * @param y La coordenada Y respecto a la ventana madre.
         *
         * @~english
         * TO TRANSLATE
         */
        int getY();

        /**
         * @~spanish
         * Establece la coordenada X de la ventana. Si tiene marco se establece
         * la coordenada X del mismo, si no tiene la de la ventana.
         * @param x La coordenada X respecto a la ventana madre.
         *
         * @~english
         * TO TRANSLATE
         */
        void setX(int x);

        /**
         * @~spanish
         * Establece la coordenada Y de la ventana. Si tiene marco se establece
         * la coordenada Y del mismo, si no tiene la de la ventana.
         * @param y La coordenada Y respecto a la ventana madre.
         *
         * @~english
         * TO TRANSLATE
         */
        void setY(int y);

        /**
         * @~spanish
         * Establece el ancho de la ventana, marco incluido si tiene uno.
         * @param width El ancho de la ventana.
         *
         * @~english
         * TO TRANSLATE
         */
        void setWidth(unsigned int width);

        /**
         * @~spanish
         * Establece el alto de la ventana, marco incluido si tiene uno.
         * @param height El alto de la ventana.
         *
         * @~english
         * TO TRANSLATE
         */
        void setHeight(unsigned int height);

        /**
         * @~spanish
         * Devuelve el ancho de la ventana, marco incluido si tiene uno.
         * @return El ancho de la ventana.
         *
         * @~english
         * TO TRANSLATE
         */
        unsigned int getWidth() const;

        /**
         * @~spanish
         * Devuelve el alto de la ventana, marco incluido si tiene uno.
         * @return El alto de la ventana.
         *
         * @~english
         * TO TRANSLATE
         */
        unsigned int getHeight() const;

        /**
         * @~spanish
         * Actualizamos el titulo de la ventana, lo llamamos desde PropertyNotifyHandler
         *
         * @~english
         * We update the title of the window, we call it from PropertyNotifyHandler
         */
        void updateTitle();

        /**
         * @~spanish
         * Obtiene el marco el título indicado para ayudar al usuario a
         * identificar las ventanas.
         *
         * @~english
         * TO TRANSLATE
         */
        QString getTitle();

        /**
         * @~spanish
         * Obtiene la ventana minimizada
         *
         * @~english
         * TO TRANSLATE
         */
        MinimizeFloat* getMinimizedFloat();

        /**
         * @~spanish
         * Actualiza la ventana minimizada
         *
         * @~english
         * TO TRANSLATE
         */
        void setMinimizedFloat(MinimizeFloat* m);

        /**
         * @~spanish
         * Ver client.h, funccion con el mismo nombre
         *
         * @~english
         * TO TRANSLATE
         */
        MWMHints* getMotifWm();

    public slots:

        /**
         * @~spanish
         * Slot que regresa si la ventana esta maximizada
         * @return true si la ventana esta maximizada, false si no.
         *
         * @~english
         * TO TRANSLATE
         */
        bool isMaximized();

        /**
         * @~spanish
         * Slot que se llama cuando el usuario redimensiona el marco. Se debe
         * redimensionar también el cliente. Se podrá redimensionar siempre que
         * el nuevo tamaño se ajuste a los mínimos y máximos solicitados por el
         * cliente.
         * @param width  Ancho a ampliar o disminuir.
         * @param height Alto a ampliar o disminuir.
         * @return true si se ha podido redimensionar la ventana, false si no.
         *
         * @~english
         * TO TRANSLATE
         */
        bool resizedFrame(int width, int height);

        /**
         * @~spanish
         * Slot que se llama cuando el usuario hace click en el botón minimizar.
         *
         * @~english
         * TO TRANSLATE
         */
        void minimizedFrame();

        /**
         * @~spanish
         * Slot que se llama cuando el usuario hace click en el botón maximizar.
         *
         * @~english
         * TO TRANSLATE
         */
        void maximizedFrame();

        /**
         * @~spanish
         * Slot que se llama cuando el usuario hace click en el botón salir.
         *
         * @~english
         * TO TRANSLATE
         */
        void closedFrame();

        void fullScreenBorder();

        /**
         * @~spanish
         * Señal que se lanza cuando el usuario hace click en el botón de
         * minimizar visible.
         *
         * @~english
         * TO TRANSLATE
         */
        void minimizedVisibleFrame();
};

#endif // XWINDOW_H
