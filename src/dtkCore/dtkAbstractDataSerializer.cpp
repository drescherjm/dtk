/* dtkAbstractDataSerializer.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: lun. oct. 17 13:20:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 11:28:04 2012 (+0200)
 *           By: tkloczko
 *     Update #: 27
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkAbstractDataSerializer.h"
#include "dtkAbstractDataSerializer_p.h"

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataSerializer implementation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataSerializer::dtkAbstractDataSerializer(void) : dtkAbstractObject(*new dtkAbstractDataSerializerPrivate(this), 0)
{
    DTK_D(dtkAbstractDataSerializer);

    d->enabled = false;
}

dtkAbstractDataSerializer::dtkAbstractDataSerializer(const dtkAbstractDataSerializer& other) : dtkAbstractObject(*new dtkAbstractDataSerializerPrivate(*other.d_func()), other)
{

}

dtkAbstractDataSerializer::~dtkAbstractDataSerializer(void)
{

}

bool dtkAbstractDataSerializer::enabled(void) const
{
    DTK_D(const dtkAbstractDataSerializer);

    return d->enabled;
}

void dtkAbstractDataSerializer::enable(void)
{
    DTK_D(dtkAbstractDataSerializer);

    d->enabled = true;
}

void dtkAbstractDataSerializer::disable(void)
{
    DTK_D(dtkAbstractDataSerializer);

    d->enabled = false;
}

QByteArray *dtkAbstractDataSerializer::data(void) const
{
    DTK_D(const dtkAbstractDataSerializer);

    return d->binary;
}

void dtkAbstractDataSerializer::setData(QByteArray *array)
{
    DTK_D(dtkAbstractDataSerializer);

    d->binary = array;
}

QByteArray *dtkAbstractDataSerializer::serialize(void)
{
    return NULL;
}

QByteArray *dtkAbstractDataSerializer::serialize(dtkAbstractData *data)
{
    DTK_UNUSED(data);
    return NULL;
}

void dtkAbstractDataSerializer::setProgress(int value)
{
    emit progressed (value);
}

