/* dtkAbstractData.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:01:09 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Sep 22 12:49:01 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 99
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataReader.h>
#include <dtkCore/dtkAbstractDataWriter.h>
#include <dtkCore/dtkLog.h>

class dtkAbstractDataPrivate
{
public:
    QMap<QString, dtkAbstractDataReader *> readers;
    QMap<QString, dtkAbstractDataWriter *> writers;

    QString     path;
    QStringList paths;
};

dtkAbstractData::dtkAbstractData(dtkAbstractData *parent) : dtkAbstractObject(parent), d(new dtkAbstractDataPrivate)
{

}

dtkAbstractData::dtkAbstractData(const dtkAbstractData& data) : dtkAbstractObject(), d(new dtkAbstractDataPrivate)
{
    this->setParent(data.parent());

    d->readers = data.d->readers;
    d->writers = data.d->writers;
}

dtkAbstractData::~dtkAbstractData(void)
{
    delete d;

    d = NULL;
}


QString dtkAbstractData::description(void) const
{
    return "";
}

void dtkAbstractData::addReader(dtkAbstractDataReader *reader)
{
    d->readers.insert(reader->description(), reader);
}

void dtkAbstractData::addWriter(dtkAbstractDataWriter *writer)
{
    d->writers.insert(writer->description(), writer);
}

void dtkAbstractData::enableReader(QString reader)
{
    if (d->readers.contains(reader)) {
        d->readers.value(reader)->setData(this);
	d->readers.value(reader)->enable();
    } else
	dtkDebug() << description() << "has no such reader: " << reader;
}

void dtkAbstractData::disableReader(QString reader)
{
    if (d->readers.contains(reader))
	d->readers.value(reader)->disable();
}

void dtkAbstractData::enableWriter(QString writer)
{
    if (d->writers.contains(writer)) {
        d->writers.value(writer)->setData(this);
	d->writers.value(writer)->enable();
    } else
	dtkDebug() << description() << "has no such writer: " << writer;
}

void dtkAbstractData::disableWriter(QString writer)
{
    if (d->writers.contains(writer))
	d->writers.value(writer)->disable();
}

dtkAbstractDataReader *dtkAbstractData::reader(QString type)
{
    if (d->readers.contains(type))
	return d->readers.value(type);

    return NULL;
}

dtkAbstractDataWriter *dtkAbstractData::writer(QString type)
{
    if (d->writers.contains(type))
	return d->writers.value(type);

    return NULL;
}

void dtkAbstractData::update(void)
{

}

bool dtkAbstractData::read(const QString& file)
{
    bool read = false;

    foreach(dtkAbstractDataReader *reader, d->readers)
        if(reader->enabled() && !read)
            read = reader->read(file);

    if (read && d->path.isEmpty())
        d->path = file;

    if (read && !d->paths.contains(file))
        d->paths << file;

    return read;
}

bool dtkAbstractData::write(const QString& file)
{
    bool written = false;

    foreach(dtkAbstractDataWriter *writer, d->writers)
        if(writer->enabled() && !written)
            written = writer->write(file);

    return written;
}

QString dtkAbstractData::path(void)
{
    return d->path;
}

QStringList dtkAbstractData::paths(void)
{
    return d->paths;
}

void *dtkAbstractData::output(void)
{
    return NULL;
}

void *dtkAbstractData::data(void)
{
    return NULL;
}

void *dtkAbstractData::data(int channel)
{
    Q_UNUSED(channel);

    return NULL;
}

void dtkAbstractData::setData(void* data)
{
    Q_UNUSED(data);
}

void dtkAbstractData::setData(void* data, int channel)
{
    Q_UNUSED(data);
    Q_UNUSED(channel);
}

QDebug operator<<(QDebug debug, const dtkAbstractData& data)
{
    debug.nospace() << data.description();

    return debug.space();
}

QDebug operator<<(QDebug debug, dtkAbstractData *data)
{
    debug.nospace() << data->description();

    return debug.space();
}
