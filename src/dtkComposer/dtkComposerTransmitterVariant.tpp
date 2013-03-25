/* dtkComposerTransmitterVariant.tpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Fri Mar 22 16:46:45 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 09:20:13 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 20
 */

/* Change Log:
 * 
 */

#include "dtkComposerTransmitter_p.h"

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
    return dtkComposerTransmitter::variant().value<T>();
}

template <typename T> T dtkComposerTransmitterVariant::constData(void)
{
    return dtkComposerTransmitter::variant().value<T>();
}
