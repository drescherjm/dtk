/* dtkComposerTransmitterEmitter.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 09:39:35 2013 (+0100)
 * Version: 
 * Last-Updated: Sat Mar 23 23:11:19 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 86
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
    dtkComposerTransmitter::Kind kind(void) const;

    QString kindName(void) const;

public:
    inline bool enableCopy(void);

public:
    LinkMap leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterVariant 
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterEmitterVariant : public dtkComposerTransmitterEmitterBase
{
public:
     dtkComposerTransmitterEmitterVariant(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterEmitterVariant(void);

public:
    inline void setVariant(const QVariant& variant);

public:
    template <typename T> inline void setData(const T& data);
    template <typename T> inline void setData(      T& data);
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
    inline void setData(const T& data);
    inline void setData(      T& data);

public:
    inline int type(void) const;

private:
    void setTypeList(const TypeList& list) {;}

public:
    using dtkComposerTransmitterEmitterBase::d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterEmitter.tpp"

