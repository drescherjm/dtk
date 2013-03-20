/* dtkComposerNodeString.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: 2013 Mon Jan 14 12:33:32 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 62
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeString.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

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
    QVector<const dtkComposerType*> variant_list;

    variant_list << dtkComposerTypeInfo<int*>::type() << dtkComposerTypeInfo<uint*>::type() << dtkComposerTypeInfo<qlonglong*>::type() << dtkComposerTypeInfo<qulonglong*>::type() 
                 << dtkComposerTypeInfo<bool*>::type() << dtkComposerTypeInfo<QString*>::type() << dtkComposerTypeInfo<double*>::type();

    d->receiver.setDataTypes(variant_list);
    this->appendReceiver(&(d->receiver));

    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeString::~dtkComposerNodeString(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeString::run(void)
{
    if (!d->receiver.isEmpty())
        d->value = d->receiver.data<QString>();

    d->emitter.setData(d->value);
}

QString dtkComposerNodeString::value(void)
{
    return d->value;
}
   
void dtkComposerNodeString::setValue(QString value)
{
    d->value = value;
}
