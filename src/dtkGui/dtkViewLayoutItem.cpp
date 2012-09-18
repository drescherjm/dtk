/* dtkViewLayoutItem.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:45 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 24 13:54:00 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 789
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
    dtkAbstractView *view;
};

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
    QPushButton *maxmz;

public:
    QLineEdit *label;

public:
    QFrame *footer;

public:
    dtkViewLayoutItem *q;
};

// /////////////////////////////////////////////////////////////////
// dtkViewLayoutItemProxy
// /////////////////////////////////////////////////////////////////

dtkViewLayoutItemProxy::dtkViewLayoutItemProxy(QWidget *parent) : QFrame(parent), d(new dtkViewLayoutItemProxyPrivate)
{
    d->view = NULL;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    this->setFocusPolicy(Qt::StrongFocus);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

dtkViewLayoutItemProxy::~dtkViewLayoutItemProxy(void)
{
//    qDebug() << __func__ << 1;

    if(!d->view)
        goto finalize;

    if(!d->view->widget())
        goto finalize;
    
    if(!d->view->widget()->parentWidget())
        goto finalize;

//    qDebug() << __func__ << 2;

    if(dtkViewLayoutItemProxy *proxy = dynamic_cast<dtkViewLayoutItemProxy *>(d->view->widget()->parentWidget())) {

//        qDebug() << __func__ << 3;

        if(proxy == this) {

//            qDebug() << __func__ << 4;

            layout()->removeWidget(d->view->widget());

//            qDebug() << __func__ << 5;

            d->view->widget()->setParent(0);

//            qDebug() << __func__ << 6;

            disconnect(d->view, SIGNAL(focused()), proxy, SIGNAL(focusedIn()));

            d->view = NULL;
        }
    }

//    qDebug() << __func__ << 7;

finalize:
    
    delete d;

    d = NULL;
}

dtkAbstractView *dtkViewLayoutItemProxy::view(void)
{
    return d->view;
}

void dtkViewLayoutItemProxy::setView(dtkAbstractView *view)
{
    // qDebug() << __func__ << 1;
    
    if(!view)
        return;

    if(!view->widget())
        return;

    if(dtkViewLayoutItemProxy *proxy = dynamic_cast<dtkViewLayoutItemProxy *>(view->widget()->parentWidget())) {
        proxy->layout()->removeWidget(view->widget());
        proxy->d->view = NULL;

        if(dtkViewLayoutItem *item = dynamic_cast<dtkViewLayoutItem *>(proxy->parentWidget()->parentWidget())) {
            // qDebug() << "Got parent ! - clearing name";
            item->d->label->clear();
        }

        disconnect(view, SIGNAL(focused()), proxy, SIGNAL(focusedIn()));
    }

    this->layout()->addWidget(view->widget());
    
    d->view = view;

    connect(view, SIGNAL(focused()), this, SIGNAL(focusedIn()));

    if(dtkViewLayoutItem *item = dynamic_cast<dtkViewLayoutItem *>(this->parentWidget()->parentWidget())) {

        // qDebug() << "Got parent ! - setting name";

        item->d->label->setText(d->view->objectName());
    }

    // qDebug() << __func__ << 2 << this->parentWidget()->objectName() << this->parentWidget()->metaObject()->className();
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
    d->maxmz = new QPushButton("Maxmz", this);
    
    d->label = new QLineEdit(this);
    d->label->setReadOnly(true);

    QHBoxLayout *footer_layout = new QHBoxLayout;
    footer_layout->addWidget(d->label);
    footer_layout->addWidget(d->horzt);
    footer_layout->addWidget(d->vertc);
    footer_layout->addWidget(d->maxmz);
    footer_layout->addWidget(d->close);

    d->footer = new QFrame(this);
    d->footer->setLayout(footer_layout);
    d->footer->setObjectName("dtkViewLayoutItemFooterUnfocused");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->splitter);
    layout->addWidget(d->footer);

    this->setAcceptDrops(true);

    connect(d->close, SIGNAL(clicked()), this, SLOT(close()));
    connect(d->horzt, SIGNAL(clicked()), this, SLOT(horzt()));
    connect(d->vertc, SIGNAL(clicked()), this, SLOT(vertc()));
    connect(d->maxmz, SIGNAL(clicked()), this, SLOT(maxmz()));

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

void dtkViewLayoutItem::clear(void)
{
    if (d->proxy && d->proxy->view())
        d->proxy->view()->widget()->hide();
    
    delete d->proxy;
    
    d->proxy = new dtkViewLayoutItemProxy(d->root);
    
    connect(d->proxy, SIGNAL(focusedIn()), this, SLOT(onFocusedIn()));
    connect(d->proxy, SIGNAL(focusedOut()), this, SLOT(onFocusedOut()));
    
    d->splitter->addWidget(d->proxy);
    
    d->proxy->setFocus(Qt::OtherFocusReason);
    
    d->footer->show();
    
    this->setUpdatesEnabled(true);
    
    if (d->a)
        d->a->deleteLater();
    
    if (d->b)
        d->b->deleteLater();
    
    d->a = NULL;
    d->b = NULL;
}

void dtkViewLayoutItem::split(void)
{
    if(!d->proxy->view())
        return;
    
    d->a = new dtkViewLayoutItem(this);
    d->b = new dtkViewLayoutItem(this);

    d->splitter->addWidget(d->a);
    d->splitter->addWidget(d->b);

    d->a->d->proxy->setFocus(Qt::OtherFocusReason);
    d->a->d->proxy->setView(d->proxy->view());

    disconnect(d->proxy, SIGNAL(focusedIn()), this, SLOT(onFocusedIn()));
    disconnect(d->proxy, SIGNAL(focusedOut()), this, SLOT(onFocusedOut()));
    
    d->proxy->deleteLater();
    d->proxy = NULL;

    d->footer->hide();
}

void dtkViewLayoutItem::unsplit(void)
{
    if(!d->a && !d->b)
        return;

    d->root->setUpdatesEnabled(false);

    if(d->layout->current() == d->a) {

        // qDebug() << __func__ << "Current item is a";

        d->a->deleteLater();

        d->a = NULL;

        if(d->b->d->a && d->b->d->b) {

            // qDebug() << __func__ << "Current item is a, b has children, reparenting";

            dtkViewLayoutItem *a = d->b->d->a; a->d->parent = this;
            dtkViewLayoutItem *b = d->b->d->b; b->d->parent = this;

            a->setParent(this);
            b->setParent(this);

            d->splitter->setOrientation(d->b->d->splitter->orientation());

            d->b->deleteLater();

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

            // qDebug() << __func__ << "Current item is a, b has no children, creating a proxy.";

            d->proxy = new dtkViewLayoutItemProxy(this);

            // qDebug() << __func__ << "Current item is a, b has no children, proxy created.";

            connect(d->proxy, SIGNAL(focusedIn()), this, SLOT(onFocusedIn()));
            connect(d->proxy, SIGNAL(focusedOut()), this, SLOT(onFocusedOut()));      

            // qDebug() << __func__ << "Current item is a, b has no children, proxy connected.";

            d->splitter->addWidget(d->proxy);

            // qDebug() << __func__ << "Current item is a, b has no children, proxy layout out.";

            // if(!d->b->d->proxy->view())
            //     qDebug() << "VIEW IS NULL";

            // else if(!d->b->d->proxy->view()->widget())
            //     qDebug() << "VIEW'S WIDGET IS NULL";

            d->proxy->setView(d->b->d->proxy->view());

            // qDebug() << __func__ << "Current item is a, b has no children, proxy set up.";

            d->proxy->setFocus(Qt::OtherFocusReason);

            // qDebug() << __func__ << "Current item is a, b has no children, proxy focused.";

            d->b->deleteLater();

            d->b = NULL;

            // if(!d->proxy->view())
            //     qDebug() << "VIEW IS NULL";

            // else if(!d->proxy->view()->widget())
            //     qDebug() << "VIEW'S WIDGET IS NULL";

            // qDebug() << __func__ << "Current item is a, b has no children, b deleted.";

            d->footer->show();

            // qDebug() << __func__ << "Current item is a, b has no children, done.";
        }
    }

    else if(d->layout->current() == d->b) {

        // qDebug() << __func__ << "Current item is b";

        d->b->deleteLater();

        d->b = NULL;

        if(d->a->d->a && d->a->d->b) {

            // qDebug() << __func__ << "Current item is b, a has children, reparenting";

            dtkViewLayoutItem *a = d->a->d->a; a->d->parent = this;
            dtkViewLayoutItem *b = d->a->d->b; b->d->parent = this;

            a->setParent(this);
            b->setParent(this);

            d->splitter->setOrientation(d->a->d->splitter->orientation());

            d->a->deleteLater();

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

            // qDebug() << __func__ << "Current item is b, a has no children, creating a proxy.";

            d->proxy = new dtkViewLayoutItemProxy(this);

            connect(d->proxy, SIGNAL(focusedIn()), this, SLOT(onFocusedIn()));
            connect(d->proxy, SIGNAL(focusedOut()), this, SLOT(onFocusedOut()));

            d->splitter->addWidget(d->proxy);

            d->proxy->setView(d->a->d->proxy->view());
            d->proxy->setFocus(Qt::OtherFocusReason);

            d->a->deleteLater();

            d->a = NULL;

            d->footer->show();
        }

    } else {

        qDebug() << DTK_PRETTY_FUNCTION << "Unhandled case.";

    }

    d->root->setUpdatesEnabled(true);
}

void dtkViewLayoutItem::maximize(void)
{
    if(d->a && d->b)
        return;

    if(this == d->root)
        return;
    
    d->root->setUpdatesEnabled(false);

    d->root->d->proxy = new dtkViewLayoutItemProxy(d->root);

    d->root->connect(d->root->d->proxy, SIGNAL(focusedIn()), d->root, SLOT(onFocusedIn()));
    d->root->connect(d->root->d->proxy, SIGNAL(focusedOut()), d->root, SLOT(onFocusedOut()));

    d->root->d->splitter->addWidget(d->root->d->proxy);

    d->root->d->proxy->setView(d->proxy->view());
    d->root->d->proxy->setFocus(Qt::OtherFocusReason);

    d->root->d->footer->show();

    d->root->setUpdatesEnabled(true);

    d->root->d->a->deleteLater();
    d->root->d->b->deleteLater();

    d->root->d->a = NULL;
    d->root->d->b = NULL;
}

void dtkViewLayoutItem::onFocusedIn(void)
{
    if (d->layout->current())
        d->layout->current()->onFocusedOut();

    d->layout->setCurrent(this);

    d->footer->setObjectName("dtkViewLayoutItemFooterFocused");
    d->footer->style()->unpolish(d->footer);
    d->footer->style()->polish(d->footer);
    d->footer->update();

    if(d->proxy->view())
        d->root->notify(d->proxy->view());
}

void dtkViewLayoutItem::onFocusedOut(void)
{
    d->footer->setObjectName("dtkViewLayoutItemFooterUnfocused");
    d->footer->style()->unpolish(d->footer);
    d->footer->style()->polish(d->footer);
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

void dtkViewLayoutItem::maxmz(void)
{
    this->onFocusedIn();

    this->maximize();
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

    if(d->proxy->view())
        return;

    dtkAbstractView *view = dtkAbstractViewFactory::instance()->view(event->mimeData()->text());

    d->proxy->setView(view);
}

void dtkViewLayoutItem::notify(dtkAbstractView *view)
{
    if(d->root == this)
        emit focused(view);
}
