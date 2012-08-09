/* dtkComposerTransmitterVariant_p.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Aug  3 14:36:46 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  9 16:01:36 2012 (+0200)
 *           By: tkloczko
 *     Update #: 9
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

    bool already_ask;
    
public:
    bool      value_b;
    qlonglong value_i;
    qreal     value_r;
    QString   value_s;

public:
    QVariant m_variant;
};

#endif
