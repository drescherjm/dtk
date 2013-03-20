/* dtkComposerTransmitterAbstractReceiver.h --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: 2012 Thu Oct 11 12:19:59 (+0200)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERABSTRACTRECEIVER_H
#define DTKCOMPOSERTRANSMITTERABSTRACTRECEIVER_H


#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitter_p.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterAbstractReceiver interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerTransmitterAbstractReceiver : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterAbstractReceiver(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterAbstractReceiver(void);

public:
    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
};

#endif
