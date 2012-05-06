/* dtkAbstractContainer.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 15:25:17 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Sun May  6 19:03:08 2012 (+0200)
 *           By: tkloczko
 *     Update #: 47
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTCONTAINER_H
#define DTKABSTRACTCONTAINER_H

#include "dtkCoreExport.h"
#include "dtkAbstractData.h"

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainer interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkAbstractContainer : public dtkAbstractData
{
    Q_OBJECT

public:
    enum Type {
        Vector,
        List
    };

public:
             dtkAbstractContainer(dtkAbstractData *parent = 0);
             dtkAbstractContainer(const dtkAbstractContainer& other);
    virtual ~dtkAbstractContainer(void);

public:
    dtkAbstractContainer& operator = (const dtkAbstractContainer& other);

public:
    virtual Type type(void) const = 0;

public:
    virtual void clear(void) = 0;

    virtual void  append(const QVariant& data) = 0;
    virtual void prepend(const QVariant& data) = 0;
    virtual void  remove(const QVariant& data) = 0;

    virtual void  insert(const QVariant& data, dtkxarch_int index) = 0;
    virtual void replace(const QVariant& data, dtkxarch_int index) = 0;

    virtual void resize(dtkxarch_int size) = 0;

public:
    virtual bool  isEmpty(void) const = 0;

    virtual bool contains(const QVariant& data) const = 0;

    virtual dtkxarch_int count(void) const = 0;

    virtual dtkxarch_int indexOf(const QVariant& data, dtkxarch_int from = 0) const = 0;
     
    virtual QVariant    at(dtkxarch_int index) const = 0; 
    virtual QVariant first(void) const = 0;
    virtual QVariant  last(void) const = 0;

public:
    virtual bool operator != (const dtkAbstractContainer& other) const = 0;
    virtual bool operator == (const dtkAbstractContainer& other) const = 0;

    virtual QVariant operator[] (dtkxarch_int index) const = 0;
};

#endif
