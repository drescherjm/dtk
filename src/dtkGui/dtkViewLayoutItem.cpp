/* dtkViewLayoutItem.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:45 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:38:48 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkViewLayout.h"
#include "dtkViewLayoutItem.h"

#include <QtGui>

typedef QList<dtkViewLayoutItem *> dtkViewLayoutItemList;

class dtkViewLayoutItemPrivate
{
public:
    void split(void);

public:
    dtkViewLayoutItem *root;
    dtkViewLayoutItem *parent;

public:
    dtkViewLayoutItem *a;
    dtkViewLayoutItem *b;

public:
    QLabel *proxy;
    QWidget *view;

public:
    QSplitter *splitter;

public:
    QPushButton *close;
    QPushButton *horzt;
    QPushButton *vertc;

public:
    QFrame *footer;

public:
    dtkViewLayoutItem *q;
};

void dtkViewLayoutItemPrivate::split(void)
{
    if(this->a && this->b)
        return;

    this->proxy->hide();

    if(!this->a)
        this->a = new dtkViewLayoutItem(q);

    if(!this->b)
        this->b = new dtkViewLayoutItem(q);

    this->splitter->addWidget(a);
    this->splitter->addWidget(b);

    q->setCurrent(NULL);
}

dtkViewLayoutItem::dtkViewLayoutItem(dtkViewLayoutItem *parent) : QFrame(parent), d(new dtkViewLayoutItemPrivate)
{
    d->parent = parent;

    if(!d->parent)
        d->root = this;
    else
        d->root = d->parent->d->root;

    d->a = NULL;
    d->b = NULL;
    d->q = this;

    d->view = NULL;

    d->proxy = new QLabel("Drop a view here", this);
    d->proxy->setAlignment(Qt::AlignCenter);
    d->proxy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    d->proxy->setStyleSheet("background: #aaaaaa; color: #dddddd;");

    d->splitter = new QSplitter(this);
    d->splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    d->splitter->addWidget(d->proxy);

    d->horzt = new QPushButton("Horzt", this);
    d->vertc = new QPushButton("Vertc", this);
    d->close = new QPushButton("Close", this);
    d->close->setEnabled(d->root != this);

    QHBoxLayout *footer_layout = new QHBoxLayout;
    footer_layout->addWidget(d->close);
    footer_layout->addWidget(d->horzt);
    footer_layout->addWidget(d->vertc);

    d->footer = new QFrame(this);
    d->footer->setLayout(footer_layout);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->splitter);
    layout->addWidget(d->footer);

    this->setAcceptDrops(true);
    this->setFocusPolicy(Qt::StrongFocus);

    connect(d->close, SIGNAL(clicked()), this, SLOT(close()));
    connect(d->horzt, SIGNAL(clicked()), this, SLOT(horzt()));
    connect(d->vertc, SIGNAL(clicked()), this, SLOT(vertc()));
}

dtkViewLayoutItem::~dtkViewLayoutItem(void)
{
    qDebug() << __func__;

    delete d;

    d = NULL;
}

void dtkViewLayoutItem::setCurrent(dtkViewLayoutItem *item)
{
    if(item == this)
        d->footer->setStyleSheet(".QFrame { background: blue; }");
    else
        d->footer->setStyleSheet(".QFrame { background: none; }");

    if (d->a)
        d->a->setCurrent(item);

    if (d->b)
        d->b->setCurrent(item);

    this->update();
}

void dtkViewLayoutItem::remove(dtkViewLayoutItem *item)
{
    if(item == d->a) {
        delete d->a;
        d->a = NULL;
    }

    if(item == d->b) {
        delete d->b;
        d->b = NULL;
    }

    if(!d->a && !d->b)
        d->proxy->show();

    d->close->setEnabled(d->root != this);
}

void dtkViewLayoutItem::focusInEvent(QFocusEvent *)
{
    if(d->a || d->b)
        return;

    d->root->setCurrent(this);
}

void dtkViewLayoutItem::focusOutEvent(QFocusEvent *)
{

}

void dtkViewLayoutItem::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void dtkViewLayoutItem::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void dtkViewLayoutItem::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void dtkViewLayoutItem::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event);

    if(d->a && d->b)
        return;

    d->proxy->hide();

    // dtkAbstractViewFactory::instance()->create();

    d->view = new QFrame(this);
    d->view->setStyleSheet("background: black;");

    // --

    d->splitter->addWidget(d->view);

    d->close->setEnabled(true);
    d->horzt->setEnabled(false);
    d->vertc->setEnabled(false);
}

void dtkViewLayoutItem::close(void)
{
    if (d->view) {
        d->view->hide();
        d->view = NULL;
        d->proxy->show();
        d->horzt->setEnabled(true);
        d->vertc->setEnabled(true);
        return;
    }

    if(!d->parent)
        return;

    d->parent->remove(this);
}

void dtkViewLayoutItem::horzt(void)
{
    d->splitter->setOrientation(Qt::Horizontal);

    d->split();
}

void dtkViewLayoutItem::vertc(void)
{
    d->splitter->setOrientation(Qt::Vertical);

    d->split();
}
