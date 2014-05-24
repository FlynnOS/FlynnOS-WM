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

bool TaskBar::ready_to_add = false;

TaskBar* TaskBar::getInstance()
{
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
    this->titlebar = new QLabel(this);
    this->clock_text = new QLabel(this);
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

    //mostramos la ventana de tasks
    this->show();

    //We connect the signals and start the timer for the clock
    connect(this->timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(1000);

    //We call the timer once, so the time is updated at start
    this->update();
}

bool TaskBar::isTaskWindow(Window w)
{
    QList<bar_item>::Iterator i = this->task_bar_list_.begin();
    while(i != this->task_bar_list_.end())
    {
        if ((*i).btn_->winId() == w || this->winId() == w)
        {
            return true;
        }
        i++;
    }
    return false;
}

void TaskBar::setFocus(XWindow* window)
{
    QList<bar_item>::Iterator i = this->task_bar_list_.begin();
    while(i != this->task_bar_list_.end())
    {
        if ((*i).win_ == window)
        {
            (*i).btn_->setAutoFillBackground(true);
            (*i).btn_->setObjectName("title_selected");
            (*i).btn_->setStyleSheet("text-align:left; background-color: rgb(255, 0, 0);");
        }
        else
        {
            (*i).btn_->setAutoFillBackground(true);
            (*i).btn_->setObjectName("title");
            (*i).btn_->setStyleSheet("text-align:left; background-color: #DCD9D7; color: rgb(76,76,76);");
        }
        i++;
    }
}

void TaskBar::clickTaskItem(Window w)
{
    QList<bar_item>::Iterator i = this->task_bar_list_.begin();
    while(i != this->task_bar_list_.end())
    {
        if ((*i).btn_->winId() == w)
        {
            //we show or iconify the window
            if ((*i).win_->getState() == IconicState)
            {
                (*i).win_->setState(NormalState);
                qDebug() << "\tModificando la lista del EWMH";
                this->wl->restackManagedWindow((*i).win_);

                qDebug() << "\tActualizando la ventana activa";
                this->wl->setActiveWindow((*i).win_);

                setFocus((*i).win_);
            }
            else
            {
                if (wl->getTopWindow() != (*i).win_)
                {
                    this->wl->restackManagedWindow((*i).win_);
                    qDebug() << "\tModificando la lista del EWMH";
                    this->wl->restackManagedWindow((*i).win_);

                    qDebug() << "\tActualizando la ventana activa";
                    this->wl->setActiveWindow((*i).win_);

                    setFocus((*i).win_);
                }
                else
                {
                    (*i).win_->setState(IconicState);
                    setFocus(0);
                }
            }
        }
        i++;
    }
}

void TaskBar::AddTask(XWindow* window_bar_)
{
    QList<bar_item>::Iterator i = this->task_bar_list_.begin();
    while(i != this->task_bar_list_.end())
    {
        if ((*i).win_ == window_bar_)
        {
            (*i).btn_->setText((*i).win_->getTitle());
            UpdateTitles();
            return;
        }
        i++;
    }

    QPushButton* added_ = new QPushButton(this);
    added_->setObjectName("title");
    added_->setText(window_bar_->getTitle());
    added_->show();
    connect( added_, SIGNAL( clicked() ), this, SLOT(click_item()) );
    this->task_bar_list_.push_back(bar_item(window_bar_, added_));
    UpdateTitles();
    TaskBar::ready_to_add = true;
}

void TaskBar::RemoveTask(XWindow* window_bar_)
{

    QList<bar_item>::Iterator i = this->task_bar_list_.begin();
    while(i != this->task_bar_list_.end())
    {
        if ((*i).win_ == window_bar_)
        {
            (*i).btn_->deleteLater();
            this->task_bar_list_.erase(i);
            UpdateTitles();
            return;
        }
        i++;
    }
}

void TaskBar::UpdateTitles()
{
    QList<bar_item>::Iterator i = this->task_bar_list_.begin();
    int x = 0;
    while(i != this->task_bar_list_.end())
    {
        int pixelWidth = (*i).btn_->fontMetrics().width((*i).btn_->text()) + 10;
        (*i).btn_->resize(pixelWidth,18);
        (*i).btn_->move(x,0);
        x += pixelWidth;
        i++;
    }
    UpdateTitlesSizes();
}

void TaskBar::UpdateTitlesSizes()
{
    QList<bar_item>::Iterator i = this->task_bar_list_.begin();
    float x = 0;
    int clock_text_width = clock_text->fontMetrics().width(clock_text->text()) + 20;
    float task_w = 100;
    //revisamos que el tamaño no sea mayor al de el ancho de la pantalla
    if ((this->task_bar_list_.size()) * task_w > QApplication::desktop()->width()-clock_text_width)
    {
        //Todas mis ventanas sumadas no caben en la parte de abajo, tengo que cambiarles el tamaño
        float max_size = QApplication::desktop()->width()-clock_text_width;
        task_w = max_size/(float)this->task_bar_list_.size();
    }
    while(i != this->task_bar_list_.end())
    {
        (*i).btn_->resize(task_w,18);
        (*i).btn_->move(x,0);
        x+=task_w;
        i++;
    }
}


TaskBar::~TaskBar()
{
    QList<bar_item>::Iterator i = this->task_bar_list_.begin();
    while(i != this->task_bar_list_.end())
    {
        delete (*i).btn_;
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

void TaskBar::click_item()
{
    clickTaskItem(((QPushButton*)QObject::sender())->winId());
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
