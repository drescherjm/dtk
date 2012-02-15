/* dtkComposerReceiver.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 11:39:15 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 08:56:39 2012 (+0100)
 *           By: tkloczko
 *     Update #: 12
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

#include <QList>

class QString;

template <typename T> class dtkComposerEmitter;

// /////////////////////////////////////////////////////////////////
// dtkComposerReceiver declaration
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCOMPOSER_EXPORT dtkComposerReceiver : public dtkComposerTransmitter
{
public:
     dtkComposerReceiver(dtkComposerSceneNode *parent = 0);
    ~dtkComposerReceiver(void);

public:
    inline void connect(dtkComposerEmitter<T> *emitter);

    inline       T& data(void);
    inline const T& data(void) const;

public:
    bool isEmpty(void) const;

public:
    QString identifier(void) const;

private:
    QList<dtkComposerEmitter<T> *> emitters;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerReceiver implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerReceiver.tpp"

#endif
