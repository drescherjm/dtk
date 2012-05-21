/* dtkViewLayoutItem.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:45 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 22 00:39:02 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 399
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkViewLayout.h"
#include "dtkViewLayoutItem.h"

#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkViewLayoutItemProxyPrivate
// /////////////////////////////////////////////////////////////////

class dtkViewLayoutItemProxyPrivate
{
public:
    QVBoxLayout *layout;

public:
    dtkAbstractView *view;
};

// /////////////////////////////////////////////////////////////////
// dtkViewLayoutItemProxy
// /////////////////////////////////////////////////////////////////

dtkViewLayoutItemProxy::dtkViewLayoutItemProxy(QWidget *parent) : QFrame(parent), d(new dtkViewLayoutItemProxyPrivate)
{
    d->layout = new QVBoxLayout(this);
    d->layout->setContentsMargins(0, 0, 0, 0);

    d->view = NULL;

    this->setFocusPolicy(Qt::StrongFocus);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

dtkViewLayoutItemProxy::~dtkViewLayoutItemProxy(void)
{
    if (d->view)
        d->layout->removeWidget(d->view->widget());

    delete d;

    d = NULL;
}

dtkAbstractView *dtkViewLayoutItemProxy::view(void)
{
    return d->view;
}

void dtkViewLayoutItemProxy::setView(dtkAbstractView *view)
{
    if(!view)
        return;

    if(!view->widget())
        return;

    if(dtkViewLayoutItemProxy *proxy = dynamic_cast<dtkViewLayoutItemProxy *>(view->widget()->parentWidget())) {
        proxy->d->layout->removeWidget(view->widget());
        proxy->d->view = NULL;
    }

    if (d->view)
        d->layout->removeWidget(d->view->widget());

    d->view = view;
    d->layout->addWidget(d->view->widget());

    // qDebug() << __func__ << d->view->widget()->parentWidget()->metaObject()->className();
}

void dtkViewLayoutItemProxy::focusInEvent(QFocusEvent *event)
{
    QFrame::focusInEvent(event);

    emit focusedIn();
}

void dtkViewLayoutItemProxy::focusOutEvent(QFocusEvent *event)
{
    QFrame::focusOutEvent(event);

    emit focusedOut();
}

// /////////////////////////////////////////////////////////////////
// dtkViewLayoutItemPrivate
// /////////////////////////////////////////////////////////////////

class dtkViewLayoutItemPrivate
{
public:
    static dtkViewLayoutItemProxy *firstViewChild(dtkViewLayoutItem *item);

public:
    dtkViewLayoutItem *root;
    dtkViewLayoutItem *parent;

public:
    dtkViewLayoutItem *a;
    dtkViewLayoutItem *b;

public:
    dtkViewLayout *layout;

public:
    dtkViewLayoutItemProxy *proxy;

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

dtkViewLayoutItemProxy *dtkViewLayoutItemPrivate::firstViewChild(dtkViewLayoutItem *item)
{
    if(item->d->proxy)
        return item->d->proxy;

    if(item->d->a)
        return firstViewChild(item->d->a);

    if(item->d->b)
        return firstViewChild(item->d->b);

    return NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkViewLayoutItem
// /////////////////////////////////////////////////////////////////

dtkViewLayoutItem::dtkViewLayoutItem(dtkViewLayoutItem *parent) : QFrame(parent), d(new dtkViewLayoutItemPrivate)
{
    d->a = NULL;
    d->b = NULL;
    d->q = this;

    d->layout = NULL;

    if((d->parent = parent)) {
        d->root = d->parent->d->root;
        d->layout = d->parent->d->layout;
    } else {
        d->root = this;
    }

    d->proxy = new dtkViewLayoutItemProxy(this);

    d->splitter = new QSplitter(this);
    d->splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    d->splitter->addWidget(d->proxy);

    d->horzt = new QPushButton("Horzt", this);
    d->vertc = new QPushButton("Vertc", this);
    d->close = new QPushButton("Close", this);

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

    connect(d->close, SIGNAL(clicked()), this, SLOT(close()));
    connect(d->horzt, SIGNAL(clicked()), this, SLOT(horzt()));
    connect(d->vertc, SIGNAL(clicked()), this, SLOT(vertc()));

    connect(d->proxy, SIGNAL(focusedIn()), this, SLOT(onFocusedIn()));
    connect(d->proxy, SIGNAL(focusedOut()), this, SLOT(onFocusedOut()));

    d->proxy->setFocus(Qt::OtherFocusReason);
}

dtkViewLayoutItem::~dtkViewLayoutItem(void)
{
    delete d;

    d = NULL;
}

dtkViewLayoutItem *dtkViewLayoutItem::parent(void)
{
    return d->parent;
}

dtkViewLayout *dtkViewLayoutItem::layout(void)
{
    return d->layout;
}

dtkViewLayoutItemProxy *dtkViewLayoutItem::proxy(void)
{
    return d->proxy;
}

void dtkViewLayoutItem::setLayout(dtkViewLayout *layout)
{
    d->layout = layout;
}

void dtkViewLayoutItem::split(void)
{
    d->a = new dtkViewLayoutItem(this);
    d->b = new dtkViewLayoutItem(this);

    d->splitter->addWidget(d->a);
    d->splitter->addWidget(d->b);

    d->a->d->proxy->setFocus(Qt::OtherFocusReason);
    d->a->d->proxy->setView(d->proxy->view());

    disconnect(d->proxy, SIGNAL(focusedIn()), this, SLOT(onFocusedIn()));
    disconnect(d->proxy, SIGNAL(focusedOut()), this, SLOT(onFocusedOut()));

    delete d->proxy;

    d->proxy = NULL;

    d->footer->hide();
}

void dtkViewLayoutItem::unsplit(void)
{
    if(!d->a && !d->b)
        return;

    if(d->layout->current() == d->a) {

        delete d->a;

        d->a = NULL;

        if(d->b->d->a && d->b->d->b) {

            dtkViewLayoutItem *a = d->b->d->a; a->d->parent = this;
            dtkViewLayoutItem *b = d->b->d->b; b->d->parent = this;

            a->setParent(this);
            b->setParent(this);

            d->splitter->setOrientation(d->b->d->splitter->orientation());

            delete d->b;

            d->b = NULL;

            d->a = a;
            d->b = b;

            d->splitter->addWidget(d->a);
            d->splitter->addWidget(d->b);

            dtkViewLayoutItemProxy *child = NULL;

            if(!(child = dtkViewLayoutItemPrivate::firstViewChild(d->a)))
                 child = dtkViewLayoutItemPrivate::firstViewChild(d->b);

            if (child)
                child->setFocus(Qt::OtherFocusReason);

        } else {

            d->proxy = new dtkViewLayoutItemProxy(this);

            connect(d->proxy, SIGNAL(focusedIn()), this, SLOT(onFocusedIn()));
            connect(d->proxy, SIGNAL(focusedOut()), this, SLOT(onFocusedOut()));      

            d->splitter->addWidget(d->proxy);

            d->proxy->setView(d->b->d->proxy->view());
            d->proxy->setFocus(Qt::OtherFocusReason);

            delete d->b;

            d->b = NULL;

            d->footer->show();
        }
    }

    else if(d->layout->current() == d->b) {

        delete d->b;

        d->b = NULL;

        if(d->a->d->a && d->a->d->b) {

            dtkViewLayoutItem *a = d->a->d->a; a->d->parent = this;
            dtkViewLayoutItem *b = d->a->d->b; b->d->parent = this;

            a->setParent(this);
            b->setParent(this);

            d->splitter->setOrientation(d->a->d->splitter->orientation());

            delete d->a;

            d->a = NULL;

            d->a = a;
            d->b = b;

            d->splitter->addWidget(d->a);
            d->splitter->addWidget(d->b);

            dtkViewLayoutItemProxy *child = NULL;

            if(!(child = dtkViewLayoutItemPrivate::firstViewChild(d->a)))
                 child = dtkViewLayoutItemPrivate::firstViewChild(d->b);

            if (child)
                child->setFocus(Qt::OtherFocusReason);

        } else {

            d->proxy = new dtkViewLayoutItemProxy(this);

            connect(d->proxy, SIGNAL(focusedIn()), this, SLOT(onFocusedIn()));
            connect(d->proxy, SIGNAL(focusedOut()), this, SLOT(onFocusedOut()));

            d->splitter->addWidget(d->proxy);

            d->proxy->setView(d->a->d->proxy->view());
            d->proxy->setFocus(Qt::OtherFocusReason);

            delete d->a;

            d->a = NULL;

            d->footer->show();
        }

    } else {

        qDebug() << __func__ << "Unhandled case.";

    }
}

void dtkViewLayoutItem::onFocusedIn(void)
{
    d->layout->setCurrent(this);

    d->footer->setStyleSheet(".QFrame { background: #94a5cc; }");
    d->footer->update();
}

void dtkViewLayoutItem::onFocusedOut(void)
{
    d->footer->setStyleSheet(".QFrame { background: #aaaaaa; }");
    d->footer->update();
}

void dtkViewLayoutItem::close(void)
{
    this->onFocusedIn();

    if (d->parent)
        d->parent->unsplit();
}

void dtkViewLayoutItem::horzt(void)
{
    this->onFocusedIn();

    d->splitter->setOrientation(Qt::Horizontal);

    this->split();
}

void dtkViewLayoutItem::vertc(void)
{
    this->onFocusedIn();

    d->splitter->setOrientation(Qt::Vertical);

    this->split();
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

    d->proxy->setView(dtkAbstractViewFactory::instance()->view(event->mimeData()->text()));
}
