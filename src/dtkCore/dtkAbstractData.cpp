/* dtkAbstractData.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:01:09 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 27 15:27:17 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 152
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
#include <dtkCore/dtkAbstractDataConverter.h>
#include <dtkCore/dtkLog.h>

#include <QtGui>

class dtkAbstractDataPrivate
{
public:
    QMap<QString, dtkAbstractDataReader    *> readers;
    QMap<QString, dtkAbstractDataWriter    *> writers;
    QMap<QString, dtkAbstractDataConverter *> converters;

    QString     path;
    QStringList paths;

    QList<QImage> thumbnails;
};

dtkAbstractData::dtkAbstractData(dtkAbstractData *parent) : dtkAbstractObject(parent), d(new dtkAbstractDataPrivate)
{

}

dtkAbstractData::dtkAbstractData(const dtkAbstractData& data) : dtkAbstractObject(), d(new dtkAbstractDataPrivate)
{
    this->setParent(data.parent());

    d->readers    = data.d->readers;
    d->writers    = data.d->writers;
    d->converters = data.d->converters;
}

dtkAbstractData::~dtkAbstractData(void)
{
    delete d;

    d = NULL;
}


QString dtkAbstractData::description(void) const
{
    DTK_DEFAULT_IMPLEMENTATION;

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

void dtkAbstractData::addConverter(dtkAbstractDataConverter *converter)
{
    d->converters.insert(converter->description(), converter);
    converter->setData (this);
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

void dtkAbstractData::enableConverter(QString converter)
{
    if (d->converters.contains(converter)) {
        d->converters.value(converter)->setData(this);
	d->converters.value(converter)->enable();
    } else
	dtkDebug() << description() << "has no such converter: " << converter;
}

void dtkAbstractData::disableConverter(QString converter)
{
    if (d->converters.contains(converter))
	d->converters.value(converter)->disable();
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

dtkAbstractDataConverter *dtkAbstractData::converter(QString type)
{
    if (d->converters.contains(type))
	return d->converters.value(type);

    return NULL;
}

void dtkAbstractData::update(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

bool dtkAbstractData::read(QString file)
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

bool dtkAbstractData::read(QStringList files)
{
    bool read = false;
  
    foreach(dtkAbstractDataReader *reader, d->readers)
      if(reader->enabled() && !read)
	read = reader->read(files);
    
    if(read)
      foreach(QString file, files)
	if(!d->paths.contains(file))
	  d->paths << file;
    
    return read;
}

bool dtkAbstractData::write(QString file)
{
    bool written = false;

    foreach(dtkAbstractDataWriter *writer, d->writers)
        if(writer->enabled() && !written)
            written = writer->write(file);

    return written;
}

bool dtkAbstractData::write(QStringList files)
{
    bool written = false;

    foreach(QString file, files)
        written = written || this->write(file);

    return written;
}

dtkAbstractData *dtkAbstractData::convert(QString toType)
{
    dtkAbstractData *conversion = 0;
    foreach(dtkAbstractDataConverter *converter, d->converters)
      if(/*converter->enabled() && */!conversion && converter->canConvert (toType))
            conversion = converter->convert();

    return conversion;
}

QString dtkAbstractData::path(void)
{
    return d->path;
}

QStringList dtkAbstractData::paths(void)
{
    return d->paths;
}

QImage& dtkAbstractData::thumbnail(void) const
{
    QImage *image = new QImage(128, 128, QImage::Format_RGB32);
    
    QPainter painter(image);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::gray);
    painter.fillRect(image->rect(), Qt::black);
    
    d->thumbnails << (*image);

    return (*image);
}

QList<QImage>& dtkAbstractData::thumbnails(void) const
{
    return d->thumbnails;
}

void *dtkAbstractData::output(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

void *dtkAbstractData::data(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

void *dtkAbstractData::data(int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(channel);

    return NULL;
}

int dtkAbstractData::parameter(int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(channel);

    return -1;
}

void dtkAbstractData::setParameter(int parameter)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(parameter);
}

void dtkAbstractData::setParameter(int parameter, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(parameter);
    DTK_UNUSED(channel);
}

void dtkAbstractData::setParameter(float parameter)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(parameter);
}

void dtkAbstractData::setParameter(float parameter, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(parameter);
    DTK_UNUSED(channel);
}

void dtkAbstractData::setParameter(QString parameter)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(parameter);
}

void dtkAbstractData::setParameter(QString parameter, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(parameter);
    DTK_UNUSED(channel);
}

void dtkAbstractData::setParameter(dtkAbstractData *parameter)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(parameter);
}

void dtkAbstractData::setParameter(dtkAbstractData *parameter, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(parameter);
    DTK_UNUSED(channel);
}

void dtkAbstractData::setData(void* data)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
}

void dtkAbstractData::setData(void* data, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
}

bool dtkAbstractData::casts(QString type)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return false;
}

dtkAbstractData::operator bool (void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return false;
}

dtkAbstractData::operator int (void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 0;
}

dtkAbstractData::operator float (void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 0.0;
}

dtkAbstractData::operator double (void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 0.0;
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
