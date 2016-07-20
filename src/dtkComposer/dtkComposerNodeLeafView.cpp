/* dtkComposerNodeLeafView.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 14:38:55 2012 (+0200)
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

    bool implementation_has_changed;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafView implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLeafView::dtkComposerNodeLeafView(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeLeafViewPrivate)
{
    d->view = NULL;
    d->implementation_has_changed = false;
}

dtkComposerNodeLeafView::~dtkComposerNodeLeafView(void)
{
    if (d->view)
        delete d->view;

    d->view = NULL;

    delete d;

    d = NULL;
}

bool dtkComposerNodeLeafView::enableDefaultImplementation(void) const
{
    return false;
}

bool dtkComposerNodeLeafView::implementationHasChanged(void) const
{
    return d->implementation_has_changed;
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

    if (this->enableDefaultImplementation())
        implementations << "default";

    QStringList all_implementations = dtkAbstractViewFactory::instance()->implementations(this->abstractViewType());

    for (int i = 0; i < all_implementations.count(); ++i)
        implementations << all_implementations.at(i);

    return implementations;
}

dtkAbstractView *dtkComposerNodeLeafView::createView(const QString& implementation)
{
    d->implementation_has_changed = false;

    if (implementation.isEmpty() || implementation == "Choose implementation")
        return NULL;

    if (implementation == "default")
        const_cast<QString&>(implementation) = this->abstractViewType();

    if (!d->view) {

        d->view = dtkAbstractViewFactory::instance()->create(implementation);

        d->implementation_has_changed = true;

    } else if (d->view->identifier() != implementation) {

        delete d->view;

        d->view = dtkAbstractViewFactory::instance()->create(implementation);

        d->implementation_has_changed = true;

    }

    return d->view;
}

QImage dtkComposerNodeLeafView::screenshot(void) const
{
    QWidget *widget = d->view->widget();
    QPixmap pixmap(widget->size());
    widget->render(&pixmap);

    if ( pixmap.width() > 1920) {
        // limit width to FULL HD res.
        return pixmap.scaledToWidth(1920).toImage();
    }

    return pixmap.toImage();

}

void dtkComposerNodeLeafView::setView(dtkAbstractView *view)
{
    d->view = view;
}

dtkAbstractView *dtkComposerNodeLeafView::view(void)
{
    return d->view;
}
