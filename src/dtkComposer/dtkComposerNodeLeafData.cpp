/* dtkComposerNodeLeafData.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 10:13:10 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 28 12:33:22 2012 (+0200)
 *           By: tkloczko
 *     Update #: 58
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeLeafData.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafDataPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeafDataPrivate
{
public:
    dtkAbstractData *data;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafData implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLeafData::dtkComposerNodeLeafData(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeLeafDataPrivate)
{
    d->data = NULL;
}

dtkComposerNodeLeafData::~dtkComposerNodeLeafData(void)
{
    if (d->data)
        delete d->data;

    d->data = NULL;

    delete d;

    d = NULL;
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

    foreach(QString implementation, dtkAbstractDataFactory::instance()->implementations(this->abstractDataType()))
        implementations << implementation;

    return implementations;
}

dtkAbstractData *dtkComposerNodeLeafData::createData(const QString& implementation)
{
    if (implementation.isEmpty() || implementation == "Choose implementation")
        return NULL;
    
    if (!d->data) {

        d->data = dtkAbstractDataFactory::instance()->create(implementation);

    } else if (d->data->identifier() != implementation) {

        delete d->data;

        d->data = dtkAbstractDataFactory::instance()->create(implementation);

    }        

    return d->data;
}

dtkAbstractData *dtkComposerNodeLeafData::data(void)
{
    return d->data;
}
