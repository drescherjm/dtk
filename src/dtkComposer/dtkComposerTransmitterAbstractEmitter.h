/* dtkComposerTransmitterAbstractEmitter.h --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: 2012 Thu Oct 11 10:43:43 (+0200)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERABSTRACTEMITTER_H
#define DTKCOMPOSERTRANSMITTERABSTRACTEMITTER_H


#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitter_p.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterAbstractEmitter interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerTransmitterAbstractEmitter : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterAbstractEmitter(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterAbstractEmitter(void);

public:
    inline bool enableCopy(void);

public:
    LinkMap leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterAbstractEmitter inline method
// /////////////////////////////////////////////////////////////////

bool dtkComposerTransmitterAbstractEmitter::enableCopy(void)
{
    return (d->receivers.count() > 1);
}

#endif
