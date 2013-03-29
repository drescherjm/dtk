/* dtkComposerTransmitterReceiver.tpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 13:53:01 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 29 14:16:31 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 210
 */

/* Change Log:
 * 
 */

#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterHandler.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverBase inline implementation
// /////////////////////////////////////////////////////////////////

bool dtkComposerTransmitterReceiverBase::enableCopy(void)
{
    if (d->active_emitter)
        return d->active_emitter->enableCopy();

    return false;
}

QVariant dtkComposerTransmitterReceiverBase::variant(void)
{
    if (d->active_emitter)
	return d->active_emitter->variant();

    return d->variant;
}

QVariantList dtkComposerTransmitterReceiverBase::allData(void)
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

template <typename T> T dtkComposerTransmitterReceiverVariant::data(void)
{
    return dtkComposerTransmitterHandler<T>::data(*this);
}

template <typename T> T dtkComposerTransmitterReceiverVariant::constData(void)
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
template <typename T> dtkComposerTransmitterReceiver<T>::dtkComposerTransmitterReceiver(dtkComposerNode *parent) : dtkComposerTransmitterReceiverBase(parent)
{
    dtkComposerTransmitterHandler<T>::init(*this);
}

template <typename T> dtkComposerTransmitterReceiver<T>::~dtkComposerTransmitterReceiver(void)
{

}

template <typename T> T dtkComposerTransmitterReceiver<T>::data(void)
{
    return dtkComposerTransmitterHandler<T>::data(*this);
}

template <typename T> T dtkComposerTransmitterReceiver<T>::constData(void)
{
    return dtkComposerTransmitterHandler<T>::constData(*this);
}

template <typename T> int dtkComposerTransmitterReceiver<T>::type(void) const
{
    return d->type_list.first();
}

