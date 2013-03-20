/* dtkComposerTransmitter_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Mar 12 11:43:28 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 20 13:00:06 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 71
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTER_P_H
#define DTKCOMPOSERTRANSMITTER_P_H

#include "dtkComposerTransmitter.h"
#include "dtkComposerVariant.h"

#include <QtCore>

class dtkComposerNode;
class dtkAbstractObject;
class dtkAbstractContainerWrapper;
template <typename T> class dtkMatrix;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterPrivate
{
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
    const dtkComposerType *data_type;

public:
    dtkComposerVariant variant;

public:
    dtkAbstractContainerWrapper *container;

public:
    dtkComposerTransmitter::DataTransmission data_transmission;
};

#endif
