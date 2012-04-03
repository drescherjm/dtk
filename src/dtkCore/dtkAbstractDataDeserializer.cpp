/* dtkAbstractDataSerializer.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: lun. oct. 17 13:20:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. déc.  8 17:25:58 2011 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 9
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkAbstractDataDeserializer.h"

class dtkAbstractDataDeserializerPrivate
{
public:
    bool enabled;

    dtkAbstractData *data;
};

dtkAbstractDataDeserializer::dtkAbstractDataDeserializer(void) : dtkAbstractObject(), d(new dtkAbstractDataDeserializerPrivate)
{
    d->enabled = false;
}

dtkAbstractDataDeserializer::~dtkAbstractDataDeserializer(void)
{
    delete d;

    d = NULL;
}

bool dtkAbstractDataDeserializer::enabled(void) const
{
    return d->enabled;
}

void dtkAbstractDataDeserializer::enable(void)
{
    d->enabled = true;
}

void dtkAbstractDataDeserializer::disable(void)
{
    d->enabled = false;
}

dtkAbstractData *dtkAbstractDataDeserializer::data(void)
{
    return d->data;
}

void dtkAbstractDataDeserializer::setData(dtkAbstractData *data)
{
    d->data = data;
}

bool dtkAbstractDataDeserializer::deserialize(const QByteArray &array)
{
    return false ;
}

void dtkAbstractDataDeserializer::setProgress(int value)
{
    emit progressed (value);
}

