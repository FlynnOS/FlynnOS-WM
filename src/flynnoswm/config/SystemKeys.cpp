/**
 * Copyright 2013 Vicente Benavent and other contributors
 * FlynnOSwm is based heavily on Eggwm. (http://code.google.com/p/eggwm/) revision 50 by José Expósito, copyright 2010-2011
 *
 * This file is part of the FlynnOSwm project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class SystemKeys
 * @authors Vicente Benavent
 *
 */
#include "SystemKeys.h"
#include <cstdlib>
#include "src/flynnoswm/events/factory/EventFactory.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

SystemKeys* SystemKeys::instance = NULL;

SystemKeys* SystemKeys::getInstance()
{
    if(SystemKeys::instance == NULL)
    {
        SystemKeys::instance = new SystemKeys();
    }
    return SystemKeys::instance;
}


// ************************************************************************** //
// **********                    PUBLIC METHODS                    ********** //
// ************************************************************************** //


void SystemKeys::configureSystemKeys()
{
    XUngrabKey(QX11Info::display(), AnyKey, AnyModifier, QX11Info::appRootWindow(QX11Info::appScreen()));
    createModifiers(QX11Info::display());
    //List of keys to add
    insertKey(XK_c,Mod1Mask|ControlMask,KEY_CLOSE_WINDOW);
    insertKey(XK_t,ControlMask,KEY_ALT_TAB);
    insertKey(XK_Return,Mod1Mask|ControlMask,KEY_OPEN_TERMINAL);


    //Don't edit below here
    for (std::map<unsigned int, std::map<unsigned int, key_events> >::iterator k =key_list.begin(); k!= key_list.end(); k++)
    {
        for (std::map<unsigned int, key_events>::iterator m = k->second.begin();m != k->second.end();m++)
        {
            //we transform the key to the value Xlib returns
            qDebug() << "Adding key to key list: " << k->first << ": " << m->first;
            addKey(k->first,m->first);
        }
    }

}

void SystemKeys::insertKey(unsigned int keycode, unsigned int mask, key_events _e)
{
    keycode = XKeysymToKeycode(QX11Info::display(), keycode);
    key_list[keycode][mask] = _e;
}

void SystemKeys::ProcessKey(unsigned int keycode, unsigned int mask)
{

    //Note: There must be a better way to do this
    //We keep only the masks we need
    unsigned int check_mask = 0;
    check_mask += (mask & (ShiftMask));
    check_mask += (mask & (ControlMask));
    check_mask += (mask & (Mod1Mask));

    std::map<unsigned int, std::map<unsigned int, key_events> >::iterator k = key_list.find(keycode);
    if (k != key_list.end())
    {
        std::map<unsigned int, key_events>::iterator m = k->second.find(check_mask);
        if (m != k->second.end())
        {
            //encontramos la tecla!
            //qDebug() << "Le dio click a una tecla que esta en la lista de las teclas de sistema";
            switch (m->second)
            {
                case KEY_CLOSE_WINDOW:
                    if (EventFactory::getInstance()->windowList_->getTopWindow() != 0 && ((XWindow*)(EventFactory::getInstance()->windowList_->getTopWindow()))->haveFrame())
                    {
                        ((XWindow*)(EventFactory::getInstance()->windowList_->getTopWindow()))->closedFrame();
                    }
                    break;
                case KEY_OPEN_TERMINAL:
                    std::system("terminator &");
                    break;
                case KEY_ALT_TAB:
                    //std::system("terminator &");
                    //EventFactory::getInstance()->windowList_->setActiveWindow();
                    EventFactory::getInstance()->windowList_->changeActiveStack();
                    break;
                default:
                    break;
            }
        }
    }
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

/*
 * This method locates key masks like scroll lock, number lock and caps lock
 * because X11 does not provide fixed constants for them.  Variables populated
 * are located above this comment.
 */
void SystemKeys::createModifiers(Display * display)
{
    int i;
    XModifierKeymap *modmap;
    KeyCode nlock, slock;
    static int mask_table[8] =
    {
        ShiftMask, LockMask, ControlMask, Mod1Mask, Mod2Mask, Mod3Mask, Mod4Mask, Mod5Mask
    };

    nlock = XKeysymToKeycode (display, XK_Num_Lock);
    slock = XKeysymToKeycode (display, XK_Scroll_Lock);

    //Find out the masks for the NumLock and ScrollLock modifiers, so that we
    //can bind the grabs for when they are enabled too.
    modmap = XGetModifierMapping (display);

    if (modmap != NULL && modmap->max_keypermod > 0)
    {
        for (i = 0; i < 8 * modmap->max_keypermod; i++)
        {
            if (modmap->modifiermap[i] == nlock && nlock != 0)
            {
                NumberLockMask = mask_table[i / modmap->max_keypermod];
            }
            else if (modmap->modifiermap[i] == slock && slock != 0)
            {
                ScrollLockMask = mask_table[i / modmap->max_keypermod];
            }
        }
    }

    CapsLockMask = LockMask;

    if (modmap)
    {
        XFreeModifiermap(modmap);
    }
}

void SystemKeys::addKey(int keycode, unsigned int mask)
{
    //Find the X11 KeyCode we are listening for.
    //KeyCode key = XKeysymToKeycode(QX11Info::display(), XK_p);

    //unsigned int mask = Mod1Mask;
    KeyCode key = keycode;

    //ShiftMask
    XGrabKey(QX11Info::display(), key, mask, QX11Info::appRootWindow(QX11Info::appScreen()), false, GrabModeAsync, GrabModeAsync);

    //NumberLockMask
    XGrabKey(QX11Info::display(), key, mask | NumberLockMask, QX11Info::appRootWindow(QX11Info::appScreen()), false, GrabModeAsync, GrabModeAsync);

    //ScrollLockMask
    XGrabKey(QX11Info::display(), key, mask | ScrollLockMask, QX11Info::appRootWindow(QX11Info::appScreen()), false, GrabModeAsync, GrabModeAsync);

    //CapsLockMask
    XGrabKey(QX11Info::display(), key, mask | CapsLockMask, QX11Info::appRootWindow(QX11Info::appScreen()), false, GrabModeAsync, GrabModeAsync);

    //NumberLockMask | ScrollLockMask
    XGrabKey(QX11Info::display(), key, mask | NumberLockMask | ScrollLockMask, QX11Info::appRootWindow(QX11Info::appScreen()), false, GrabModeAsync, GrabModeAsync);

    //NumberLockMask | CapsLockMask
    XGrabKey(QX11Info::display(), key, mask | NumberLockMask | CapsLockMask, QX11Info::appRootWindow(QX11Info::appScreen()), false, GrabModeAsync, GrabModeAsync);

    //ScrollLockMask | CapsLockMask
    XGrabKey(QX11Info::display(), key, mask | ScrollLockMask | CapsLockMask, QX11Info::appRootWindow(QX11Info::appScreen()), false, GrabModeAsync, GrabModeAsync);

    //NumberLockMask | ScrollLockMask | CapsLockMask
    XGrabKey(QX11Info::display(), key, mask | NumberLockMask | ScrollLockMask | CapsLockMask, QX11Info::appRootWindow(QX11Info::appScreen()), false, GrabModeAsync, GrabModeAsync);
}

// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //
