// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkWidgetsViewLayout.h"
#include "dtkWidgetsViewLayoutItem.h"

#include <dtkCoreSupport/dtkAbstractView.h>
#include <dtkCoreSupport/dtkAbstractViewFactory.h>

#include <QtWidgets>

// /////////////////////////////////////////////////////////////////
// dtkWidgetsViewLayoutItemProxyPrivate
// /////////////////////////////////////////////////////////////////

class dtkWidgetsViewLayoutItemProxyPrivate
{
public:
    QWidget *view;
};

// /////////////////////////////////////////////////////////////////
// dtkWidgetsViewLayoutItemPrivate
// /////////////////////////////////////////////////////////////////

class dtkWidgetsViewLayoutItemPrivate
{
public:
    static dtkWidgetsViewLayoutItemProxy *firstViewChild(dtkWidgetsViewLayoutItem *item);

public:
    dtkWidgetsViewLayoutItem *root;
    dtkWidgetsViewLayoutItem *parent;

public:
    dtkWidgetsViewLayoutItem *a;
    dtkWidgetsViewLayoutItem *b;

public:
    dtkWidgetsViewLayout *layout;

public:
    dtkWidgetsViewLayoutItemProxy *proxy;

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
    dtkWidgetsViewLayoutItem *q;
};

// /////////////////////////////////////////////////////////////////
// dtkWidgetsViewLayoutItemProxy
// /////////////////////////////////////////////////////////////////

