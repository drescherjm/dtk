/* dtkComposerNodeData.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/29 11:17:21
 * Version: $Id$
 * Last-Updated: mar. févr.  4 17:24:31 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 301
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

#include <dtkCoreSupport/dtkAbstractData>

#include <dtkLog/dtkLogger.h>

#include <dtkMathSupport/dtkVector.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeDataPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeDataPrivate
{
public:
    dtkComposerTransmitterEmitter<dtkAbstractData> receiver_data;
    dtkComposerTransmitterReceiver<QString> receiver_string;
    dtkComposerTransmitterReceiver<dtkVectorReal> receiver_vector;

public:
    dtkComposerTransmitterEmitter<dtkAbstractData> emitter_data;

public:
    dtkAbstractData *data;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeData implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeData::dtkComposerNodeData(void) : dtkComposerNodeLeafData(), d(new dtkComposerNodeDataPrivate)
{
    this->appendReceiver(&(d->receiver_string));
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
   
bool dtkComposerNodeData::isAbstractData(void) const 
{
    return true; 
}

QString dtkComposerNodeData::abstractDataType(void) const 
{ 
    return "dtkAbstractData"; 
}

void dtkComposerNodeData::run(void)
{
    if (this->implementationHasChanged())
        d->data = this->data();

    if (!d->data) {
        dtkWarn() << "no data, abort "<< this->currentImplementation();
        return;
    }

    if (!d->receiver_string.isEmpty())
        d->data->setParameter(*d->receiver_string.data());

    if(!d->receiver_vector.isEmpty())
        d->data->setParameter(*d->receiver_vector.data());

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
        return "string";
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
