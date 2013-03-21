/* dtkComposerTransmitterEmitter.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 09:39:35 2013 (+0100)
 * Version: 
 * Last-Updated: Thu Mar 21 16:56:41 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 71
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkComposerTransmitter.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterBase
// /////////////////////////////////////////////////////////////////

class  dtkComposerTransmitterEmitterBase : public dtkComposerTransmitter
{
public:
            dtkComposerTransmitterEmitterBase(dtkComposerNode *parent = 0);
    virtual ~dtkComposerTransmitterEmitterBase(void);

public:
    inline void clearData(void);

public:
    inline bool enableCopy(void);

public:
    inline void setData(const QVariant& data);

public:
    LinkMap leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterEmitter : public dtkComposerTransmitterEmitterBase
{
public:
      dtkComposerTransmitterEmitter(dtkComposerNode *parent = 0);
     ~dtkComposerTransmitterEmitter(void);

public:
    dtkComposerTransmitter::Kind kind(void) const;

    QString kindName(void) const;

public:
    inline void setData(const T& data);
    inline void setData(      T& data);

public:
    using dtkComposerTransmitterEmitterBase::d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterEmitter.tpp"

