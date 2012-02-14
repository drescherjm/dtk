/* dtkComposerTransmitter.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:36:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 14 14:29:59 2012 (+0100)
 *           By: David Rey
 *     Update #: 18
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

class dtkComposerSceneNode;
class QDebug;
class QString;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterPrivate;

class DTKCOMPOSER_EXPORT dtkComposerTransmitter
{
public:
             dtkComposerTransmitter(dtkComposerSceneNode *parent = 0);
    virtual ~dtkComposerTransmitter(void);

public:
    virtual QString identifier(void) const = 0;

public:
    dtkComposerSceneNode *parentNode(void) const;

public:
    void   activate(void);
    void inactivate(void);

    bool active(void);
    
    void setRequired(bool required);

    bool required(void);

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

#endif
