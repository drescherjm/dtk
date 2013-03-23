/* dtkComposerTransmitterVariant.tpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Fri Mar 22 16:46:45 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 22 16:52:15 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 16
 */

/* Change Log:
 * 
 */

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant template implementation
// /////////////////////////////////////////////////////////////////

template <typename T> void dtkComposerTransmitterVariant::setData(T& data)
{
    d->variant.setValue(data);
}

template <typename T> void dtkComposerTransmitterVariant::setData(const T& data)
{
    d->variant.setValue(const_cast<T&>(data));
}

template <typename T> T dtkComposerTransmitterVariant::data(void)
{
    return dtkComposerTransmitterReceiverBase::variant().value<T>();
}

template <typename T> T dtkComposerTransmitterVariant::data(void)
{
    return dtkComposerTransmitterReceiverBase::variant().value<T>();
}
