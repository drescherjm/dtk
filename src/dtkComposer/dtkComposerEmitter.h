/* dtkComposerEmitter.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:33:49 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 14 11:37:29 2012 (+0100)
 *           By: tkloczko
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREMITTER_H
#define DTKCOMPOSEREMITTER_H

#include "dtkComposerTransmitter.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerEmitter declaration
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCOMPOSER_EXPORT dtkComposerEmitter : public dtkComposerTransmitter
{
public:
     dtkComposerEmitter(dtkComposerSceneNode *parent = 0);
    ~dtkComposerEmitter(void);

public:
    inline void setData(const T& data);

    inline       T& data(void);
    inline const T& data(void) const;

public:
    QString identifier(void) const;

private:
    T m_data;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerEmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerEmitter.tpp"

#endif
