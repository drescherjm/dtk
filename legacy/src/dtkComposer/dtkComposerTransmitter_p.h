/* dtkComposerTransmitter_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Mar 12 11:43:28 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. sept. 17 14:27:14 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 52
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
    int data_type;

public:
    QVariant variant;

public:
    dtkAbstractObject *object;

public:
    dtkMatrix<double> *matrix;

public:
    dtkAbstractContainerWrapper *container;

public:
    dtkComposerTransmitter::DataTransmission data_transmission;

public:
    bool ready;
    QAtomicInt copy_counter;
};

#endif
