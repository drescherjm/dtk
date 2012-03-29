/* dtkComposerTransmitterEmitter.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:33:49 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 29 10:53:59 2012 (+0200)
 *           By: tkloczko
 *     Update #: 57
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTEREMITTER_H
#define DTKCOMPOSERTRANSMITTEREMITTER_H

#include "dtkComposerTransmitter.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter declaration
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCOMPOSER_EXPORT dtkComposerTransmitterEmitter : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterEmitter(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterEmitter(void);

public:
    inline void setData(const T& data);

    inline T data(void);

public:
    Kind kind(void) const;

    QString kindName(void) const;

public:
    LinkMap leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

private:
    T m_data;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterEmitter.tpp"

#endif
