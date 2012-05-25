/* dtkAbstractContainerWrapper.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May 23 17:46:55 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri May 25 09:56:29 2012 (+0200)
 *           By: tkloczko
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTCONTAINERWRAPPER_H
#define DTKABSTRACTCONTAINERWRAPPER_H

#include "dtkAbstractContainer.h"
#include "dtkContainerExport.h"
#include <dtkCore/dtkAbstractData>

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainerWrapper interface
// /////////////////////////////////////////////////////////////////

class DTKCONTAINER_EXPORT dtkAbstractContainerWrapper : public dtkAbstractData
{
    Q_OBJECT

public:
    enum Type {
        None,
        Vector
    };

public:
             dtkAbstractContainerWrapper(dtkAbstractData *parent = 0);
             dtkAbstractContainerWrapper(const dtkAbstractContainerWrapper& other);
    virtual ~dtkAbstractContainerWrapper(void);

protected:
    void init(void);

public:
    void reset(void);

public:
    dtkAbstractContainerWrapper& operator = (const dtkAbstractContainerWrapper& other);

public:
    virtual dtkAbstractContainerWrapper *clone(void) const;

public:
    QString identifier(void) const;

public:
    void setName(const QString& name);

    QString name(void) const;

public:
    virtual Type type(void) const;

public:
    virtual void clear(void);

    virtual void  append(const QVariant& data);
    virtual void prepend(const QVariant& data);
    virtual void  remove(const QVariant& data);

    virtual void  insert(const QVariant& data, dtkxarch_int index);
    virtual void replace(const QVariant& data, dtkxarch_int index);

    virtual void resize(dtkxarch_int size);

public:
    virtual bool isEmpty(void) const;

    virtual bool contains(const QVariant& data) const;

    virtual dtkxarch_int count(void) const;

    virtual dtkxarch_int indexOf(const QVariant& data, dtkxarch_int from = 0) const;
     
    virtual QVariant at(dtkxarch_int index) const;

public:
    bool operator != (const dtkAbstractContainerWrapper& other) const;
    bool operator == (const dtkAbstractContainerWrapper& other) const;

public:
    virtual bool isEqual(const dtkAbstractContainerWrapper& other) const;

private:
    dtkAbstractContainerWrapper *m_container;
};

Q_DECLARE_METATYPE(dtkAbstractContainerWrapper);
Q_DECLARE_METATYPE(dtkAbstractContainerWrapper *);

#endif
