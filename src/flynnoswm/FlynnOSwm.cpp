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
    //qDebug()  << "Error handled!";
    return 0;
}

FlynnOSwm::FlynnOSwm(int argc, char** argv) : QApplication(argc, argv)
{
    // Inicializamos los atributos
    this->wmCheckWindow = new WMCheckWindow;
    this->windowList    = new XWindowList;
    this->eventFactory  = EventFactory::getInstance();
    this->eventFactory->initialize(this->windowList);

    // cargamos la configuración
    Config* cfg = Config::getInstance();
    cfg->loadConfig();
    // TODO Añadir a la lista de ventanas las ventanas que ya existan

    // Establecemos diversas propiedades requeridas por el estándar EWMH
    this->sendHints();

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
            | ButtonPressMask);        /* ButtonPress */
    XFlush(QX11Info::display());

    //Adding a button test by Zaxuhe
    QWidget *window = new QWidget;
    QPushButton *button1 = new QPushButton("Close Window Manager");
    button1->show();
    connect(button1, SIGNAL(clicked()),this, SLOT(closeWindowManager()));

    QPushButton *button2 = new QPushButton("Launch terminator");
    QRect rect = button2->geometry();
    button2->move(QApplication::desktop()->width()-110, 0);
    button2->show();
    connect(button2, SIGNAL(clicked()),this, SLOT(launchTerminal()));

}

void FlynnOSwm::closeWindowManager()
{
    qDebug() << "We are closing the window manager" ;
    exit(0);
}

void FlynnOSwm::launchTerminal()
{
    std::system("terminator &");
}

FlynnOSwm::~FlynnOSwm()
{
    delete this->wmCheckWindow;
    delete this->windowList;
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
