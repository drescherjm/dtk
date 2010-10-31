/* dtkAbstractDataConverter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 22:03:03 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Oct 31 19:45:43 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 37
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataConverter.h>

class dtkAbstractDataConverterPrivate
{
public:
    bool enabled;

    dtkAbstractData *data;
};

dtkAbstractDataConverter::dtkAbstractDataConverter(void) : dtkAbstractObject(), d(new dtkAbstractDataConverterPrivate)
{
    d->enabled = false;
    d->data = NULL;
}

dtkAbstractDataConverter::~dtkAbstractDataConverter(void)
{
    delete d;

    d = NULL;
}

bool dtkAbstractDataConverter::enabled(void)
{
    return d->enabled;
}

void dtkAbstractDataConverter::enable(void)
{
    d->enabled = true;
}

void dtkAbstractDataConverter::disable(void)
{
    d->enabled = false;
}

dtkAbstractData *dtkAbstractDataConverter::data(void)
{
    return d->data;
}

void dtkAbstractDataConverter::setData(dtkAbstractData *data)
{
    d->data = data;
}

bool dtkAbstractDataConverter::canConvert(QString toType)
{
    return this->toType() == toType;
}

dtkAbstractData *dtkAbstractDataConverter::convert(void)
{
    return NULL;
}

void dtkAbstractDataConverter::setProgress(int value)
{
    emit progressed (value);
}
