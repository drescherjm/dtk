/* dtkAbstractDataWriter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 22:03:03 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec 14 10:24:41 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 33
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAbstractDataWriter.h"

#include "dtkAbstractData.h"
#include "dtkSmartPointer.h"

class dtkAbstractDataWriterPrivate
{
public:
    bool enabled;

    dtkSmartPointer<dtkAbstractData> data;
};

dtkAbstractDataWriter::dtkAbstractDataWriter(void) : dtkAbstractObject(), d(new dtkAbstractDataWriterPrivate)
{
    d->enabled = false;
}

dtkAbstractDataWriter::~dtkAbstractDataWriter(void)
{
    delete d;

    d = NULL;
}

bool dtkAbstractDataWriter::enabled(void) const
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

/**
 * Set the data that will be written.
 * The writer will increase the reference count of the data.
 */
void dtkAbstractDataWriter::setData(dtkAbstractData *data)
{
    d->data = data;
}

bool dtkAbstractDataWriter::canWrite(const QString& file)
{
    DTK_UNUSED(file);

    return false;
}

bool dtkAbstractDataWriter::canWrite(const QStringList& files)
{
    DTK_UNUSED(files);

    return false;
}

bool dtkAbstractDataWriter::write(const QString& file)
{
    DTK_UNUSED(file);

    return false;
}

bool dtkAbstractDataWriter::write(const QStringList& files)
{
    DTK_UNUSED(files);

    return false;
}

void dtkAbstractDataWriter::setProgress(int value)
{
    emit progressed (value);
}

//! 
/*! 
 * Get the extension this writer prefers.  The list may depend on the
 * data set by setData.  The default implementation returns an
 * empty StringList, indicating no preferred extension.
 * 
 * \return The list of supported extensions.
 */

QStringList dtkAbstractDataWriter::supportedFileExtensions(void) const
{
    return QStringList();
}
