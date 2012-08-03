/* dtkComposerTransmitterUtils.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Aug  1 09:42:27 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Aug  3 23:58:24 2012 (+0200)
 *           By: tkloczko
 *     Update #: 42
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERUTILS_TPP
#define DTKCOMPOSERTRANSMITTERUTILS_TPP

#include <QSharedPointer>

// /////////////////////////////////////////////////////////////////
// Helper functions implementation
// /////////////////////////////////////////////////////////////////

template <typename T> T *dtkComposerTransmitterData(dtkComposerTransmitterReceiver<T>& receiver)
{
    T *value = receiver.data();

    switch(receiver.dataTransmission()) {
    case dtkComposerTransmitter::CopyOnWrite:
        if (receiver.copyOnWrite())
            return new T(*value);
        else
            return value;
        break;
    case dtkComposerTransmitter::Copy:
        return new T(*value);
        break;
    case dtkComposerTransmitter::Reference:
        return value;
        break;
    default:
        break;
    };

    return value;
};

template <typename T> T *dtkComposerTransmitterData(dtkComposerTransmitterVariant& receiver)
{
    T *value = receiver.data<T>();

    switch(receiver.dataTransmission()) {
    case dtkComposerTransmitter::CopyOnWrite:
        if (receiver.copyOnWrite())
            return new T(*value);
        else
            return value;
        break;
    case dtkComposerTransmitter::Copy:
        return new T(*value);
        break;
    case dtkComposerTransmitter::Reference:
        return value;
        break;
    default:
        break;
    };

    return value;
};

// template <typename T> dtkContainerVector<T> *dtkComposerTransmitterVector(dtkComposerTransmitterReceiverVector<T>& receiver)
// {
//     QSharedPointer<dtkContainerVector<T> > value = receiver.data();

//     switch(receiver.dataTransmission()) {
//     case dtkComposerTransmitter::CopyOnWrite:
//         if (receiver.copyOnWrite())
//             return new dtkContainerVector<T>(*value);
//         else
//             return value.data();
//         break;
//     case dtkComposerTransmitter::Copy:
//         return new dtkContainerVector<T>(*value);
//         break;
//     case dtkComposerTransmitter::Reference:
//         return value.data();
//         break;
//     default:
//         break;
//     };

//     return value.data();
// };

// template <typename T> dtkContainerVector<T> *dtkComposerTransmitterVector(dtkComposerTransmitterVariant& receiver)
// {
//     QSharedPointer<dtkContainerVector<T> > value = receiver.container()->vector<T>();

//     switch(receiver.dataTransmission()) {
//     case dtkComposerTransmitter::CopyOnWrite:
//         if (receiver.copyOnWrite())
//             return new T(*value);
//         else
//             return value.data();
//         break;
//     case dtkComposerTransmitter::Copy:
//         return new T(*value);
//         break;
//     case dtkComposerTransmitter::Reference:
//         return value.data();
//         break;
//     default:
//         break;
//     };

//     return value.data();
// };

// QVariant dtkComposerTransmitterVariant(dtkComposerTransmitter& receiver)
// {
//     QVariant variant 
// };

// dtkAbstractContainerWrapper *dtkComposerTransmitterContainer(dtkComposerTransmitterVariant& receiver)
// {
//     QSharedPointer<dtkAbstractContainerWrapper> value = receiver.container();

//     switch(receiver.dataTransmission()) {
//     case dtkComposerTransmitter::CopyOnWrite:
//         if (receiver.copyOnWrite())
//             return new dtkAbstractContainerWrapper(*value);
//         else
//             return value.data();
//         break;
//     case dtkComposerTransmitter::Copy:
//         return new dtkAbstractContainerWrapper(*value);
//         break;
//     case dtkComposerTransmitter::Reference:
//         return value.data();
//         break;
//     default:
//         break;
//     };

//     return value.data();
// };

#endif
