/* dtkComposerTransmitter.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:59:27 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 17:07:35 2012 (+0100)
 *           By: tkloczko
 *     Update #: 23
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

class dtkComposerNode;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter declaration
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCOMPOSER_EXPORT dtkComposerTransmitter : public dtkComposerAbstractTransmitter
{
public:
     dtkComposerTransmitter(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitter(void);

public:
    QString identifier(void) const;

public:
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitter.tpp"

#endif
