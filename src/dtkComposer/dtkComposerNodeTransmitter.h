/* dtkComposerNodeTransmitter.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Nov  2 09:44:16 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov  2 14:33:51 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 35
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODETRANSMITTER_H
#define DTKCOMPOSERNODETRANSMITTER_H

#include "dtkComposerExport.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeAbstractTransmitter declaration
// /////////////////////////////////////////////////////////////////

#include <dtkCore/dtkGlobal>

class QDebug;
class QString;

class DTKCOMPOSER_EXPORT dtkComposerNodeAbstractTransmitter
{
public:
    virtual ~dtkComposerNodeAbstractTransmitter(void) {;}

public:
    virtual void setCurrentData(dtkxarch_int index) = 0;

    virtual void clear(void) = 0;

    virtual QString identifier(void) const = 0;

public:
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug, const dtkComposerNodeAbstractTransmitter& transmitter);
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug,       dtkComposerNodeAbstractTransmitter *transmitter);
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug, const dtkComposerNodeAbstractTransmitter& transmitter);
DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug,       dtkComposerNodeAbstractTransmitter *transmitter);

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeTransmitter declaration
// /////////////////////////////////////////////////////////////////

template <typename T> class QVector;
template <typename T> class QList;

template <typename T> class DTKCOMPOSER_EXPORT dtkComposerNodeTransmitter : public dtkComposerNodeAbstractTransmitter
{
public:
     dtkComposerNodeTransmitter(void);
    ~dtkComposerNodeTransmitter(void);

public:
    void setData(const T& data);

          T& data(void);
    const T& data(void) const;

public:
    void setVector(QVector<T> *vector);
    void   setList(  QList<T> *list);

    QVector<T> *vector(void);
      QList<T> *list(void);

public:
    void setCurrentData(dtkxarch_int index);

    void clear(void);

    QString identifier(void) const;

private:
            T   m_data;
    QVector<T> *m_vector;
      QList<T> *m_list;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeTransmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerNodeTransmitter.tpp"

#endif
