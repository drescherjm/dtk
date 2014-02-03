/* dtkAbstractObject_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Apr 23 10:50:52 2012 (+0200)
 * Version: $Id$
 * Last-Updated: lun. févr.  3 13:40:37 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTOBJECT_P_H
#define DTKABSTRACTOBJECT_P_H

#include "dtkCoreSupportExport.h"
#include "dtkAbstractObject.h"

#include <QtCore>

////////////////////////////////////////////////////
// dtkAbstractObjectPrivate interface
////////////////////////////////////////////////////

class DTKCORESUPPORT_EXPORT dtkAbstractObjectPrivate
{
public:
    dtkAbstractObjectPrivate(dtkAbstractObject *q = 0) : q_ptr(q) {}
    dtkAbstractObjectPrivate(dtkAbstractObject& q, const dtkAbstractObjectPrivate& other) : q_ptr(&q), 
                                                                                            values(other.values), 
                                                                                            properties(other.properties), 
                                                                                            metadatas(other.metadatas) {}

public:
    virtual ~dtkAbstractObjectPrivate(void) {}

public:
    friend class dtkAbstractObject;

public:
    dtkAbstractObject *q_ptr;

public:
    QAtomicInt count;

public:
    QHash<QString, QStringList> values;
    QHash<QString, QString> properties;

public:
    QHash<QString, QStringList> metadatas;

public:
    bool isDeferredDeletionEnabled;
};

////////////////////////////////////////////////////
// dtkAbstractObject inline methods
////////////////////////////////////////////////////

inline dtkAbstractObject::dtkAbstractObject(dtkAbstractObjectPrivate& dd, QObject *parent) : QObject(parent), d_ptr(&dd)
{

}

inline dtkAbstractObject::dtkAbstractObject(dtkAbstractObjectPrivate& dd, const dtkAbstractObject& other) : QObject(other.parent()), d_ptr(&dd)
{

}

#endif // DTKABSTRACTOBJECT_P_H
