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
#include "Background.h"
#include "src/flynnoswm/atoms/AtomList.h"
#include "X11/extensions/XTest.h"
#include <QPainter>

//ugly hack to enable QStyleOption
#ifdef None
int v = None;
#undef None
#endif
#include <QStyleOption>
#define None v;



// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

Background* Background::instance = NULL;

Background* Background::getInstance()
{
    if(Background::instance == NULL)
        Background::instance = new Background();
    return Background::instance;
}


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

Background::Background(QWidget* parent)
        : QWidget(parent)
{
    Config* cfg = Config::getInstance();
    AtomList* al = AtomList::getInstance();


    // Inicializamos los atributos

    // Aplicamos el estilo a la ventana

    this->setObjectName("Background");

    //We setup the frame

    this->setWidth(QApplication::desktop()->width());
    this->setHeight(QApplication::desktop()->height());
    this->setX(0);
    this->setY(0);

    this->setStyleSheet(cfg->getStyle());


    QPushButton* added_ = new QPushButton(this);
    added_->setObjectName("exit_btn");
    added_->setText("Exit window manager");
    added_->show();
    connect(added_, SIGNAL(clicked()),this, SLOT(closeWindowManager()));

    QPushButton* btn2_ = new QPushButton(this);
    btn2_->setObjectName("term_btn");
    btn2_->setText("Open terminal");
    btn2_->move(QApplication::desktop()->width()-110, 0);
    btn2_->show();
    connect(btn2_, SIGNAL(clicked()),this, SLOT(launchTerminal()));



    //Le decimos al manejador de ventanas que somos desktop
    Atom dock = al->getAtom("_NET_WM_WINDOW_TYPE_DESKTOP");
    XChangeProperty(QX11Info::display(), winId(),  al->getAtom("_NET_WM_WINDOW_TYPE"),  al->getAtom("ATOM"), 32,  PropModeReplace, (unsigned char *)&dock,1);

    //mostramos el background
    this->show();


    //We connect the signals and start the timer for the clock
    this->timer =  new QTimer();
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(1000);

    //We call the timer once, so the time is updated at start
    this->update();

}


Background::~Background()
{
    delete this->timer;
}

// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //
void Background::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

// ************************************************************************** //
// **********                        PUBLIC SLOTS                  ********** //
// ************************************************************************** //
/*d
//this is going to be used on screen keyboard
// A full list of available codes can be found in /usr/include/X11/keysymdef.h
#define KEYCODE XK_a

// Function to create a keyboard event
XKeyEvent createKeyEvent(Display *display, Window &win,
                           Window &winRoot, bool press,
                           int keycode, int modifiers)
{
   XKeyEvent event;

   event.display     = display;
   event.window      = win;
   event.root        = winRoot;
   event.subwindow   = None;
   event.time        = CurrentTime;
   event.x           = 1;
   event.y           = 1;
   event.x_root      = 1;
   event.y_root      = 1;
   event.same_screen = True;
   event.keycode     = XKeysymToKeycode(display, keycode);
   event.state       = modifiers;

   if(press)
      event.type = KeyPress;
   else
      event.type = KeyRelease;

   return event;
}*/

void Background::update()
{
    return;

    /*Display *display = QX11Info::display();
    // Get the root window for the current display.
    Window winRoot = XDefaultRootWindow(display);

    // Find the window which has the current keyboard focus.
    Window winFocus;
    int    revert;
    XGetInputFocus(display, &winFocus, &revert);
    // Send a fake key press event to the window.
    XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, KEYCODE, 0);
    //XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
    XTestFakeKeyEvent(event.display, event.keycode, True, CurrentTime);
    qDebug() << "Fucking keys press";
    // Send a fake key release event to the window.
    event = createKeyEvent(display, winFocus, winRoot, false, KEYCODE, 0);
    //XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
    XTestFakeKeyEvent(event.display, event.keycode, True, CurrentTime);
    qDebug() << "Fucking keys release";*/

}

void Background::closeWindowManager()
{
    qDebug() << "We are closing the window manager" ;
    exit(0);
}

void Background::launchTerminal()
{
    std::system("terminator &");
}

// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

void Background::setVisible(bool visible)
{
    QWidget::setVisible(visible);
}

int Background::getX()
{
    return this->x();
}

int Background::getY()
{
    return this->y();
}

void Background::setX(int x)
{
    this->move(x, this->y());
}

void Background::setY(int y)
{
    this->move(this->x(), y);
}

void Background::setWidth(unsigned int width)
{
    this->resize(width, this->height());
}

void Background::setHeight(unsigned int height)
{
    this->resize(this->width(), height);
}

unsigned int Background::getWidth() const
{
    return this->width();
}

unsigned int Background::getHeight() const
{
    return this->height();
}
