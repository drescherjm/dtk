/* dtkAbstractDataConverter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 22:03:03 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jun 15 11:09:09 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 36
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
    return this->toType()==toType;
}

dtkAbstractData *dtkAbstractDataConverter::convert(void)
{
    return NULL;
}

void dtkAbstractDataConverter::setProgress(int value)
{
    emit progressed (value);
}
