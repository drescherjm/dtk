/* dtkComposerTransmitterEmitter.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:33:49 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May 23 18:39:59 2012 (+0200)
 *           By: tkloczko
 *     Update #: 78
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

#include <dtkContainer/dtkContainerVector.h>

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

    inline       T& data(void);
    inline const T& data(void) const;

public:
    inline void setVector(const dtkContainerVector<T>& vector);

    inline       dtkContainerVector<T>& vector(void);
    inline const dtkContainerVector<T>& vector(void) const;

/* public: */
/*     inline void setList(const dtkContainerList<T>& list); */

/*     inline       dtkContainerList<T>& list(void); */
/*     inline const dtkContainerList<T>& list(void) const; */

public:
    Kind kind(void) const;

    QString kindName(void) const;

public:
    LinkMap leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

private:
    T m_data;
    
    dtkContainerVector<T> m_vector;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterEmitter.tpp"

#endif
