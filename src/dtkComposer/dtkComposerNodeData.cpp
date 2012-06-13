/* dtkComposerNodeData.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/29 11:17:21
 * Version: $Id$
 * Last-Updated: Thu May 31 01:16:54 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 276
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeData.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkCore>

#include <dtkLog/dtkLog.h>

#include <dtkMath/dtkVector.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeDataPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeDataPrivate
{
public:
    dtkComposerTransmitterEmitter<dtkAbstractData *> receiver_data;
    dtkComposerTransmitterReceiver<QString> receiver_type;
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;

public:
    dtkComposerTransmitterEmitter<dtkAbstractData *> emitter_data;

public:
    dtkAbstractData *data;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeData implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeData::dtkComposerNodeData(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeDataPrivate)
{
    this->appendReceiver(&(d->receiver_type));
    this->appendReceiver(&(d->receiver_data));
    this->appendReceiver(&(d->receiver_vector));

    this->appendEmitter(&(d->emitter_data));

    d->data = NULL;
}

dtkComposerNodeData::~dtkComposerNodeData(void)
{
    if (d->data)
        delete d->data;

    delete d;

    d = NULL;
}

void dtkComposerNodeData::run(void)
{
    if (d->receiver_type.isEmpty()) {
        dtkWarn() << "no type speficied in data node!";
        return;
    }

    if(!d->data)
        d->data = dtkAbstractDataFactory::instance()->create(d->receiver_type.data());

    if (!d->data) {
        dtkWarn() << "no data, abort "<<  d->receiver_type.data();
        return;
    }

    if(!d->receiver_vector.isEmpty())
        d->data->setParameter(d->receiver_vector.data());

    d->data->update();

    d->emitter_data.setData(d->data);
}

QString dtkComposerNodeData::type(void)
{
    return "data";
}

QString dtkComposerNodeData::titleHint(void)
{
    return "Data";
}

QString dtkComposerNodeData::inputLabelHint(int port)
{
    switch (port) {
    case 0:
        return "type";
    case 1:
        return "data";
    case 2:
        return "vector";
    default:
        return dtkComposerNodeLeaf::inputLabelHint(port);
    }
}

QString dtkComposerNodeData::outputLabelHint(int port)
{
    switch (port) {
    case 0:
        return "data";
    default:
        return dtkComposerNodeLeaf::outputLabelHint(port);
    }
}
