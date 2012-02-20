/* dtkComposerTransmitter.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:36:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 20 17:04:22 2012 (+0100)
 *           By: tkloczko
 *     Update #: 65
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
    typedef QMultiHash<dtkComposerTransmitter *, dtkComposerTransmitterLink *> LinkMap;

public:
             dtkComposerTransmitter(dtkComposerNode *parent = 0);
    virtual ~dtkComposerTransmitter(void);

public:
    virtual QString identifier(void) const = 0;

public:
    dtkComposerNode *parentNode(void) const;

public:
    void   setActive(bool active);
    void setRequired(bool required);

    bool   active(void);
    bool required(void);

public:
    virtual bool connect(dtkComposerTransmitter *transmitter);

    virtual LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    virtual LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

public:
    static bool onTransmittersConnected(dtkComposerTransmitter *source, dtkComposerTransmitter *destination, dtkComposerTransmitterLinkList& valid_links, dtkComposerTransmitterLinkList& invalid_links);

public:
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug, const dtkComposerTransmitter& transmitter);
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug,       dtkComposerTransmitter *transmitter);

private:
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

class DTKCOMPOSER_EXPORT dtkComposerTransmitterLinkList : public QList<dtkComposerTransmitterLink *>
{
public:
};

#endif
