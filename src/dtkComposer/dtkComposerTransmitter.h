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
#include "dtkComposerMetaType.h"

#include <QtCore>

class dtkComposerNode;
class dtkComposerTransmitterPrivate;
class dtkComposerTransmitterLink;
class dtkComposerTransmitterLinkList;
class dtkComposerTransmitterVariant;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerTransmitter
{
public:
    enum Kind {
        Emitter,
        Receiver,
        Proxy,
        ProxyLoop,
        ProxyVariant
    };

public:
    enum DataTransmission {
        AutoCopy,
        Copy,
        Reference
    };

public:
    typedef QList<int> TypeList;

public:
             dtkComposerTransmitter(dtkComposerNode *parent = 0);
    virtual ~dtkComposerTransmitter(void);

#pragma mark -
#pragma mark Mandatory specific properties

public:
    virtual Kind kind(void) const = 0;

    virtual QString kindName(void) const = 0;

#pragma mark -
#pragma mark Static properties

public:
    void setParentNode(dtkComposerNode *parent);

    dtkComposerNode *parentNode(void) const;

public:
    void setDataTransmission(DataTransmission value);

    DataTransmission dataTransmission(void) const;

public:
    void setRequired(bool required);

    bool required(void);

#pragma mark -
#pragma mark Dynamic behaviour

public:
    void clearData(void);

public:
    bool isEmpty(void) const;

public:
    bool active(void);

    virtual void setActive(bool active);

    void activateEmitter(dtkComposerTransmitter *emitter);

public:
    virtual bool enableCopy(void);

public:
    void setTypeList(const TypeList& list);

    TypeList typeList(void) const;

public:
    virtual QVariant variant(void);

    virtual QVariantList allData(void);

#pragma mark -
#pragma mark Connection management

public:
    void appendNext(dtkComposerTransmitter *transmitter);
    void removeNext(dtkComposerTransmitter *transmitter);

    void appendPrevious(dtkComposerTransmitter *transmitter);
    void removePrevious(dtkComposerTransmitter *transmitter);

public:
    virtual bool    connect(dtkComposerTransmitter *transmitter);
    virtual bool disconnect(dtkComposerTransmitter *transmitter);

    virtual bool enableConnection(dtkComposerTransmitter *transmitter);

public:
    void appendReceiver(dtkComposerTransmitter *receiver);
    void removeReceiver(dtkComposerTransmitter *receiver);

public:
    int receiverCount(void);

#pragma mark -
#pragma mark Link management

public:
    typedef QMultiHash<dtkComposerTransmitter *, dtkComposerTransmitterLink *> LinkMap;

public:
    virtual LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    virtual LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

public:
    static bool onTransmittersConnected(dtkComposerTransmitter *source, dtkComposerTransmitter *destination, dtkComposerTransmitterLinkList& valid_links, dtkComposerTransmitterLinkList& invalid_links);
    static bool onTransmittersDisconnected(dtkComposerTransmitter *source, dtkComposerTransmitter *destination, dtkComposerTransmitterLinkList& invalid_links);

public:
    template <typename T> friend class dtkComposerTransmitterHandler;
                          friend class dtkComposerTransmitterHandlerVariant;

private:
    friend QDebug operator << (QDebug debug, const dtkComposerTransmitter& transmitter);
    friend QDebug operator << (QDebug debug,       dtkComposerTransmitter *transmitter);

protected:
    dtkComposerTransmitterPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

QDebug operator << (QDebug debug, const dtkComposerTransmitter& transmitter);
QDebug operator << (QDebug debug,       dtkComposerTransmitter *transmitter);

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterLink declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterLinkPrivate;

class DTKCOMPOSER_EXPORT dtkComposerTransmitterLink
{
public:
     dtkComposerTransmitterLink(dtkComposerTransmitter *source, dtkComposerTransmitter *destination);
    ~dtkComposerTransmitterLink(void);

public:
    dtkComposerTransmitter *source();
    dtkComposerTransmitter *destination();

private:
    dtkComposerTransmitterLinkPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterLinkList declaration
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerTransmitterLinkList : public QList<dtkComposerTransmitterLink *> {};

//
// dtkComposerTransmitter.h ends here
