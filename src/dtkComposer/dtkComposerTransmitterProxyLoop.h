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

// ///////////////////////////////////////////////////////////////////
// dtkComposerTransmitterProxyLoop
// ///////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerTransmitterProxyLoop : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterProxyLoop(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterProxyLoop(void);

public:
    dtkComposerTransmitter::Kind kind(void) const;

    QString kindName(void) const;

public:
    bool enableCopy(void);

public:
    QVariant variant(void);
    void setVariant(const QVariant&);

public:
    QVariantList allData(void);

public:
    void  enableLoopMode(void);
    void disableLoopMode(void);

public:
    void setTwin(dtkComposerTransmitterProxyLoop *twin);

    dtkComposerTransmitterProxyLoop *twin(void) const;

public:
    bool    connect(dtkComposerTransmitter *transmitter);
    bool disconnect(dtkComposerTransmitter *transmitter);

    bool enableConnection(dtkComposerTransmitter *transmitter);

public:
    LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

private:
    void setTypeList(const TypeList& list) {;}

private:
    dtkComposerTransmitter *m_source;
    dtkComposerTransmitterProxyLoop *m_twin;
};

// ///////////////////////////////////////////////////////////////////
// Implementations
// ///////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterProxyLoop.tpp"

// 
// dtkComposerTransmitterProxyLoop.h ends here