dtkWidgetsViewLayoutItemProxy::dtkWidgetsViewLayoutItemProxy(QWidget *parent) : QFrame(parent), d(new dtkWidgetsViewLayoutItemProxyPrivate)
{
    d->view = NULL;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    this->setFocusPolicy(Qt::StrongFocus);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

dtkWidgetsViewLayoutItemProxy::~dtkWidgetsViewLayoutItemProxy(void)
{
//    qDebug() << __func__ << 1;

    if(!d->view)
        goto finalize;

    if(!d->view)
        goto finalize;

    if(!d->view->parentWidget())
        goto finalize;

//    qDebug() << __func__ << 2;

    if(dtkWidgetsViewLayoutItemProxy *proxy = dynamic_cast<dtkWidgetsViewLayoutItemProxy *>(d->view->parentWidget())) {

//        qDebug() << __func__ << 3;

        if(proxy == this) {

//            qDebug() << __func__ << 4;

            layout()->removeWidget(d->view);

//            qDebug() << __func__ << 5;

            d->view->setParent(0);

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

QWidget *dtkWidgetsViewLayoutItemProxy::view(void)
{
    return d->view;
}

void dtkWidgetsViewLayoutItemProxy::setView(QWidget *view)
{
    // qDebug() << __func__ << 1;

    if(!view)
        return;

    if(dtkWidgetsViewLayoutItemProxy *proxy = dynamic_cast<dtkWidgetsViewLayoutItemProxy *>(view->parentWidget())) {
        proxy->layout()->removeWidget(view);
        proxy->d->view = NULL;

        if(dtkWidgetsViewLayoutItem *item = dynamic_cast<dtkWidgetsViewLayoutItem *>(proxy->parentWidget()->parentWidget())) {
            // qDebug() << "Got parent ! - clearing name";
            item->d->label->clear();
        }

        disconnect(view, SIGNAL(focused()), proxy, SIGNAL(focusedIn()));
    }

    this->layout()->addWidget(view);

    d->view = view;
    d->view->show();
    connect(view, SIGNAL(focused()), this, SIGNAL(focusedIn()));

    if(dtkWidgetsViewLayoutItem *item = dynamic_cast<dtkWidgetsViewLayoutItem *>(this->parentWidget()->parentWidget())) {

        // qDebug() << "Got parent ! - setting name";

        item->d->close->setEnabled(true);
        item->d->vertc->setEnabled(true);
        item->d->horzt->setEnabled(true);
        item->d->maxmz->setEnabled(true);
        emit focusedIn();
    }

    // qDebug() << __func__ << 2 << this->parentWidget()->objectName() << this->parentWidget()->metaObject()->className();
}

void dtkWidgetsViewLayoutItemProxy::focusInEvent(QFocusEvent *event)
{
    QFrame::focusInEvent(event);

    emit focusedIn();
}

void dtkWidgetsViewLayoutItemProxy::focusOutEvent(QFocusEvent *event)
{
    QFrame::focusOutEvent(event);

    emit focusedOut();
}

// /////////////////////////////////////////////////////////////////
// dtkWidgetsViewLayoutItemPrivate
// /////////////////////////////////////////////////////////////////

dtkWidgetsViewLayoutItemProxy *dtkWidgetsViewLayoutItemPrivate::firstViewChild(dtkWidgetsViewLayoutItem *item)
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
// dtkWidgetsViewLayoutItem
// /////////////////////////////////////////////////////////////////

dtkWidgetsViewLayoutItem::dtkWidgetsViewLayoutItem(dtkWidgetsViewLayoutItem *parent) : QFrame(parent), d(new dtkWidgetsViewLayoutItemPrivate)
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

    d->proxy = new dtkWidgetsViewLayoutItemProxy(this);

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
    d->footer->setObjectName("dtkWidgetsViewLayoutItemFooterUnfocused");

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

    d->close->setEnabled(d->parent!=NULL);
    d->vertc->setEnabled(false);
    d->horzt->setEnabled(false);
    d->maxmz->setEnabled(false);
}

dtkWidgetsViewLayoutItem::~dtkWidgetsViewLayoutItem(void)
{
    delete d;

    d = NULL;
}

QWidget *dtkWidgetsViewLayoutItem::view(void)
{
    if(this->proxy())
        return proxy()->view();
    else
        return NULL;
}

dtkWidgetsViewLayoutItem *dtkWidgetsViewLayoutItem::parent(void)
{
    return d->parent;
}

dtkWidgetsViewLayoutItem *dtkWidgetsViewLayoutItem::first(void)
{
    return d->a;
}

dtkWidgetsViewLayoutItem *dtkWidgetsViewLayoutItem::second(void)
{
    return d->b;
}

void dtkWidgetsViewLayoutItem::setOrientation(Qt::Orientation orientation)
{
    d->splitter->setOrientation(orientation);
}

void dtkWidgetsViewLayoutItem::setSizes(QList<int> sizes)
{
    d->splitter->setSizes(sizes);
}

int dtkWidgetsViewLayoutItem::canvasHeight(void)
{
    return d->splitter->sizes().first();
}

int dtkWidgetsViewLayoutItem::footerHeight(void)
{
    return d->footer->height();
}

int dtkWidgetsViewLayoutItem::handleHeight(void)
{
    return 7;
}

int dtkWidgetsViewLayoutItem::handleWidth(void)
{
    return 7;
}

dtkWidgetsViewLayout *dtkWidgetsViewLayoutItem::layout(void)
{
    return d->layout;
}

dtkWidgetsViewLayoutItemProxy *dtkWidgetsViewLayoutItem::proxy(void)
{
    return d->proxy;
}

void dtkWidgetsViewLayoutItem::setLayout(dtkWidgetsViewLayout *layout)
{
    d->layout = layout;
}

void dtkWidgetsViewLayoutItem::clear(void)
{
    if (d->proxy && d->proxy->view()){
        d->proxy->view()->hide();
        emit unfocused(d->proxy->view());
    }
    delete d->proxy;

    d->proxy = new dtkWidgetsViewLayoutItemProxy(d->root);

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

    d->label->clear();
    d->close->setEnabled(false);
    d->vertc->setEnabled(false);
    d->horzt->setEnabled(false);
    d->maxmz->setEnabled(false);
}

void dtkWidgetsViewLayoutItem::split(void)
{
    if(!d->proxy->view())
        return;

    QSize size = this->size();

    d->a = new dtkWidgetsViewLayoutItem(this);
    d->b = new dtkWidgetsViewLayoutItem(this);

    d->splitter->addWidget(d->a);
    d->splitter->addWidget(d->b);

    d->a->d->proxy->setFocus(Qt::OtherFocusReason);
    d->a->d->proxy->setView(d->proxy->view());

    disconnect(d->proxy, SIGNAL(focusedIn()), this, SLOT(onFocusedIn()));
    disconnect(d->proxy, SIGNAL(focusedOut()), this, SLOT(onFocusedOut()));

    delete d->proxy;

    d->proxy = NULL;

    d->footer->hide();

    d->splitter->resize(size);
}

void dtkWidgetsViewLayoutItem::unsplit(void)
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

            dtkWidgetsViewLayoutItem *a = d->b->d->a; a->d->parent = this;
            dtkWidgetsViewLayoutItem *b = d->b->d->b; b->d->parent = this;

            a->setParent(this);
            b->setParent(this);

            d->splitter->setOrientation(d->b->d->splitter->orientation());

            d->b->deleteLater();

            d->b = NULL;

            d->a = a;
            d->b = b;

            d->splitter->addWidget(d->a);
            d->splitter->addWidget(d->b);

            dtkWidgetsViewLayoutItemProxy *child = NULL;

            if(!(child = dtkWidgetsViewLayoutItemPrivate::firstViewChild(d->a)))
                 child = dtkWidgetsViewLayoutItemPrivate::firstViewChild(d->b);

            if (child)
                child->setFocus(Qt::OtherFocusReason);

        } else {

            // qDebug() << __func__ << "Current item is a, b has no children, creating a proxy.";

            d->proxy = new dtkWidgetsViewLayoutItemProxy(this);

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

            dtkWidgetsViewLayoutItem *a = d->a->d->a; a->d->parent = this;
            dtkWidgetsViewLayoutItem *b = d->a->d->b; b->d->parent = this;

            a->setParent(this);
            b->setParent(this);

            d->splitter->setOrientation(d->a->d->splitter->orientation());

            d->a->deleteLater();

            d->a = NULL;

            d->a = a;
            d->b = b;

            d->splitter->addWidget(d->a);
            d->splitter->addWidget(d->b);

            dtkWidgetsViewLayoutItemProxy *child = NULL;

            if(!(child = dtkWidgetsViewLayoutItemPrivate::firstViewChild(d->a)))
                 child = dtkWidgetsViewLayoutItemPrivate::firstViewChild(d->b);

            if (child)
                child->setFocus(Qt::OtherFocusReason);

        } else {

            // qDebug() << __func__ << "Current item is b, a has no children, creating a proxy.";

            d->proxy = new dtkWidgetsViewLayoutItemProxy(this);

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

void dtkWidgetsViewLayoutItem::maximize(void)
{
    if(d->a && d->b)
        return;

    if(this == d->root)
        return;

    d->root->setUpdatesEnabled(false);

    d->root->d->proxy = new dtkWidgetsViewLayoutItemProxy(d->root);

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

void dtkWidgetsViewLayoutItem::onFocusedIn(void)
{
    if (d->layout->current())
        d->layout->current()->onFocusedOut();

    d->layout->setCurrent(this);

    d->footer->setObjectName("dtkWidgetsViewLayoutItemFooterFocused");
    d->footer->style()->unpolish(d->footer);
    d->footer->style()->polish(d->footer);
    d->footer->update();

    if(d->proxy->view())
        d->root->notify(d->proxy->view());
}

void dtkWidgetsViewLayoutItem::onFocusedOut(void)
{
    d->footer->setObjectName("dtkWidgetsViewLayoutItemFooterUnfocused");
    d->footer->style()->unpolish(d->footer);
    d->footer->style()->polish(d->footer);
    d->footer->update();
}

void dtkWidgetsViewLayoutItem::close(void)
{
    this->onFocusedIn();

    if (d->parent)
        d->parent->unsplit();
    else
        clear();
}

void dtkWidgetsViewLayoutItem::horzt(void)
{
    this->onFocusedIn();

    d->splitter->setOrientation(Qt::Horizontal);

    this->split();
}

void dtkWidgetsViewLayoutItem::vertc(void)
{
    this->onFocusedIn();

    d->splitter->setOrientation(Qt::Vertical);

    this->split();
}

void dtkWidgetsViewLayoutItem::maxmz(void)
{
    this->onFocusedIn();

    this->maximize();
}

void dtkWidgetsViewLayoutItem::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void dtkWidgetsViewLayoutItem::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void dtkWidgetsViewLayoutItem::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void dtkWidgetsViewLayoutItem::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event);

    if(d->a && d->b)
        return;

    if(d->proxy->view())
        return;

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

    // dtkAbstractView *view = dtkAbstractViewFactory::instance()->view(event->mimeData()->text());

    // d->proxy->setView(view);

// ///////////////////////////////////////////////////////////
}

void dtkWidgetsViewLayoutItem::notify(QWidget *view)
{
    if(d->root == this)
        emit focused(view);
}

//
// dtkWidgetsViewLayoutItem.cpp ends here
