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
#include "dtkComposerTransmitterHandler.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverBase inline implementation
// /////////////////////////////////////////////////////////////////

inline bool dtkComposerTransmitterReceiverBase::enableCopy(void)
{
    if (d->active_emitter)
        return d->active_emitter->enableCopy();

    return false;
}

inline QVariant dtkComposerTransmitterReceiverBase::variant(void)
{
    if (d->active_emitter)
	return d->active_emitter->variant();

    return d->variant;
}

inline QVariantList dtkComposerTransmitterReceiverBase::allData(void)
{
    QVariantList list;

    foreach(dtkComposerTransmitter *e, d->emitters) {
	if (e->active())
	    list << e->variant();
    }

    return list;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverVariant template implementation
// /////////////////////////////////////////////////////////////////

template <typename T> inline T dtkComposerTransmitterReceiverVariant::data(void)
{
    return dtkComposerTransmitterHandler<T>::data(*this);
}

template <typename T> inline T dtkComposerTransmitterReceiverVariant::constData(void)
{
    return dtkComposerTransmitterHandler<T>::constData(*this);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver implementation
// /////////////////////////////////////////////////////////////////

//! Constructs a receiver.
/*! 
 *  Initialize the type of the receiver and the variant that it contains.
 */
template <typename T> inline dtkComposerTransmitterReceiver<T>::dtkComposerTransmitterReceiver(dtkComposerNode *parent) : dtkComposerTransmitterReceiverBase(parent)
{
    dtkComposerTransmitterHandler<T>::init(*this);
}

template <typename T> inline dtkComposerTransmitterReceiver<T>::~dtkComposerTransmitterReceiver(void)
{

}

template <typename T> inline T dtkComposerTransmitterReceiver<T>::data(void)
{
    return dtkComposerTransmitterHandler<T>::data(*this);
}

template <typename T> inline T dtkComposerTransmitterReceiver<T>::constData(void)
{
    return dtkComposerTransmitterHandler<T>::constData(*this);
}

template <typename T> inline int dtkComposerTransmitterReceiver<T>::type(void) const
{
    return d->type_list.first();
}

template <typename T> inline void dtkComposerTransmitterReceiver<T>::setTypeList(const TypeList&) 
{
    // Forbiden method.
}

// 
// dtkComposerTransmitterReceiver.tpp ends here
