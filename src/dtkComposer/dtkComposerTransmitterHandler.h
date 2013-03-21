/* dtkComposerTransmitterHandler.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 15:22:41 2013 (+0100)
 * Version: 
 * Last-Updated: Thu Mar 21 16:17:29 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 27
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkCore/dtkCore.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler
// /////////////////////////////////////////////////////////////////

template <typename T, bool U> 
class dtkComposerTransmitterHandler<T*, U>
{
public:
    static inline T *copyData(const QVariant& source, QVariant& target, bool enable_copy);
};

template <typename T> 
class dtkComposerTransmitterHandler<T*, true>
{
public:
    static inline T *copyData(const QVariant& source, QVariant& target, bool enable_copy);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterHandler.tpp"
