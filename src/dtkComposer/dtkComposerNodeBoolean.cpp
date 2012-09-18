/* dtkComposerNodeBoolean.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 16:49:25 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Sep 18 13:52:24 2012 (+0200)
 *           By: tkloczko
 *     Update #: 42
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeBoolean.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBooleanPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeBooleanPrivate
{
public:
    dtkComposerTransmitterVariant receiver;

public:    
    dtkComposerTransmitterEmitter<bool> emitter;

public:
    bool value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeBoolean implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeBoolean::dtkComposerNodeBoolean(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeBooleanPrivate)
{
    QList<int> variant_list;
    variant_list << QMetaType::Bool << QMetaType::Int << QMetaType::UInt << QMetaType::LongLong << QMetaType::ULongLong << QMetaType::Double << QMetaType::QString;

    d->receiver.setDataTypes(variant_list);
    this->appendReceiver(&d->receiver);

    d->value = false;
    d->emitter.setData(&d->value);
    this->appendEmitter(&d->emitter);
}

dtkComposerNodeBoolean::~dtkComposerNodeBoolean(void)
{
    delete d;
    
    d = NULL;
}

void dtkComposerNodeBoolean::run(void)
{
    if (!d->receiver.isEmpty())
        d->value = *(d->receiver.data<bool>());
}

bool dtkComposerNodeBoolean::value(void)
{
    return d->value;
}

void dtkComposerNodeBoolean::setValue(bool value)
{
    d->value = value;
}
