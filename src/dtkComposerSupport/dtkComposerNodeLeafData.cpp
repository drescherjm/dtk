/* dtkComposerNodeLeafData.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 10:13:10 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Fri Nov 16 16:10:04 (+0100)
 *           By: Thibaud Kloczko, Inria.
 *     Update #: 69
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeLeafData.h"

#include <dtkCoreSupport/dtkAbstractData.h>
#include <dtkCoreSupport/dtkAbstractDataFactory.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafDataPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeafDataPrivate
{
public:
    dtkAbstractData *data;

    bool implementation_has_changed;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafData implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLeafData::dtkComposerNodeLeafData(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeLeafDataPrivate)
{
    d->data = NULL;
    d->implementation_has_changed = false;
}

dtkComposerNodeLeafData::~dtkComposerNodeLeafData(void)
{
    if (d->data)
        delete d->data;

    d->data = NULL;

    delete d;

    d = NULL;
}

bool dtkComposerNodeLeafData::enableDefaultImplementation(void) const
{
    return false;
}

bool dtkComposerNodeLeafData::implementationHasChanged(void) const
{
    return d->implementation_has_changed;
}

QString dtkComposerNodeLeafData::currentImplementation(void)
{
    if (d->data)
        return d->data->identifier();

    return QString();
}

QStringList dtkComposerNodeLeafData::implementations(void)
{
    QStringList implementations;

    if (this->enableDefaultImplementation())
        implementations << "default";

    QStringList all_implementations = dtkAbstractDataFactory::instance()->implementations(this->abstractDataType());

    for (int i = 0; i < all_implementations.count(); ++i)
        implementations << all_implementations.at(i);

    return implementations;
}

dtkAbstractData *dtkComposerNodeLeafData::createData(const QString& implementation)
{
    d->implementation_has_changed = false;

    if (implementation.isEmpty() || implementation == "Choose implementation")
        return NULL;

    if (implementation == "default")
        const_cast<QString&>(implementation) = this->abstractDataType();

    if (!d->data) {

        d->data = dtkAbstractDataFactory::instance()->create(implementation);

        d->implementation_has_changed = true;

    } else if (d->data->identifier() != implementation) {

        delete d->data;

        d->data = dtkAbstractDataFactory::instance()->create(implementation);

        d->implementation_has_changed = true;

    }

    return d->data;
}

dtkAbstractData *dtkComposerNodeLeafData::data(void)
{
    return d->data;
}
