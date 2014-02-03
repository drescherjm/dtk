/* @(#)dtkComposerNodeStringOperator.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/23 09:24:08
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerMetatype.h"

#include "dtkComposerNodeStringOperator.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorUnary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorUnaryPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> receiver;

public:
    dtkComposerTransmitterEmitter<QString> emitter;

public:
    QString value;
};

dtkComposerNodeStringOperatorUnary::dtkComposerNodeStringOperatorUnary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorUnaryPrivate)
{
    this->appendReceiver(&(d->receiver));

    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeStringOperatorUnary::~dtkComposerNodeStringOperatorUnary(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinary
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorBinaryPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> receiver_lhs;
    dtkComposerTransmitterReceiver<QString> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<QString> emitter;

public:
    QString value;
};

dtkComposerNodeStringOperatorBinary::dtkComposerNodeStringOperatorBinary(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorBinaryPrivate)
{
    this->appendReceiver(&(d->receiver_lhs));
    this->appendReceiver(&(d->receiver_rhs));

    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeStringOperatorBinary::~dtkComposerNodeStringOperatorBinary(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinaryLogic
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringOperatorBinaryLogicPrivate
{
public:
    dtkComposerTransmitterReceiver<QString> receiver_lhs;
    dtkComposerTransmitterReceiver<QString> receiver_rhs;

public:
    dtkComposerTransmitterEmitter<bool> emitter;

public:
    bool value;
};

dtkComposerNodeStringOperatorBinaryLogic::dtkComposerNodeStringOperatorBinaryLogic(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringOperatorBinaryLogicPrivate)
{
    this->appendReceiver(&(d->receiver_lhs));
    this->appendReceiver(&(d->receiver_rhs));

    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeStringOperatorBinaryLogic::~dtkComposerNodeStringOperatorBinaryLogic(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinary - Append
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeStringOperatorBinaryAppend::run(void)
{
    d->value = *(d->receiver_lhs.data()) + *(d->receiver_rhs.data());
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringOperatorBinaryLogic - Equality
// /////////////////////////////////////////////////////////////////

void dtkComposerNodeStringOperatorBinaryLogicEquality::run(void)
{
    d->value = (*(d->receiver_lhs.data()) == *(d->receiver_rhs.data()));
}








// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringListAppend
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringListAppendPrivate
{
public:
    dtkComposerTransmitterReceiver<QStringList> receiver_list;
    dtkComposerTransmitterReceiver<QString> receiver_string;

public:
    dtkComposerTransmitterEmitter<QStringList> emitter;

public:
    QStringList list;
};

dtkComposerNodeStringListAppend::dtkComposerNodeStringListAppend(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringListAppendPrivate)
{
    this->appendReceiver(&(d->receiver_list));
    this->appendReceiver(&(d->receiver_string));

    d->emitter.setData(&d->list);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeStringListAppend::~dtkComposerNodeStringListAppend(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeStringListAppend::run(void)
{
    if (!d->receiver_list.isEmpty() && !d->receiver_string.isEmpty() ) {
        d->list = *(d->receiver_list.data());
        d->list.append(*(d->receiver_string.data()));
    } else if (d->receiver_list.isEmpty() && !d->receiver_string.isEmpty() ) {
        d->list.clear();
        d->list.append(*(d->receiver_string.data()));
    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter.clearData();
    }
}


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringListExtract
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringListExtractPrivate
{
public:
    dtkComposerTransmitterReceiver<QStringList> receiver_list;
    dtkComposerTransmitterReceiver<qlonglong> receiver_index;

public:
    dtkComposerTransmitterEmitter<QString> emitter;

public:
    QString value;
};

dtkComposerNodeStringListExtract::dtkComposerNodeStringListExtract(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringListExtractPrivate)
{
    this->appendReceiver(&(d->receiver_list));
    this->appendReceiver(&(d->receiver_index));

    d->emitter.setData(&d->value);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeStringListExtract::~dtkComposerNodeStringListExtract(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeStringListExtract::run(void)
{
    if (!d->receiver_list.isEmpty() && !d->receiver_index.isEmpty() ) {
        QStringList *list = d->receiver_list.data();
        d->value = list->at(*(d->receiver_index.data()));
    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter.clearData();
    }
}


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeStringListSet
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeStringListSetPrivate
{
public:
    dtkComposerTransmitterReceiver<QStringList> receiver_list;
    dtkComposerTransmitterReceiver<qlonglong> receiver_index;
    dtkComposerTransmitterReceiver<QString> receiver_value;

public:
    dtkComposerTransmitterEmitter<QStringList> emitter;

public:
    QStringList list;
};

dtkComposerNodeStringListSet::dtkComposerNodeStringListSet(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeStringListSetPrivate)
{
    this->appendReceiver(&(d->receiver_list));
    this->appendReceiver(&(d->receiver_index));
    this->appendReceiver(&(d->receiver_value));

    d->emitter.setData(&d->list);
    this->appendEmitter(&(d->emitter));
}

dtkComposerNodeStringListSet::~dtkComposerNodeStringListSet(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeStringListSet::run(void)
{
    if (!d->receiver_list.isEmpty() && !d->receiver_value.isEmpty()&& !d->receiver_index.isEmpty()  ) {
        d->list = *(d->receiver_list.data());
        qlonglong index = *(d->receiver_index.data());
         if (index >= 0 && index < d->list.size())
             d->list.replace(index, *(d->receiver_value.data()));
         else
             dtkWarn() << "bad index value in set string list" << index;
    } else {
        dtkWarn() << "Inputs not specified. Nothing is done";
        d->emitter.clearData();
    }

}

