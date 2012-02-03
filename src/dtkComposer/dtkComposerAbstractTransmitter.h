/* dtkComposerAbstractTransmitter.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:36:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  3 14:08:23 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERABSTRACTTRANSMITTER_H
#define DTKCOMPOSERABSTRACTTRANSMITTER_H

#include "dtkComposerExport.h"

#include <QObject>

class dtkComposerSceneNode;

// /////////////////////////////////////////////////////////////////
// dtkComposerAbstractTransmitter declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerAbstractTransmitterPrivate;

class DTKCOMPOSER_EXPORT dtkComposerAbstractTransmitter
{
public:
             dtkComposerAbstractTransmitter(dtkComposerSceneNode *parent = 0);
    virtual ~dtkComposerAbstractTransmitter(void);

public:
    virtual QString identifier(void) const = 0;

public:
    dtkComposerSceneNode *parentNode(void) const;
    
public:
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug, const dtkComposerAbstractTransmitter& transmitter);
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug,       dtkComposerAbstractTransmitter *transmitter);

private:
    dtkComposerAbstractTransmitterPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug, const dtkComposerAbstractTransmitter& transmitter);
DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug,       dtkComposerAbstractTransmitter *transmitter);

#endif
