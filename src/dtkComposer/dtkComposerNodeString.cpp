/* dtkComposerNodeString.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:38:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr  3 10:48:15 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 71
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
    dtkComposerTransmitterReceiver<QString> receiver;

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
        d->value = d->receiver.data();

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








// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringListPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringListPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> receiver;
    dtkComposerTransmitterReceiver<qlonglong> receiver_size;
    dtkComposerTransmitterReceiver<QStringList> receiver_list;

public:
    dtkComposerTransmitterEmitter<QStringList> emitter;

public:
    QStringList value;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringList implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeStringList::dtkComposerNodeStringList(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringListPrivate)
{
    this->appendReceiver(&(d->receiver_list));
    this->appendReceiver(&(d->receiver_size));
    this->appendReceiver(&(d->receiver));

    d->emitter.setData(d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeStringList::~dtkComposerNodeStringList(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeStringList::run(void)
{
    if (!d->receiver_list.isEmpty()) {
        d->value = d->receiver_list.data();
    } else {
        d->value.clear();
    }

    if (!d->receiver.isEmpty()) {
        qlonglong size = 1;
        if (!d->receiver_size.isEmpty())
            size = d->receiver_size.data();
        for (qlonglong i = 0; i< size; ++i){
            d->value.append(d->receiver.data());
        }
    }
}

QStringList dtkComposerNodeStringList::value(void)
{
    return d->value;
}

void dtkComposerNodeStringList::setValue(QStringList value)
{
    d->value = value;
}

