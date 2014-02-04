/* dtkComposerNode.h --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 14:24:23 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 10 15:07:28 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 93
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <dtkCore>

#include <QtCore>

class dtkComposerNodePrivate;
class dtkComposerTransmitter;

// /////////////////////////////////////////////////////////////////
// dtkComposerNode
// /////////////////////////////////////////////////////////////////

class dtkComposerNode
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

public:
    virtual QString  inputLabelHint(int port);
    virtual QString outputLabelHint(int port);

public:
    void setTitleHint(const QString& hint);

public:
    void  setInputLabelHint(const QString& hint, int port);
    void setOutputLabelHint(const QString& hint, int port);

private:
    dtkComposerNodePrivate *d;
};
