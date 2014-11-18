// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:


#include "dtkComposerTransmitter_p.h"
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

bool dtkComposerTransmitterEmitterBase::enableConnection(dtkComposerTransmitter *transmitter)
{
    bool enable_connection = true;

    if (!d->type_list.isEmpty()) {
	QVariant var;
	dtkComposerTransmitter::TypeList list = transmitter->typeList();
	int count = d->type_list.count();
	int i = 0;
	while(enable_connection && i < count) {
	    var = QVariant(d->type_list.at(i++), 0);
	    foreach(int t, list) {
		if (!var.canConvert(t)) {
		    enable_connection = false;
		    break;
		}
	    }
	}
    }

    return enable_connection;
}

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

// 
// dtkComposerTransmitterEmitter.cpp ends here
