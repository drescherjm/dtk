/* dtkComposerTransmitter.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:59:27 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  2 17:05:02 2012 (+0100)
 *           By: tkloczko
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTER_H
#define DTKCOMPOSERTRANSMITTER_H

#include "dtkComposerAbstractTransmitter.h"

#include <QSharedData>
#include <QSharedDataPointer>

class dtkComposerNode;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter declaration
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterPrivate : public QSharedData
{
public:
    T data;
 };

template <typename T> class DTKCOMPOSER_EXPORT dtkComposerTransmitter : public dtkComposerAbstractTransmitter
{
public:
     dtkComposerTransmitter(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitter(void);

public:
    inline void setData(const T& data);

    inline       T& data(void);
    inline const T& data(void) const;

public:
    QString identifier(void) const;

private:
    QSharedDataPointer<dtkComposerTransmitterPrivate<T> > d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitter.tpp"

#endif
