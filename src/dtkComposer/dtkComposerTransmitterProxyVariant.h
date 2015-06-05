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
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterProxyVariant
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerTransmitterProxyVariant : public dtkComposerTransmitter
{
public:    
     dtkComposerTransmitterProxyVariant(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterProxyVariant(void);

public:
    void enableReceiver(void);
    void  enableEmitter(void);

public:
    QVariant variant(void);

public:
    QVariantList allData(void);

public:
    QVariant data(void);

public:
    template <typename T> T      data(void);
    template <typename T> T constData(void);

public:
    void setVariant(const QVariant& variant);

public:
    template <typename T> void setData(const T& data);
    template <typename T> void setData(      T& data);

public:
    dtkComposerTransmitter::Kind kind(void) const;

    QString kindName(void) const;

public:
    bool enableCopy(void);

public:
    bool enableConnection(dtkComposerTransmitter *transmitter);

public:
    bool    connect(dtkComposerTransmitter *transmitter);
    bool disconnect(dtkComposerTransmitter *transmitter);

public:
    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

private:
    dtkComposerTransmitterReceiverVariant m_receiver;
    dtkComposerTransmitterEmitterVariant  m_emitter;
    dtkComposerTransmitter *m_transmitter;
};

// /////////////////////////////////////////////////////////////////

inline QVariant dtkComposerTransmitterProxyVariant::data(void)
{
    return m_receiver.data();
}

template <typename T> inline T dtkComposerTransmitterProxyVariant::data(void)
{
    return m_receiver.data<T>();
}

template <typename T> inline T dtkComposerTransmitterProxyVariant::constData(void)
{
    return m_receiver.constData<T>();
}

inline void dtkComposerTransmitterProxyVariant::setVariant(const QVariant& variant)
{
    m_emitter.setVariant(variant);
}

template <typename T> inline void dtkComposerTransmitterProxyVariant::setData(const T& data)
{
    m_emitter.setData(data);
}

template <typename T> inline void dtkComposerTransmitterProxyVariant::setData(T& data)
{
    m_emitter.setData(data);
}

// 
// dtkComposerTransmitterProxyVariant.h ends here
