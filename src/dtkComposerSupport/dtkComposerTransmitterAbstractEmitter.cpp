/* dtkComposerTransmitterAbstractEmitter.cpp --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: 2012 Thu Oct 11 10:50:38 (+0200)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitterAbstractEmitter.h"

#include <dtkCoreSupport/dtkGlobal>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterAbstractEmitter implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterAbstractEmitter::dtkComposerTransmitterAbstractEmitter(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{

}
 
dtkComposerTransmitterAbstractEmitter::~dtkComposerTransmitterAbstractEmitter(void)
{

}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterAbstractEmitter::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;    
}

/*! 
    \fn bool dtkComposerTransmitterAbstractEmitter::enableCopy(void)
  
    Returns true when the emitter is connected to more than one
    receiver.
  
    When several receivers are connected to the emitter, some nodes
    receiving the data can modify it while others only read
    it. According to the order of such operations, the data can be
    modified before it is read leading to unexpected behaviors.
  
    To circumvent this issue, the emitter informs the receivers that
    they must copy the data if they modify it ensuring that the
    original data is not corrupted for the other nodes.
*/
