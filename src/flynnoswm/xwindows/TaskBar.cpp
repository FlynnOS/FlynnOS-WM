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

TaskBar* TaskBar::instance = NULL;

TaskBar* TaskBar::getInstance() {
    if(TaskBar::instance == NULL)
        TaskBar::instance = new TaskBar();
    return TaskBar::instance;
}


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

void TaskBar::AddTask(XWindow* window_bar_)
{
    QMap<XWindow*, QPushButton*>::Iterator i = this->task_bar_list_.find(window_bar_);
    if (i != this->task_bar_list_.end())
    {
        i.value()->setText(i.key()->getTitle());
    }
    else
    {
        QPushButton* added_ = new QPushButton(this);
        added_->setObjectName("title");
        added_->setText(window_bar_->getTitle());
        added_->show();
        this->task_bar_list_.insert(window_bar_, added_);
    }

    UpdateTitles();
}

void TaskBar::RemoveTask(XWindow* window_bar_)
{
    QMap<XWindow*, QPushButton*>::Iterator i = this->task_bar_list_.find(window_bar_);
    if (i == this->task_bar_list_.end())
    {
        return;
    }
    i.value()->deleteLater();
    this->task_bar_list_.remove(window_bar_);
    UpdateTitles();
}

void TaskBar::UpdateTitles()
{
    QMap<XWindow*, QPushButton*>::Iterator i;
    i = this->task_bar_list_.begin();
    int x = 0;
    while(i != this->task_bar_list_.end())
    {
        int pixelWidth = i.value()->fontMetrics().width(i.value()->text()) + 10;
        i.value()->resize(pixelWidth,18);
        i.value()->move(x,0);
        x += pixelWidth;
        i++;
    }
}


TaskBar::~TaskBar()
{
    QMap<XWindow*, QPushButton*>::Iterator i;
    i = this->task_bar_list_.begin();
    while(i != this->task_bar_list_.end())
    {
        delete i.value();
        i++;
    }
    this->task_bar_list_.clear();

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
