/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class XWindowList
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "XWindowList.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

XWindowList::XWindowList() {
    this->clientHash   = new QHash<Window, const XWindow*>;
    this->frameHash    = new QHash<Window, const XWindow*>;
    this->mappingList  = new QList<const XWindow*>;
    this->stackingList = new QList<const XWindow*>;
    this->activeWindow = NULL;
}

XWindowList::~XWindowList() {
    delete this->clientHash;
    delete this->frameHash;
    delete this->mappingList;
    delete this->stackingList;
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

void XWindowList::restackWindows() const {
    int numWindows = this->stackingList->size();
    Window windows[numWindows];

    for(int n=numWindows-1; n>=0; n--) {
        const XWindow* aux = this->stackingList->at(n);
        windows[numWindows-1-n] = aux->haveFrame()
                ? aux->getFrameID()
                : aux->getClientID();
    }

    XRestackWindows(QX11Info::display(), windows, numWindows);
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

bool XWindowList::existClient(Window clientID) const {
    return this->clientHash->contains(clientID);
}

void XWindowList::addClient(Window clientID, const XWindow* xwindow) {
    this->clientHash->insert(clientID, xwindow);
}

void XWindowList::removeClient(Window clientID) {
    this->clientHash->remove(clientID);
}

XWindow* XWindowList::getXWindowByClientID(Window clientID) const {
    return (XWindow*)this->clientHash->value(clientID, NULL);
}

//------------------------------------------------------------------------------

bool XWindowList::existFrame(Window frameID) const {
    return this->frameHash->contains(frameID);
}

void XWindowList::addFrame(Window frameID, const XWindow* xwindow) {
    this->frameHash->insert(frameID, xwindow);
}

void XWindowList::removeFrame(Window frameID) {
    this->frameHash->remove(frameID);
}

XWindow* XWindowList::getXWindowByFrameID(Window frameID) const {
    return (XWindow*)this->frameHash->value(frameID, NULL);
}

//------------------------------------------------------------------------------

void XWindowList::addToManagedWindows(const XWindow* xwindow) {
    this->mappingList->removeOne(xwindow);
    this->mappingList->append(xwindow);

    this->restackManagedWindow(xwindow);

    EWMHRoot ewmhRoot;
    ewmhRoot.sendMappingClientList(this->mappingList);
    ewmhRoot.sendStackingClientList(this->stackingList);
}

void XWindowList::removeFromManagedWindow(const XWindow* xwindow) {
    this->mappingList->removeOne(xwindow);
    this->stackingList->removeOne(xwindow);

    EWMHRoot ewmhRoot;
    ewmhRoot.sendMappingClientList(this->mappingList);
    ewmhRoot.sendStackingClientList(this->stackingList);
}

void XWindowList::restackManagedWindow(const XWindow* xwindow) {
    this->stackingList->removeOne(xwindow);
    int numWindows = this->stackingList->size();

    // Ventanas que siempre están arriba
    if(xwindow->isTopWindow()) {
        this->stackingList->append(xwindow);

    // Ventanas que siempre están abajo
    } else if(xwindow->isBottomWindow()) {
        this->stackingList->prepend(xwindow);

    // Resto de ventanas
    } else {
        int  pos = numWindows - 1;
        bool end = false;

        while(pos >= 0 && !end) {
            const XWindow* aux = this->stackingList->at(pos);

            if(aux->isTopWindow())
                pos--;
            else
                end = true;
        }

        this->stackingList->insert(pos+1, xwindow);
    }

    this->restackWindows();

    EWMHRoot ewmhRoot;
    ewmhRoot.sendStackingClientList(this->stackingList);
}

void XWindowList::updateWorkarea()
{
    AtomList* al = AtomList::getInstance();
    //Variables need by XGetWindowProperty
    Atom rt;
    int rf;
    unsigned long nir, bar;
    long workarea[16], *data;
    int ewmh_strut[4];
    unsigned char *p;

    //we start the variables
    for(int j = 0; j < 4; j++)
        ewmh_strut[j] = 0;

    const XWindow* window_loop;
    foreach( window_loop, clientHash->values() )
    {
        if(XGetWindowProperty(QX11Info::display(), window_loop->getClientID(), al->getAtom("_NET_WM_STRUT_PARTIAL"), 0, 4, False, XA_CARDINAL, &rt, &rf, &nir, &bar, (unsigned char **) &p) != Success || nir < 4)
        {
            if(XGetWindowProperty(QX11Info::display(), window_loop->getClientID(), al->getAtom("_NET_WM_STRUT"), 0, 4, False, XA_CARDINAL, &rt, &rf, &nir, &bar, (unsigned char **) &p) != Success || nir < 4)
            {
                continue;
            }
        }

        data = (long *) p;
        if(data[0])
        ewmh_strut[0] += data[0];// - (screens_leftmost() + screens[clients[i]->screen].x);
        if(data[1])
        ewmh_strut[1] += data[1];// - (screens_rightmost() - (screens[clients[i]->screen].x + screens[clients[i]->screen].width));
        if(data[2])
        ewmh_strut[2] += data[2];// - (screens_topmost() + screens[clients[i]->screen].y);
        if(data[3])
        ewmh_strut[3] += data[3];// - (screens_bottom() - (screens[clients[i]->screen].y + screens[clients[i]->screen].height));
        XFree((void *) p);
    }

    //qDebug() << ewmh_strut[0] << " " << ewmh_strut[1] << " " << ewmh_strut[2] << " " << ewmh_strut[3] << " ";

    workarea[0] = /*screens[scr].x*/ 0 + ewmh_strut[0];
    workarea[1] = /*screens[scr].x*/ 0 + ewmh_strut[2];
    workarea[2] = (QApplication::desktop()->width() - 0 /*screens[scr].x*/)  - (ewmh_strut[0] + ewmh_strut[1]);
    workarea[3] = (QApplication::desktop()->height() - 0 /*screens[scr].y*/) - (ewmh_strut[2] + ewmh_strut[3]);
    workarea[4] = workarea[0]; // why 4 times? ask gnome developpers, this is the only way nautilus will listen to it
    workarea[5] = workarea[1];
    workarea[6] = workarea[2];
    workarea[7] = workarea[3];
    workarea[8] = workarea[0];
    workarea[9] = workarea[1];
    workarea[10] = workarea[2];
    workarea[11] = workarea[3];
    workarea[12] = workarea[0];
    workarea[13] = workarea[1];
    workarea[14] = workarea[2];
    workarea[15] = workarea[3];
    XChangeProperty(QX11Info::display(), QX11Info::appRootWindow(QX11Info::appScreen()), al->getAtom("_NET_WORKAREA"), XA_CARDINAL, 32, PropModeReplace, (unsigned char *) &workarea, sizeof(workarea) / sizeof(long));
    //qDebug() << "Workarea: " << workarea[0] << " " << workarea[1] << " " << workarea[2] << " " << workarea[3] << " ";

    //we change the size of all maximized windows
    foreach( window_loop, clientHash->values() )
    {
        XWindow* xwindow = (XWindow*)window_loop;
        xwindow->updateMaximizedWindow();
    }
}

void XWindowList::setActiveWindow(const XWindow* activeWindow)
{
    this->activeWindow = (XWindow*)activeWindow;

    // TODO Si se quiere cambiar la decoración de la ventana activa este es el
    //      sitio ;)

    EWMHRoot ewmhRoot;
    if(this->activeWindow == NULL)
    {
        ewmhRoot.sendActiveWindow(None);
    }
    else
    {
        ewmhRoot.sendActiveWindow(this->activeWindow->getClientID());
        this->activeWindow->setFocus();
    }
}

const XWindow* XWindowList::getTopWindow() const {
    const XWindow* ret = NULL;
    int pos = this->stackingList->size() - 1;

    while(pos >= 0 && ret == NULL) {
        const XWindow* aux = this->stackingList->at(pos);

        if(!aux->isTopWindow() && !aux->isBottomWindow()
                && aux->getState() != IconicState)
            ret = aux;
        pos--;
    }

    return ret;
}
