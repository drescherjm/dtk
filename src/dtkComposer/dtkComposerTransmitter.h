/* dtkComposerTransmitter.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:36:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jun  1 14:09:35 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 168
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTER_H
#define DTKCOMPOSERTRANSMITTER_H

#include "dtkComposerExport.h"

#include <QtCore>

class dtkAbstractContainerWrapper;
class dtkComposerNode;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterPrivate;
class dtkComposerTransmitterLink;
class dtkComposerTransmitterLinkList;

class DTKCOMPOSER_EXPORT dtkComposerTransmitter
{
public:
    enum Kind {
        Emitter,
        Receiver,
        Proxy,
        Variant,
        VariantContainer,
        EmitterVector,
        ReceiverVector
    };

public:
             dtkComposerTransmitter(dtkComposerNode *parent = 0);
    virtual ~dtkComposerTransmitter(void);

public:
    virtual Kind kind(void) const = 0;

    virtual QString kindName(void) const = 0;

public:
          QVariant& variant(void);
    const QVariant& variant(void) const;

public:
    virtual       dtkAbstractContainerWrapper& container(void);
    virtual const dtkAbstractContainerWrapper& container(void) const;

public:
    virtual QVariant::Type type(void) const;

public:
    QString typeName(void) const;

public:
    void setParentNode(dtkComposerNode *parent);

    dtkComposerNode *parentNode(void) const;

public:
    virtual void setActive(bool active);

    bool active(void);

public:
    virtual void setActiveEmitter(dtkComposerTransmitter *emitter);

public:
    void setRequired(bool required);

    bool required(void);

public:
    void appendNext(dtkComposerTransmitter *transmitter);
    void removeNext(dtkComposerTransmitter *transmitter);
    
    void appendPrevious(dtkComposerTransmitter *transmitter);
    void removePrevious(dtkComposerTransmitter *transmitter);

public:
    virtual bool    connect(dtkComposerTransmitter *transmitter);
    virtual bool disconnect(dtkComposerTransmitter *transmitter);

public:
    void appendReceiver(dtkComposerTransmitter *receiver);
    void removeReceiver(dtkComposerTransmitter *receiver);

public:
    int receiverCount(void);

public:
    virtual void clear(void);

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
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug, const dtkComposerTransmitter& transmitter);
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug,       dtkComposerTransmitter *transmitter);

protected:
    dtkComposerTransmitterPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug, const dtkComposerTransmitter& transmitter);
DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug,       dtkComposerTransmitter *transmitter);

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

#endif
