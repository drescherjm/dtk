/* dtkAbstractDataConverter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 22:03:03 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jul  5 15:16:11 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 38
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataConverter.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkSmartPointer.h>

class dtkAbstractDataConverterPrivate
{
public:
    bool enabled;

    dtkSmartPointer<dtkAbstractData> data;
};

dtkAbstractDataConverter::dtkAbstractDataConverter(void) : dtkAbstractObject(), d(new dtkAbstractDataConverterPrivate)
{
    d->enabled = false;
}

dtkAbstractDataConverter::~dtkAbstractDataConverter(void)
{
    delete d;

    d = NULL;
}

bool dtkAbstractDataConverter::enabled(void) const
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

bool dtkAbstractDataConverter::canConvert(const QString& toType)
{
    return (this->toType() == toType);
}

dtkAbstractData *dtkAbstractDataConverter::convert(void)
{
    return NULL;
}

void dtkAbstractDataConverter::setProgress(int value)
{
    emit progressed (value);
}
