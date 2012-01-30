/* dtkComposerAbstractTransmitter.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:36:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 16:50:47 2012 (+0100)
 *           By: tkloczko
 *     Update #: 4
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

class dtkComposerNode;

// /////////////////////////////////////////////////////////////////
// dtkComposerAbstractTransmitter declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerAbstractTransmitterPrivate;

class DTKCOMPOSER_EXPORT dtkComposerAbstractTransmitter : public QObject
{
    Q_OBJECT

public:
             dtkComposerAbstractTransmitter(dtkComposerNode *parent = 0);
    virtual ~dtkComposerAbstractTransmitter(void);

public:
    virtual QString identifier(void) const = 0;

public:
    dtkComposerNode *parentNode(void) const;
    
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
