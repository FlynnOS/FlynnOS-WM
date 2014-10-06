/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class FlynnOSwm
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "FlynnOSwm.h"
#include "config/SystemKeys.h"
#include "xwindows/Background.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

//If this is called it means that there was an error starting the window manager
int xerror_at_start(Display *dpy, XErrorEvent *ee)
{
	qDebug()  << "FlynnOSwm: another window manager is already running";
    exit(-1);
}

//General error handler
int error_handler(Display *dpy, XErrorEvent *ee)
{

    /*char err[64], req[64], min[64];;

    XGetErrorText( dpy, ee->error_code, err, 64 );
    XGetErrorText( dpy, ee->request_code, req, 64 );
    XGetErrorText( dpy, ee->minor_code, min, 64 );

    qDebug() << err;
    qDebug() << req;
    qDebug() << min;*/
    return 0;

}

FlynnOSwm::FlynnOSwm(int& argc, char **argv[]) : QApplication(argc, *argv)
{
    TaskBar::setRaw(0);
    TaskBar::ready_to_add = false;
    // Inicializamos los atributos
    this->wmCheckWindow = new WMCheckWindow;
    this->windowList    = new XWindowList;
    this->eventFactory  = EventFactory::getInstance();
    this->eventFactory->initialize(this->windowList);

    // cargamos la configuración
     qDebug() << "pre1" ;
    Config* cfg = Config::getInstance();
    cfg->loadConfig();
    qDebug() << "pre2" ;
    // TODO Añadir a la lista de ventanas las ventanas que ya existan

    // Establecemos diversas propiedades requeridas por el estándar EWMH
    this->sendHints();
    qDebug() << "pre3" ;

    //we check that another window manager is not running
    XSetErrorHandler(xerror_at_start);
    // this causes an error if some other window manager is running
    XSelectInput(QX11Info::display(), QX11Info::appRootWindow(QX11Info::appScreen()), SubstructureRedirectMask);
    XSetErrorHandler(error_handler);

    // Establecemos que eventos queremos recibir
    XSelectInput(QX11Info::display(),
            QX11Info::appRootWindow(QX11Info::appScreen()),
              SubstructureRedirectMask /* MapRequest, ConfigureRequest,
                                          CirculateRequest */
            | SubstructureNotifyMask   /* CreateNotify, DestroyNotify,
                                          MapNotify, UnmapNotify,
                                          ReparentNotify, GravityNotify,
                                          ConfigureNotify, CirculateNotify */
            | ButtonPressMask
            );        /* ButtonPress */
    XFlush(QX11Info::display());

    Background::getInstance();

    TaskBar::getInstance()->wl = this->windowList;

    qDebug() << "pre5" ;
    SystemKeys::getInstance()->configureSystemKeys();
    qDebug() << "pre4" ;
}

FlynnOSwm::~FlynnOSwm()
{
    delete this->wmCheckWindow;
    delete this->windowList;
    //delete this->taskBar;
}

// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

void FlynnOSwm::sendHints()
{
    EWMHRoot ewmhRoot;

    ewmhRoot.sendSupportedHints();
    ewmhRoot.sendActiveWindow(None);
    ewmhRoot.sendSupportingWmCheck(this->wmCheckWindow->winId());

    ewmhRoot.sendNumberOfDesktops(1.0);
    ewmhRoot.sendDesktopNames("FlynnOSwm Desktop");
    ewmhRoot.sendDesktopGeometry((long)QApplication::desktop()->width(),
            (long)QApplication::desktop()->height());
    ewmhRoot.sendDesktopViewport(0.0, 0.0);
    ewmhRoot.sendWorkarea(0.0, 0.0, (long)QApplication::desktop()->width(),
            (long)QApplication::desktop()->height());
    ewmhRoot.sendCurrentDesktop(0.0);
    ewmhRoot.sendSupportShowingdesktop(0.0);
}


// ************************************************************************** //
// **********                   PROTECTED METHODS                  ********** //
// ************************************************************************** //

bool FlynnOSwm::x11EventFilter(XEvent* event)
{
    EventHandler* handler = this->eventFactory->getEventHandler(event->type);

    if(handler != NULL)
        return handler->processEvent(event);
    else
        return false;
}
