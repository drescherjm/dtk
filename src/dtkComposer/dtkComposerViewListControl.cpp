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

#include "dtkComposerViewController.h"
#include "dtkComposerViewLayout.h"
#include "dtkComposerViewLayoutItem.h"
#include "dtkComposerViewList.h"
#include "dtkComposerViewListControl.h"

class dtkComposerViewListControlPrivate
{
public:
    dtkComposerViewLayout *layout;
    dtkComposerViewList *list;

public:
    QPushButton *hor;
    QPushButton *ver;
    QPushButton *grd;
    QPushButton *cls;
};

dtkComposerViewListControl::dtkComposerViewListControl(QWidget *parent) : QFrame(parent), d(new dtkComposerViewListControlPrivate)
{
    d->layout = NULL;
    d->list = NULL;

    d->hor = new QPushButton("Horizontal", this);
    d->ver = new QPushButton("Vertical", this);
    d->grd = new QPushButton("Grid", this);
    d->cls = new QPushButton("Close All", this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(d->hor);
    layout->addWidget(d->ver);
    layout->addWidget(d->grd);
    layout->addWidget(d->cls);

    connect(d->hor, SIGNAL(clicked()), this, SLOT(onLayoutHorizontally()));
    connect(d->ver, SIGNAL(clicked()), this, SLOT(onLayoutVertically()));
    connect(d->grd, SIGNAL(clicked()), this, SLOT(onLayoutGrid()));
    connect(d->cls, SIGNAL(clicked()), this, SLOT(onLayoutCloseAll()));
}

dtkComposerViewListControl::~dtkComposerViewListControl(void)
{
    delete d;

    d = NULL;
}

void dtkComposerViewListControl::setLayout(dtkComposerViewLayout *layout)
{
    d->layout = layout;
}

void dtkComposerViewListControl::setList(dtkComposerViewList *list)
{
    d->list = list;
}

bool dtkComposerViewListControl::isEmpty(void) const
{
    if (!d->list)
        return true;

    if (!d->list->count())
        return true;

    if (!d->layout)
        return true;

    return false;
}

void dtkComposerViewListControl::onActorStarted(QString view_name)
{
    if (!d->layout)
        return;

    dtkComposerViewWidget *view = dtkComposerViewController::instance()->view(view_name);

    if (view && !d->layout->current()->proxy()->view())
        d->layout->current()->proxy()->setView(view);
}

void dtkComposerViewListControl::layoutHorizontally(void)
{
    if (this->isEmpty())
        return;

    this->closeAllLayout();

    qApp->sendPostedEvents(0, QEvent::DeferredDelete);

    int w = d->layout->current()->width();
    int n = d->list->count();
    int s = d->layout->current()->handleWidth();
    int v = (w - (n - 1) * s) / n;

    for (int i = 1; i <= n; i++) {

        dtkComposerViewLayoutItem *current = d->layout->current();
        current->setOrientation(Qt::Horizontal);
        current->proxy()->setView(dtkComposerViewController::instance()->view(d->list->item(i - 1)->text().split(" ").first()));

        if (i != n) {
            QList<int> sizes = QList<int>() << v << current->width() - s - v;
            current->split();
            current->setSizes(sizes);
        }

        d->layout->setCurrent(current->second());
    }
}

void dtkComposerViewListControl::onLayoutHorizontally(void)
{
    this->layoutHorizontally();
}

void dtkComposerViewListControl::layoutVertically(void)
{
    if (this->isEmpty())
        return;

    this->closeAllLayout();

    qApp->sendPostedEvents(0, QEvent::DeferredDelete);

    int h = d->layout->current()->height();
    int f = d->layout->current()->footerHeight();
    int n = d->list->count();
    int s = d->layout->current()->handleHeight();
    int v = (h - n * f - (n - 1) * s) / n;

    for (int i = 1; i <= n; i++) {

        dtkComposerViewLayoutItem *current = d->layout->current();
        current->setOrientation(Qt::Vertical);
        current->proxy()->setView(dtkComposerViewController::instance()->view(d->list->item(i - 1)->text().split(" ").first()));

        if (i != n) {
            QList<int> sizes = QList<int>() << v + f << current->height() - s - v - f;
            current->split();
            current->setSizes(sizes);
        }

        d->layout->setCurrent(current->second());
    }
}

void dtkComposerViewListControl::onLayoutVertically(void)
{
    this->layoutVertically();
}

void dtkComposerViewListControl::layoutGrid(void)
{
    if (this->isEmpty())
        return;

    int n = d->list->count();
    int i = 0;

    typedef QPair<dtkComposerViewLayoutItem *, Qt::Orientation> item_t;

    d->layout->clear();
    d->layout->setCurrent(d->layout->root());
    d->layout->current()->proxy()->setView(dtkComposerViewController::instance()->view(d->list->item(i)->text().split(" ").first()));

    QList<item_t> items; items << qMakePair(d->layout->current(), Qt::Horizontal);

    for (int i = 1; i < n; i++) {

        item_t item = items.takeFirst();

        d->layout->setCurrent(item.first);

        dtkComposerViewLayoutItem *current = item.first;
        current->setOrientation(item.second);
        current->split();
        current->second()->proxy()->setView(dtkComposerViewController::instance()->view(d->list->item(i)->text().split(" ").first()));

        items << qMakePair(current->first(), item.second == Qt::Horizontal ? Qt::Vertical : Qt::Horizontal);
        items << qMakePair(current->second(), item.second == Qt::Horizontal ? Qt::Vertical : Qt::Horizontal);
    }
}

void dtkComposerViewListControl::onLayoutGrid(void)
{
    this->layoutGrid();
}

void dtkComposerViewListControl::closeAllLayout(void)
{
    if (this->isEmpty())
        return;

    d->layout->clear();
    d->layout->setCurrent(d->layout->root());
}

void dtkComposerViewListControl::onLayoutCloseAll(void)
{
    this->closeAllLayout();
}

//
// dtkComposerViewListControl.cpp ends here
