/* dtkAbstractDataReader.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 22:03:03 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:10:57 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataReader.h>

class dtkAbstractDataReaderPrivate
{
public:
    bool enabled;

    dtkAbstractData *data;
};

dtkAbstractDataReader::dtkAbstractDataReader(void) : dtkAbstractObject(), d(new dtkAbstractDataReaderPrivate)
{
    d->enabled = false;
    d->data = NULL;
}

dtkAbstractDataReader::~dtkAbstractDataReader(void)
{
    delete d;

    d = NULL;
}

bool dtkAbstractDataReader::enabled(void)
{
    return d->enabled;
}

void dtkAbstractDataReader::enable(void)
{
    d->enabled = true;
}

void dtkAbstractDataReader::disable(void)
{
    d->enabled = false;
}

dtkAbstractData *dtkAbstractDataReader::data(void)
{
    return d->data;
}

void dtkAbstractDataReader::setData(dtkAbstractData *data)
{
    d->data = data;
}

bool dtkAbstractDataReader::read(const QString& path)
{
    Q_UNUSED(path);

    return false;
}
