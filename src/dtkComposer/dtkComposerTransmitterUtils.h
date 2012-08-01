/* dtkComposerTransmitterUtils.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Aug  1 09:35:38 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Aug  1 09:43:48 2012 (+0200)
 *           By: tkloczko
 *     Update #: 5
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

// /////////////////////////////////////////////////////////////////
// Helper functions interfaces
// /////////////////////////////////////////////////////////////////

template <typename T> T *dtkComposerTransmitterValue(const dtkComposerTransmitterReceiver<T>& receiver);
template <typename T> T *dtkComposerTransmitterValue(const dtkComposerTransmitterVariant&     receiver);

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterUtils.tpp"

#endif
