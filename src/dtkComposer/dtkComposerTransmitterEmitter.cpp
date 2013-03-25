/* dtkComposerTransmitterEmitter.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 10:15:56 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 09:15:07 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 14
 */

/* Change Log:
 * 
 */

#include "dtkComposerTransmitterEmitter.h"

// ///////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterBase implementation
// ///////////////////////////////////////////////////////////////////

dtkComposerTransmitterEmitterBase::dtkComposerTransmitterEmitterBase(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{

}
 
dtkComposerTransmitterEmitterBase::~dtkComposerTransmitterEmitterBase(void)
{

}

dtkComposerTransmitter::Kind dtkComposerTransmitterEmitterBase::kind(void) const
{
    return dtkComposerTransmitter::Emitter;
};

QString dtkComposerTransmitterEmitterBase::kindName(void) const
{
    return "Emitter";
};

dtkComposerTransmitter::LinkMap dtkComposerTransmitterEmitterBase::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    Q_UNUSED(transmitter);

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

// ///////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterVariant implementation
// ///////////////////////////////////////////////////////////////////

dtkComposerTransmitterEmitterVariant::dtkComposerTransmitterEmitterVariant(dtkComposerNode *parent) : dtkComposerTransmitterEmitterBase(parent)
{

}
 
dtkComposerTransmitterEmitterVariant::~dtkComposerTransmitterEmitterVariant(void)
{

}
