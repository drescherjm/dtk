/* dtkComposerNode.h --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 14:24:23 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 14 16:47:15 2012 (+0100)
 *           By: David Rey
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODE_H
#define DTKCOMPOSERNODE_H

#include "dtkComposerExport.h"

#include <QList>

class dtkComposerTransmitter;

// /////////////////////////////////////////////////////////////////
// dtkComposerNode declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNode
{
public: 
             dtkComposerNode(void);
    virtual ~dtkComposerNode(void);

public:
    void appendEmitter(dtkComposerTransmitter *emitter);
    void removeEmitter(dtkComposerTransmitter *emitter);

    void appendReceiver(dtkComposerTransmitter *receiver);
    void removeReceiver(dtkComposerTransmitter *receiver);

    QList<dtkComposerTransmitter *> emitters(void);
    QList<dtkComposerTransmitter *> receivers(void);

private:
    dtkComposerNodePrivate *d;
};

#endif
