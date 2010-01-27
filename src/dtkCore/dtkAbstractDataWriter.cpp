/* dtkAbstractDataWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 22:03:03 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Oct  3 18:19:10 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataWriter.h>

class dtkAbstractDataWriterPrivate
{
public:
    bool enabled;

    dtkAbstractData *data;
};

dtkAbstractDataWriter::dtkAbstractDataWriter(void) : dtkAbstractObject(), d(new dtkAbstractDataWriterPrivate)
{
    d->enabled = false;
    d->data = NULL;
}

dtkAbstractDataWriter::~dtkAbstractDataWriter(void)
{
    delete d;

    d = NULL;
}

bool dtkAbstractDataWriter::enabled(void)
{
    return d->enabled;
}

void dtkAbstractDataWriter::enable(void)
{
    d->enabled = true;
}

void dtkAbstractDataWriter::disable(void)
{
    d->enabled = false;
}

dtkAbstractData *dtkAbstractDataWriter::data(void)
{
    return d->data;
}

void dtkAbstractDataWriter::setData(dtkAbstractData *data)
{
    d->data = data;
}

bool dtkAbstractDataWriter::canWrite(QString file)
{
    DTK_UNUSED(file);

    return false;
}

bool dtkAbstractDataWriter::canWrite(QStringList files)
{
    DTK_UNUSED(files);

    return false;
}

bool dtkAbstractDataWriter::write(QString file)
{
    DTK_UNUSED(file);

    return false;
}

bool dtkAbstractDataWriter::write(QStringList files)
{
    DTK_UNUSED(files);

    return false;
}
