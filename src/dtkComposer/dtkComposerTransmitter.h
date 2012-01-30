/* dtkComposerTransmitter.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 10:59:27 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 11:21:40 2012 (+0100)
 *           By: tkloczko
 *     Update #: 9
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

class QDebug;
class QString;

// /////////////////////////////////////////////////////////////////
// dtkComposerAbstractTransmitter declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerAbstractTransmitterPrivate;

class DTKCOMPOSER_EXPORT dtkComposerAbstractTransmitter
{
public:
             dtkComposerAbstractTransmitter(void);
    virtual ~dtkComposerAbstractTransmitter(void);

public:
    virtual QString identifier(void) const = 0;
    
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

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter declaration
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCOMPOSER_EXPORT dtkComposerTransmitter : public dtkComposerAbstractTransmitter
{
public:
     dtkComposerTransmitter(void);
    ~dtkComposerTransmitter(void);

public:
    QString identifier(void) const;

public:
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitter.tpp"

#endif
