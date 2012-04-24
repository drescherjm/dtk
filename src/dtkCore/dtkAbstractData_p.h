/* dtkAbstractData_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Apr 23 12:12:08 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 11:25:07 2012 (+0200)
 *           By: tkloczko
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATA_P_H
#define DTKABSTRACTDATA_P_H

#include "dtkCoreExport.h"
#include "dtkAbstractObject_p.h"

class dtkAbstractData;

////////////////////////////////////////////////////
// dtkAbstractDataPrivate interface
////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkAbstractDataPrivate : public dtkAbstractObjectPrivate
{
    DTK_DECLARE_PUBLIC(dtkAbstractData);

public:
    dtkAbstractDataPrivate(dtkAbstractData *q = 0) : dtkAbstractObjectPrivate(q) {}
    dtkAbstractDataPrivate(const dtkAbstractDataPrivate& other) : dtkAbstractObjectPrivate(other), 
                                                                  readers(other.readers),
                                                                  writers(other.writers),
                                                                  converters(other.converters),
                                                                  serializers(other.serializers),
                                                                  deserializers(other.deserializers),
                                                                  path(other.path),
                                                                  paths(other.paths),
                                                                  numberOfChannels(other.numberOfChannels),
                                                                  thumbnails(other.thumbnails) {}

public:
    virtual ~dtkAbstractDataPrivate(void) {}

public:
    QMap<QString, bool> readers;
    QMap<QString, bool> writers;
    QMap<QString, bool> converters;
    QMap<QString, bool> serializers;
    QMap<QString, bool> deserializers;

public:
    QString     path;
    QStringList paths;

public:
    int numberOfChannels;

public:
    QList<QImage> thumbnails;
};

////////////////////////////////////////////////////
// dtkAbstractData protected constructors
////////////////////////////////////////////////////

DTK_IMPLEMENT_PRIVATE(dtkAbstractData, dtkAbstractObject);

#endif
