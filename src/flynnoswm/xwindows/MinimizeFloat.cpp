/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class MinimizeFloat
 * @authors Vicente Benavent
 *
 */
#include "MinimizeFloat.h"
#include <QMenu>
#include <src/flynnoswm/events/factory/EventFactory.h>
// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //


// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MinimizeFloat::MinimizeFloat(XWindow* window, QWidget* parent)
        : QLabel(parent)
{
    this->window = window;

    //We get the window "image" and set it
    windowPixmap = QPixmap::grabWindow(this->window->getFrameID(), 0, 0, this->window->getWidth(), this->window->getHeight());
    setPixmap(windowPixmap.scaled(this->window->getWidth()/4, this->window->getHeight()/4, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    //We move the window to the position
    move(this->window->getX(), this->window->getY());
    show();
    setFrameStyle(QFrame::Box | QFrame::Raised);

    //The line width, we use it to focus / unfocus the window
    setLineWidth(2);

    //We call the destructor after deleting the widget
    this->setAttribute(Qt::WA_DeleteOnClose);

    //minimizamos la ventana, dejamos este widget visible solamente
    this->window->minimizedFrame();
    EventFactory::getInstance()->windowList_->floatWindowHash.push_back(this);
}

MinimizeFloat::~MinimizeFloat()
{
    //qDebug() << "Memory Freed!";
    QList<MinimizeFloat*>::Iterator i;
    i = EventFactory::getInstance()->windowList_->floatWindowHash.begin();
    while(i != EventFactory::getInstance()->windowList_->floatWindowHash.end())
    {
        if ((*i) == this)
        {
            break;
        }
        i++;
    }
    EventFactory::getInstance()->windowList_->floatWindowHash.erase(i);
}

// ************************************************************************** //
// **********                  PROTECTED METHODS                   ********** //
// ************************************************************************** //

void MinimizeFloat::closeWindow()
{
    close();
    deleteLater();
}

void MinimizeFloat::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        window->setState(1);
        closeWindow();
    }
}

void MinimizeFloat::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //guardamos la posicion y cambiamos el cursor
        mousePos = event->pos();
        grabMouse(QCursor(Qt::SizeAllCursor));
    }
    if (event->button() == Qt::RightButton)
    {
        //creamos el menu y lo conectamos
        //TODO free mem? parece que no lo hacemos
        QMenu *menu = new QMenu(this);
        menu->addAction(tr("Close this window"));
        menu->addAction(tr("Open this window"));
        menu->popup(event->globalPos());
        connect(menu, SIGNAL(triggered(QAction *)), this, SLOT(menuClick(QAction *)));
    }
}

void MinimizeFloat::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setLineWidth(3);
}

void MinimizeFloat::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setLineWidth(2);
}

void MinimizeFloat::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->globalPos()-mousePos;
    move(p.x(), p.y());
}

void MinimizeFloat::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    releaseMouse();
}

// ************************************************************************** //
// **********                        PUBLIC SLOTS                  ********** //
// ************************************************************************** //
void MinimizeFloat::menuClick(QAction *act)
{
    if (act->text() == tr("Close this window"))
    {
        //emit destroy_deskicon(this);
        //frm->destroy_it();
        window->closedFrame();
        closeWindow();
    }
    else if (act->text() == tr("Open this window"))
    {
        window->setState(1);
        closeWindow();
    }

}

// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

void MinimizeFloat::setVisible(bool visible)
{
    QLabel::QWidget::setVisible(visible);
}

int MinimizeFloat::getX()
{
    return this->x();
}

int MinimizeFloat::getY()
{
    return this->y();
}

void MinimizeFloat::setX(int x)
{
    this->move(x, this->y());
}

void MinimizeFloat::setY(int y)
{
    this->move(this->x(), y);
}

void MinimizeFloat::setWidth(unsigned int width)
{
    this->resize(width, this->height());
}

void MinimizeFloat::setHeight(unsigned int height)
{
    this->resize(this->width(), height);
}

unsigned int MinimizeFloat::getWidth() const
{
    return this->width();
}

unsigned int MinimizeFloat::getHeight() const
{
    return this->height();
}
