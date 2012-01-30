/* dtkComposerNode.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 14:50:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 16:49:54 2012 (+0100)
 *           By: tkloczko
 *     Update #: 43
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODE_H
#define DTKCOMPOSERNODE_H

#include "dtkComposerExport.h"

#include <QObject>

class dtkComposerAbstractTransmitter;
class dtkComposerNodePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNode : public QObject
{
    Q_OBJECT

public:
             dtkComposerNode(void);
    virtual ~dtkComposerNode(void);

    virtual QString identifier(void) const = 0;

public:
    void appendEmitter(dtkComposerAbstractTransmitter *emitter);
    void removeEmitter(dtkComposerAbstractTransmitter *emitter);
    void removeEmitter(int index);

    dtkComposerAbstractTransmitter *emitter(int index);

    virtual void setReceiver(dtkComposerAbstractTransmitter *transmitter);

public:
    virtual void run(void) = 0;

public:
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode& node);
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode *node);

private:
    dtkComposerNodePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode& node);
DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode *node);

#endif
