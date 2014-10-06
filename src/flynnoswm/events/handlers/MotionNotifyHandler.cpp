/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  MotionNotifyHandler
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "MotionNotifyHandler.h"
#include "src/flynnoswm/standards/Defines.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

MotionNotifyHandler::MotionNotifyHandler(XWindowList* wl)
        : EventHandler(wl) {}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool MotionNotifyHandler::processEvent(XEvent* event)
{

    //SUPPORT FOR _NET_WM_MOVERESIZE
    if (this->wl->moveResizeWindow != 0)
    {
        if (this->wl->moveResizeAction == _NET_WM_MOVERESIZE_MOVE)
        {
            //move window
            int diffx = this->wl->moveResizeStartX-this->wl->moveResizeWindow->getX();
            int diffy = this->wl->moveResizeStartY-this->wl->moveResizeWindow->getY();
            this->wl->moveResizeWindow->setX(event->xmotion.x_root-diffx);
            this->wl->moveResizeWindow->setY(event->xmotion.y_root-diffy);
            this->wl->moveResizeStartX = event->xmotion.x_root;
            this->wl->moveResizeStartY = event->xmotion.y_root;
        }
        else if (this->wl->moveResizeAction == _NET_WM_MOVERESIZE_SIZE_RIGHT) //Resize right window
        {
            int finalw = event->xmotion.x_root-this->wl->moveResizeWindow->getX();
            if (finalw < this->wl->moveResizeWindow->getClient()->getMinWidth())
            {
                finalw = this->wl->moveResizeWindow->getClient()->getMinWidth();
            }

            this->wl->moveResizeWindow->setWidth(finalw);
        }
        else if (this->wl->moveResizeAction == _NET_WM_MOVERESIZE_SIZE_LEFT) //Resize left window
        {
            int diffx = this->wl->moveResizeWindow->getX()-event->xmotion.x_root;
            int finalw = this->wl->moveResizeWindow->getWidth()+diffx;
            if (finalw >= this->wl->moveResizeWindow->getClient()->getMinWidth())
            {
                this->wl->moveResizeWindow->setX(event->xmotion.x_root);
                this->wl->moveResizeWindow->setWidth(finalw);
            }

        }
        else if (this->wl->moveResizeAction == _NET_WM_MOVERESIZE_SIZE_BOTTOMLEFT) //Resize bottom/left window
        {
            int diffx = this->wl->moveResizeWindow->getX()-event->xmotion.x_root;
            int finalw = this->wl->moveResizeWindow->getWidth()+diffx;
            if (finalw >= this->wl->moveResizeWindow->getClient()->getMinWidth())
            {
                this->wl->moveResizeWindow->setX(event->xmotion.x_root);
                this->wl->moveResizeWindow->setWidth(finalw);
            }

            int finalh = event->xmotion.y_root-this->wl->moveResizeWindow->getY();
            if (finalh < this->wl->moveResizeWindow->getClient()->getMinHeight())
            {
                finalh = this->wl->moveResizeWindow->getClient()->getMinHeight();
            }

            this->wl->moveResizeWindow->setHeight(finalh);

        }
        else if (this->wl->moveResizeAction == _NET_WM_MOVERESIZE_SIZE_TOPLEFT) //Resize top/left window
        {
            int diffy = this->wl->moveResizeWindow->getY()-event->xmotion.y_root;
            int finalh = this->wl->moveResizeWindow->getHeight()+diffy;
            if (finalh >= this->wl->moveResizeWindow->getClient()->getMinHeight())
            {
                this->wl->moveResizeWindow->setY(event->xmotion.y_root);
                this->wl->moveResizeWindow->setHeight(finalh);
            }


            int diffx = this->wl->moveResizeWindow->getX()-event->xmotion.x_root;
            int finalw = this->wl->moveResizeWindow->getWidth()+diffx;
            if (finalw >= this->wl->moveResizeWindow->getClient()->getMinWidth())
            {
                this->wl->moveResizeWindow->setX(event->xmotion.x_root);
                this->wl->moveResizeWindow->setWidth(finalw);
            }
        }
        else if (this->wl->moveResizeAction == _NET_WM_MOVERESIZE_SIZE_TOP) //Resize top window
        {
            int diffy = this->wl->moveResizeWindow->getY()-event->xmotion.y_root;
            int finalh = this->wl->moveResizeWindow->getHeight()+diffy;
            if (finalh >= this->wl->moveResizeWindow->getClient()->getMinHeight())
            {
                this->wl->moveResizeWindow->setY(event->xmotion.y_root);
                this->wl->moveResizeWindow->setHeight(finalh);
            }

        }
        else if (this->wl->moveResizeAction == _NET_WM_MOVERESIZE_SIZE_TOPRIGHT) //Resize top/right window
        {
            int diffy = this->wl->moveResizeWindow->getY()-event->xmotion.y_root;
            int finalh = this->wl->moveResizeWindow->getHeight()+diffy;
            if (finalh >= this->wl->moveResizeWindow->getClient()->getMinHeight())
            {
                this->wl->moveResizeWindow->setY(event->xmotion.y_root);
                this->wl->moveResizeWindow->setHeight(finalh);
            }

            int finalw = event->xmotion.x_root-this->wl->moveResizeWindow->getX();
            if (finalw < this->wl->moveResizeWindow->getClient()->getMinWidth())
            {
                finalw = this->wl->moveResizeWindow->getClient()->getMinWidth();
            }

            this->wl->moveResizeWindow->setWidth(finalw);

        }
        else if (this->wl->moveResizeAction == _NET_WM_MOVERESIZE_SIZE_BOTTOM) //Resize right window
        {
            int finalh = event->xmotion.y_root-this->wl->moveResizeWindow->getY();
            if (finalh < this->wl->moveResizeWindow->getClient()->getMinHeight())
            {
                finalh = this->wl->moveResizeWindow->getClient()->getMinHeight();
            }

            this->wl->moveResizeWindow->setHeight(finalh);
        }
        else if (this->wl->moveResizeAction == _NET_WM_MOVERESIZE_SIZE_BOTTOMRIGHT) //Resize right-bottom window
        {

            int finalw = event->xmotion.x_root-this->wl->moveResizeWindow->getX();
            if (finalw < this->wl->moveResizeWindow->getClient()->getMinWidth())
            {
                finalw = this->wl->moveResizeWindow->getClient()->getMinWidth();
            }

            this->wl->moveResizeWindow->setWidth(finalw);

            int finalh = event->xmotion.y_root-this->wl->moveResizeWindow->getY();
            if (finalh < this->wl->moveResizeWindow->getClient()->getMinHeight())
            {
                finalh = this->wl->moveResizeWindow->getClient()->getMinHeight();
            }

            this->wl->moveResizeWindow->setHeight(finalh);
        }
    }

    return false;
}
