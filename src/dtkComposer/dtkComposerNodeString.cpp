/* dtkComposerNodeString.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  4 01:20:24 2012 (+0200)
 *           By: tkloczko
 *     Update #: 53
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerMetatype.h"

#include "dtkComposerNodeString.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterUtils.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringPrivate
{
public:
    dtkComposerTransmitterVariant receiver;

public:
    dtkComposerTransmitterEmitter<QString> emitter;

public:
    QString value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeString implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeString::dtkComposerNodeString(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringPrivate)
{
    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong << QVariant::Double << QVariant::String;

    d->receiver.setTypes(variant_list);
    this->appendReceiver(&(d->receiver));

    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeString::~dtkComposerNodeString(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeString::run(void)
{
    if (!d->receiver.isEmpty()) {
        if (d->receiver.type() == QVariant::String) {
            d->value = *dtkComposerTransmitterData<QString>(d->receiver);
        } else if (d->receiver.type() == QVariant::Double) {
            d->value.setNum(*dtkComposerTransmitterData<double>(d->receiver));
        } else {
            d->value.setNum(*dtkComposerTransmitterData<qlonglong>(d->receiver));
        }
    }
}

QString dtkComposerNodeString::value(void)
{
    return d->value;
}
   
void dtkComposerNodeString::setValue(QString value)
{
    d->value = value;
}
