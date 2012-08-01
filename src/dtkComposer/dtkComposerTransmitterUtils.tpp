/* dtkComposerTransmitterUtils.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Aug  1 09:42:27 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Aug  1 09:43:14 2012 (+0200)
 *           By: tkloczko
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERUTILS_TPP
#define DTKCOMPOSERTRANSMITTERUTILS_TPP

// /////////////////////////////////////////////////////////////////
// Helper functions implementation
// /////////////////////////////////////////////////////////////////

template <typename T> T *dtkComposerTransmitterValue(const dtkComposerTransmitterReceiver<T>& receiver)
{
    T *value = receiver.data();

    switch(receiver.dataTransmission()) {
    case dtkComposerTransmitter::Reference:
        return value;
        break;
    case dtkComposerTransmitter::Copy:
        return new T(*value);
        break;
    case dtkComposerTransmitter::CopyOnWrite:
        if (receiver.copyOnWrite())
            return new T(*value);
        else
            return value;
        break;
    default:
        break;
    };

    return value;
};

template <typename T> T *dtkComposerTransmitterValue(const dtkComposerTransmitterVariant& receiver)
{
    T *value = qvariant_cast<T*>(receiver.data());

    switch(receiver.dataTransmission()) {
    case dtkComposerTransmitter::Reference:
        return value;
        break;
    case dtkComposerTransmitter::Copy:
        return new T(*value);
        break;
    case dtkComposerTransmitter::CopyOnWrite:
        if (receiver.copyOnWrite())
            return new T(*value);
        else
            return value;
        break;
    default:
        break;
    };

    return value;
};

#endif
