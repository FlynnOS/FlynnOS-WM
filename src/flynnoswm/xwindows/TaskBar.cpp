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
#include "TaskBar.h"
#include "src/flynnoswm/atoms/AtomList.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

TaskBar::TaskBar(QWidget* parent)
        : QWidget(parent)
{
    Config* cfg = Config::getInstance();
    AtomList* al = AtomList::getInstance();

    // Inicializamos los atributos
    this->titlebar          = new QLabel(this);
    this->clock_text             = new QLabel(this);
    this->timer = new QTimer(this);

    // Hacemos que las imágenes se ajusten a sus contenedores
    this->titlebar->setScaledContents(true);

    // Establecemos el nombre de los distintos elementos configurables desde el
    // archivo de configuración "style.qss"
    this->titlebar->setObjectName("titlebar");
    this->clock_text->setObjectName("title");

    // Aplicamos el estilo a la ventana
    this->setStyleSheet(cfg->getStyle());

    // Ajustamos el tamaño de los distintos elementos
    this->clock_text->resize(this->clock_text->width(), cfg->getTitlebarWidth()
            + cfg->getTopBorderWidth());
    //this->setVerticalAling(this->title, Config::TOP);

    //We setup the frame
    this->setWidth(QApplication::desktop()->width());
    this->setHeight(18);
    this->setY(QApplication::desktop()->height()-this->getHeight());


    //Le decimos al manejador de ventanas que somos un dock
    Atom dock = al->getAtom("_NET_WM_WINDOW_TYPE_DOCK");
    XChangeProperty(QX11Info::display(), winId(),  al->getAtom("_NET_WM_WINDOW_TYPE"),  al->getAtom("ATOM"), 32,  PropModeReplace, (unsigned char *)&dock,1);

    //Le decimos al manejador de ventanas el tamaño del dock
    unsigned long strut[12] = {0};
    strut[3] = this->getHeight();
    XChangeProperty(QX11Info::display(), winId(), al->getAtom("_NET_WM_STRUT_PARTIAL"), al->getAtom("CARDINAL"), 32, PropModeReplace, (unsigned char *)&strut, 12);

    //mostramos la ventana
    this->show();

    //We connect the signals and start the timer for the clock
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(1000);

    //We call the timer once, so the time is updated at start
    this->update();
}

TaskBar::~TaskBar()
{
    delete this->titlebar;
    delete this->clock_text;
    delete this->timer;
}

// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //


// ************************************************************************** //
// **********                        PUBLIC SLOTS                  ********** //
// ************************************************************************** //
void TaskBar::update()
{
    //qDebug("Clock update");
    QTime qtime = QTime::currentTime();
    QString stime = qtime.toString(Qt::LocalDate);
    stime = QString().sprintf("%02d",qtime.hour()) + " : " + QString().sprintf("%02d",qtime.minute()) + " : " + QString().sprintf("%02d",qtime.second());

    this->setClockText(stime);
    int pixelWidth = clock_text->fontMetrics().width(clock_text->text()) + 10;
    this->clock_text->move(QApplication::desktop()->width()-pixelWidth,this->clock_text->y());


}

// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

void TaskBar::setVisible(bool visible)
{
    QWidget::setVisible(visible);
}

int TaskBar::getX()
{
    return this->x();
}

int TaskBar::getY()
{
    return this->y();
}

void TaskBar::setX(int x)
{
    this->move(x, this->y());
}

void TaskBar::setY(int y)
{
    this->move(this->x(), y);
}

void TaskBar::setWidth(unsigned int width)
{
    this->resize(width, this->height());
}

void TaskBar::setHeight(unsigned int height)
{
    this->resize(this->width(), height);
}

unsigned int TaskBar::getWidth() const
{
    return this->width();
}

unsigned int TaskBar::getHeight() const
{
    return this->height();
}

void TaskBar::setClockText(const QString& title)
{
    this->clock_text->setText(title);
}
