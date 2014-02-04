/* dtkComposerFactoryView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 13:24:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:12:38 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 159
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerFactory.h"
#include "dtkComposerFactoryView.h"

#include <dtkGuiSupport/dtkSplitter.h>
#include <dtkGuiSupport/dtkTagCloud.h>

class dtkComposerFactoryViewPrivate
{
public:
    dtkComposerFactory *factory;

public:
    dtkTagScope *scope;
    dtkTagCloud *cloud;
    dtkItemView *view;

public:
    dtkTagController *controller;
};

dtkComposerFactoryView::dtkComposerFactoryView(QWidget *parent) : QWidget(parent), d(new dtkComposerFactoryViewPrivate)
{
    d->factory = NULL;

    d->scope = new dtkTagScope(this);
    d->scope->toggle();

    d->cloud = new dtkTagCloud(this);
    d->cloud->setSortingType(dtkTagCloud::Alpha);
    d->cloud->setSortingOrder(dtkTagCloud::Asc);
    d->cloud->setFontSize(17);
    d->cloud->setFontRange(15);

    d->view = new dtkItemView(this);

    d->controller = new dtkTagController;
    d->controller->attach(d->scope);
    d->controller->attach(d->view);
    d->controller->attach(d->cloud);
    d->controller->onUnionMode(false);

    dtkSplitter *splitter = new dtkSplitter(this);
    splitter->addWidget(d->cloud);
    splitter->addWidget(d->view);
    splitter->setOrientation(Qt::Vertical);
    splitter->setSizes(QList<int>() << 150 << 350);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->scope);
    layout->addWidget(splitter);
}

dtkComposerFactoryView::~dtkComposerFactoryView(void)
{
    delete d->controller;
    delete d;

    d = NULL;
}

void dtkComposerFactoryView::setFactory(dtkComposerFactory *factory)
{
    d->factory = factory;

    foreach(QString node, factory->nodes())
        d->controller->addItem(node, factory->descriptions().value(node), factory->tags().value(node), "node", factory->types().value(node));
 
    d->controller->addItem("Note", "<p>Notes help to identify and annotate some parts of a composition.</p>", QStringList() << "note", "note", "");
}

void dtkComposerFactoryView::setBlue(void)
{
    d->scope->setBlue();
    d->view->setBlue();
}

void dtkComposerFactoryView::setDark(void)
{
    d->scope->setDark();
    d->view->setDark();
}
