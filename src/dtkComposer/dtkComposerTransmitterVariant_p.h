/* dtkComposerTransmitterVariant_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Aug  3 14:36:46 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Aug  3 14:38:07 2012 (+0200)
 *           By: tkloczko
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_P_H
#define DTKCOMPOSERTRANSMITTERVARIANT_P_H

#include <QtCore>

class dtkComposerTransmitter;
class dtkComposerTransmitterVariant;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariantPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterVariantPrivate
{
public:
    QList<dtkComposerTransmitter *> emitters;
    QList<dtkComposerTransmitterVariant *> variants;

public:
    dtkComposerTransmitter        *active_emitter;
    dtkComposerTransmitterVariant *active_variant;

public:
    QList<QVariant::Type> types;

public:
    dtkComposerTransmitterVariant *twin;

    bool twinned;
};

#endif
