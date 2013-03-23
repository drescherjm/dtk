/* dtkComposerTransmitterHandler.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 15:22:41 2013 (+0100)
 * Version: 
 * Last-Updated: Sat Mar 23 22:40:45 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 64
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkCore/dtkCore.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterHandler
{
public:
    static inline T      data(dtkComposerTransmitter& t);
    static inline T constData(dtkComposerTransmitter& t);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterHandler<T *>
{
public:
    static inline T      *data(dtkComposerTransmitter& t);
    static inline T *constData(dtkComposerTransmitter& t);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler pointer specialization
// /////////////////////////////////////////////////////////////////

template <typename T, bool U> class dtkComposerTransmitterCopier
{
public:
    static inline T *copy(T *source, QVariant& target);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler dtkCoreObject specialization
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterHandlerCopier<T, true>
{
public:
    static inline T *copy(T *source, QVariant& target);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterHandler implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterHandler.tpp"
