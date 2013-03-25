/* dtkComposerNodeBoolean.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 16:49:25 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 25 09:05:06 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 56
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
    dtkComposerTransmitterReceiverVariant receiver;

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
    dtkComposerTransmitter::TypeList type_list;
    type_list << QMetaType::Bool;// << dtkComposerTypeInfo<int*>::type() << dtkComposerTypeInfo<uint*>::type() 
    //<< dtkComposerTypeInfo<qlonglong*>::type() << dtkComposerTypeInfo<double*>::type() << dtkComposerTypeInfo<QString*>::type();

    d->receiver.setTypeList(type_list);
    this->appendReceiver(&d->receiver);

    d->value = false;
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
        d->value = (d->receiver.data<bool>());

    d->emitter.setData(d->value);
}

bool dtkComposerNodeBoolean::value(void)
{
    return d->value;
}

void dtkComposerNodeBoolean::setValue(bool value)
{
    d->value = value;
}
