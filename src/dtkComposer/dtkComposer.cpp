/* dtkComposer.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:34:49 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 31 18:13:52 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 76
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposer.h"
#include "dtkComposer_p.h"
#include "dtkComposerFactory.h"
#include "dtkComposerMachine.h"
#include "dtkComposerScene.h"
#include "dtkComposerStack.h"
#include "dtkComposerView.h"

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkComposer
// /////////////////////////////////////////////////////////////////

dtkComposer::dtkComposer(QWidget *parent) : QWidget(parent), d(new dtkComposerPrivate)
{
    d->machine = new dtkComposerMachine;

    d->factory = new dtkComposerFactory;

    d->stack = new dtkComposerStack;

    d->scene = new dtkComposerScene;
    d->scene->setFactory(d->factory);
    d->scene->setMachine(d->machine);
    d->scene->setStack(d->stack);

    d->view = new dtkComposerView;
    d->view->setScene(d->scene);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->view);
}

dtkComposer::~dtkComposer(void)
{
    delete d->machine;
    delete d->factory;
    delete d->stack;
    delete d;
    
    d = NULL;
}

dtkComposerMachine *dtkComposer::machine(void)
{
    return d->machine;
}

dtkComposerFactory *dtkComposer::factory(void)
{
    return d->factory;
}

dtkComposerStack *dtkComposer::stack(void)
{
    return d->stack;
}
