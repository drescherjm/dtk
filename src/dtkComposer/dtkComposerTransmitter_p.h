/* dtkComposerTransmitter_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Mar 12 11:43:28 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 21 09:40:20 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 90
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
    dtkComposerTransmitterPrivate(dtkComposerNode *parent) {
	active = true;
	required = true;
	parent = parent;
	data_transmission = dtkComposerTransmitter::AutoCopy;
	type = 0;
	}

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

public:
    //const dtkComposerType *data_type;
    int type;

public:
    QVariant variant;

public:
    dtkComposerTransmitter::DataTransmission data_transmission;
};

