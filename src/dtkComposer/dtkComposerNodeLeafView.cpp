/* dtkComposerNodeLeafView.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 14:38:55 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul  3 12:36:55 2012 (+0200)
 *           By: tkloczko
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeLeafView.h"

#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafViewPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeafViewPrivate
{
public:
    dtkAbstractView *view;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafView implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLeafView::dtkComposerNodeLeafView(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeLeafViewPrivate)
{
    d->view = NULL;
}

dtkComposerNodeLeafView::~dtkComposerNodeLeafView(void)
{
    if (d->view)
        delete d->view;

    d->view = NULL;

    delete d;

    d = NULL;
}

QString dtkComposerNodeLeafView::currentImplementation(void)
{
    if (d->view)
        return d->view->identifier();

    return QString();
}

QStringList dtkComposerNodeLeafView::implementations(void)
{
    QStringList implementations;
    QStringList all_implementations = dtkAbstractViewFactory::instance()->implementations(this->abstractViewType());

   for (int i = 0; i < all_implementations.count(); ++i)
        implementations << all_implementations.at(i);

    return implementations;
}

dtkAbstractView *dtkComposerNodeLeafView::createView(const QString& implementation)
{
    if (implementation.isEmpty() || implementation == "Choose implementation")
        return NULL;
    
    if (!d->view) {

        d->view = dtkAbstractViewFactory::instance()->create(implementation);

    } else if (d->view->identifier() != implementation) {

        delete d->view;

        d->view = dtkAbstractViewFactory::instance()->create(implementation);

    }        

    return d->view;
}

dtkAbstractView *dtkComposerNodeLeafView::view(void)
{
    return d->view;
}
