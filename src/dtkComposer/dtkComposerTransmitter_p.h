/* dtkComposerTransmitter_p.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Mar 12 11:43:28 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. nov. 13 10:13:58 2014 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 106
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerTransmitter.h"

#include <QtCore>

class dtkComposerNode;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterPrivate
{
public:
    dtkComposerTransmitterPrivate(dtkComposerNode *p) : active(true),
        required(true),
        parent(p),
        active_emitter(0),
        data_transmission(dtkComposerTransmitter::AutoCopy) {}

public:
    bool active;
    bool required;

public:
    dtkComposerNode *parent;

public:
    QList<dtkComposerTransmitter *>     next_list;
    QList<dtkComposerTransmitter *> previous_list;

public:
    QList<dtkComposerTransmitter *> receivers;
    QList<dtkComposerTransmitter *>  emitters;

public:
    dtkComposerTransmitter *active_emitter;

public:
    dtkComposerTransmitter::TypeList type_list;

public:
    QVariant variant;
    QVariant swap;

public:
    dtkComposerTransmitter::DataTransmission data_transmission;
};

