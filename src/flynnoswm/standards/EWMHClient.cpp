/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  EWMHClient
 * @authors José Expósito, Vicente Benavent
 *
 */
#include "EWMHClient.h"

// ************************************************************************** //
// **********              CONSTRUCTORS AND DESTRUCTOR             ********** //
// ************************************************************************** //

EWMHClient::EWMHClient(const Window& clientID) {
    this->clientID = clientID;
    this->al       = AtomList::getInstance();
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

bool EWMHClient::getProperty(Atom property, Atom propertyType,
        unsigned char** propRet) const {
    unsigned long numItems;
    return this->getProperty(property, propertyType, propRet, &numItems);
}

bool EWMHClient::getProperty(Atom property, Atom propertyType,
        unsigned char** propRet, unsigned long* numItems) const {
    return this->getProperty(property, propertyType, propRet, numItems, 0, 100);
}

bool EWMHClient::getProperty(Atom property, Atom propertyType,
        unsigned char** propRet, unsigned long* numItems, long offset,
        long lenght) const {
    Atom atomRet;
    int size;
    unsigned long bytesAfterReturn;

    int ret = XGetWindowProperty(QX11Info::display(), this->clientID, property,
            offset, lenght, false, propertyType, &atomRet, &size, numItems,
            &bytesAfterReturn, propRet);

    return (ret == Success && *numItems >= 1);
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //

QString EWMHClient::getTitle() const {
    unsigned char* propRet;

    if(this->getProperty(al->getAtom("_NET_WM_NAME"),
            al->getAtom("UTF8_STRING"), &propRet)) {
        QString title = QString::fromUtf8((char*) propRet);
        XFree(propRet);
        return title;
    } else if(this->getProperty(al->getAtom("WM_NAME"),
                                al->getAtom("UTF8_STRING"), &propRet))
    {
        QString title = QString::fromUtf8((char*) propRet);
        XFree(propRet);
        return title;
    }
    else
        return "";
}

QString EWMHClient::getVisibleTitle() const {
    unsigned char* propRet;

    if(this->getProperty(al->getAtom("_NET_WM_VISIBLE_NAME"),
            al->getAtom("UTF8_STRING"), &propRet)) {
        QString title = QString::fromUtf8((char*) propRet);
        XFree(propRet);
        return title;
    } else
        return "";
}

//------------------------------------------------------------------------------

Atom EWMHClient::getWindowType() const {
    unsigned char *propRet;

    if(this->getProperty(al->getAtom("_NET_WM_WINDOW_TYPE"), XA_ATOM,
            &propRet)) {
        Atom* types = (Atom*)propRet;
        Atom ret = types[0]; // Solo miramos el primer tipo especificado
        XFree(propRet);
        return ret;
    } else
        return al->getAtom("_NET_WM_WINDOW_TYPE_NORMAL");
}

QList<Atom> EWMHClient::getWindowState() const {
    unsigned char* propRet;
    QList<Atom> atom_list;

    if(this->getProperty(al->getAtom("_NET_WM_STATE"), XA_ATOM, &propRet))
    {
        Atom* types = (Atom*)propRet;
        for (int i = 0; i < sizeof(types)/sizeof(Atom); i++)
        {
            atom_list.append(types[i]);
        }
        XFree(propRet);
        return atom_list;
    }
    return atom_list;
}

//------------------------------------------------------------------------------

QPixmap EWMHClient::getIconPixmap() const {
    unsigned char* propRet;
    unsigned long numItems;
    int iconWidth;
    int iconHeight;
    QPixmap icon = NULL;

    // Ancho
    if(this->getProperty(al->getAtom("_NET_WM_ICON"), XA_CARDINAL, &propRet,
            &numItems, 0, 1)) {
        iconWidth = propRet[0];
        XFree(propRet);
    } else
        return NULL;

    // Alto
    if(this->getProperty(al->getAtom("_NET_WM_ICON"), XA_CARDINAL, &propRet,
            &numItems, 1, 1)) {
        iconHeight = propRet[0];
        XFree(propRet);
    } else
        return NULL;

    // Icono
    int i;
    ulong n;
    ulong* data;
    //obtenemos el icono
    XGetWindowProperty(QX11Info::display(),clientID,al->getAtom("_NET_WM_ICON"),0,LONG_MAX,False,AnyPropertyType,&n,&i,&n,&n,(uchar**)&data);
    if(data)
    {
        //creamos la imagen y compiamso los datos
        QImage image( data[0], data[1], QImage::Format_ARGB32);
        //la imagen esta desfasada, la movemos para que quede bien
        for(int i=0; i<image.byteCount()/4; ++i)
        {
            ((uint*)image.bits())[i] = data[i+2];
        }

        //creamos el pixmap
        icon = QPixmap::fromImage(image);
        XFree(data);
        return icon;
    }
    else
    {
        XFree(data);
        return NULL;
    }
}
