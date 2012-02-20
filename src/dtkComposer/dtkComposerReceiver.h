/* dtkComposerReceiver.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 11:39:15 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 20 15:41:07 2012 (+0100)
 *           By: tkloczko
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERRECEIVER_H
#define DTKCOMPOSERRECEIVER_H

#include "dtkComposerTransmitter.h"

#include <QtCore>

template <typename T> class dtkComposerEmitter;

// /////////////////////////////////////////////////////////////////
// dtkComposerReceiver declaration
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCOMPOSER_EXPORT dtkComposerReceiver : public dtkComposerTransmitter
{
public:
     dtkComposerReceiver(dtkComposerNode *parent = 0);
    ~dtkComposerReceiver(void);

public:
    inline void connect(dtkComposerEmitter<T> *emitter);

    inline       T& data(void);
    inline const T& data(void) const;

public:
    bool isEmpty(void) const;

public:
    QString identifier(void) const;

public:
    bool connect(dtkComposerTransmitter *transmitter);

    Chains rightChains(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

private:
    QList<dtkComposerEmitter<T> *> emitters;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerReceiver implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerReceiver.tpp"

#endif
