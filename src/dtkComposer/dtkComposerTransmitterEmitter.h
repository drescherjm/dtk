// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:


#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerTransmitter.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterBase
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerTransmitterEmitterBase : public dtkComposerTransmitter
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
    virtual bool enableConnection(dtkComposerTransmitter *transmitter);

public:
    LinkMap leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterVariant 
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerTransmitterEmitterVariant : public dtkComposerTransmitterEmitterBase
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

public:
    bool enableConnection(dtkComposerTransmitter *transmitter);

private:
    void setTypeList(const TypeList& list) {;}

public:
    using dtkComposerTransmitterEmitterBase::d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterEmitter.tpp"

// 
// dtkComposerTransmitterEmitter.h ends here
