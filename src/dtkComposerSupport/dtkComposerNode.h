/* dtkComposerNode.h ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 14:24:23 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. janv.  8 01:01:31 2015 (+0100)
 *           By: etienne
 *     Update #: 61
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerSupportExport.h"

#include <QtCore>

class dtkComposerTransmitter;

// /////////////////////////////////////////////////////////////////
// dtkComposerNode declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNode
{
public:
             dtkComposerNode(void);
    virtual ~dtkComposerNode(void);

public:
    void appendEmitter(dtkComposerTransmitter *emitter);
    void removeEmitter(dtkComposerTransmitter *emitter);

    dtkComposerTransmitter *removeEmitter(int index);

    void appendReceiver(dtkComposerTransmitter *receiver);
    void removeReceiver(dtkComposerTransmitter *receiver);

    dtkComposerTransmitter *removeReceiver(int index);

    QList<dtkComposerTransmitter *> emitters(void);
    QList<dtkComposerTransmitter *> receivers(void);

public:
    virtual QString type(void) = 0;

public:
    virtual QString titleHint(void);
    QString title(void) const;

public:
    virtual QString  inputLabelHint(int port);
    virtual QString outputLabelHint(int port);

public:
    void setTitleHint(const QString& hint);
    void setTitle(const QString& title);

public:
    void  setInputLabelHint(const QString& hint, int port);
    void setOutputLabelHint(const QString& hint, int port);

private:
    dtkComposerNodePrivate *d;
};
