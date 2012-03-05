/* dtkComposerTransmitterReceiver.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 11:39:15 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar  4 16:50:54 2012 (+0100)
 *           By: tkloczko
 *     Update #: 44
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERRECEIVER_H
#define DTKCOMPOSERTRANSMITTERRECEIVER_H

#include "dtkComposerTransmitter.h"

#include <QtCore>

template <typename T> class dtkComposerTransmitterEmitter;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver declaration
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCOMPOSER_EXPORT dtkComposerTransmitterReceiver : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterReceiver(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterReceiver(void);

public:
    inline       T& data(void);
    inline const T& data(void) const;

public:
    bool isEmpty(void) const;

public:
    Kind           kind(void) const;
    QVariant::Type type(void) const;

    QString kindName(void) const;
    QString typeName(void) const;
    
public:
          void *variant(void);
    const void *variant(void) const;

public:
    bool    connect(dtkComposerTransmitter *transmitter);
    bool disconnect(dtkComposerTransmitter *transmitter);

    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

private:
    QList<dtkComposerTransmitterEmitter<T> *> emitters;
    QList<dtkComposerTransmitter *> variants;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterReceiver.tpp"

#endif
