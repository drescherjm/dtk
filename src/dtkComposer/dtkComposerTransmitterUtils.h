/* dtkComposerTransmitterUtils.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Aug  1 09:35:38 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Aug  3 12:26:06 2012 (+0200)
 *           By: tkloczko
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERUTILS_H
#define DTKCOMPOSERTRANSMITTERUTILS_H

#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkContainer>

// /////////////////////////////////////////////////////////////////
// Helper functions interfaces
// /////////////////////////////////////////////////////////////////

template <typename T> T *dtkComposerTransmitterData(dtkComposerTransmitterReceiver<T>& receiver);
template <typename T> T *dtkComposerTransmitterData(dtkComposerTransmitterVariant&     receiver);

/* template <typename T> dtkContainerVector<T> *dtkComposerTransmitterVector(dtkComposerTransmitterReceiverVector<T>& receiver); */
/* template <typename T> dtkContainerVector<T> *dtkComposerTransmitterVector(dtkComposerTransmitterVariant& receiver); */

/* QVariant dtkComposerTransmitterVariant(dtkComposerTransmitter& receiver); */

/* dtkAbstractContainerWrapper *dtkComposerTransmitterContainer(dtkComposerTransmitterVariant& receiver); */

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterUtils.tpp"

#endif
