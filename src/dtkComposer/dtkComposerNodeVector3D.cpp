/* dtkComposerNodeVector3D.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 10:19:40 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 13 14:34:23 2012 (+0200)
 *           By: tkloczko
 *     Update #: 75
 */

/* Commentary: 
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeVector3D.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVector3DPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkVector3DReal> receiver_vec;

    dtkComposerTransmitterVariant receiver_x;
    dtkComposerTransmitterVariant receiver_y;
    dtkComposerTransmitterVariant receiver_z;

public:
    dtkComposerTransmitterEmitter<dtkVector3DReal> emitter_vec;

    dtkComposerTransmitterEmitter<qreal> emitter_x;
    dtkComposerTransmitterEmitter<qreal> emitter_y;
    dtkComposerTransmitterEmitter<qreal> emitter_z;

public:
    dtkVector3DReal *vector;
    qreal x;
    qreal y;
    qreal z;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVector3D::dtkComposerNodeVector3D(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DPrivate)
{
    d->vector = NULL;
    d->x = 0.;
    d->y = 0.;
    d->z = 0.;

    this->appendReceiver(&d->receiver_vec);

    QList<QVariant::Type> variant_list;
    variant_list << QVariant::Double << QVariant::LongLong;
    d->receiver_x.setTypes(variant_list);
    d->receiver_y.setTypes(variant_list);
    d->receiver_z.setTypes(variant_list);

    this->appendReceiver(&d->receiver_x);
    this->appendReceiver(&d->receiver_y);
    this->appendReceiver(&d->receiver_z);

    this->appendEmitter(&d->emitter_vec);

    d->emitter_x.setData(&d->x);
    this->appendEmitter(&d->emitter_x);
    d->emitter_y.setData(&d->y);
    this->appendEmitter(&d->emitter_y);
    d->emitter_z.setData(&d->z);
    this->appendEmitter(&d->emitter_z);
}

dtkComposerNodeVector3D::~dtkComposerNodeVector3D(void)
{
    delete d;
    
    d = NULL;
}

QString dtkComposerNodeVector3D::inputLabelHint(int port) 
{
    switch(port) {
    case 0:
        return "vector";
        break;
    case 1:
        return "x";
        break;
    case 2:
        return "y";
        break;
    case 3:
        return "z";
        break;
    default:
        break;
    }

    return "port";
}

QString dtkComposerNodeVector3D::outputLabelHint(int port)
{    
    switch(port) {
    case 0:
        return "vector";
        break;
    case 1:
        return "x";
        break;
    case 2:
        return "y";
        break;
    case 3:
        return "z";
        break;
    default:
        break;
    }

    return "port";
}

void dtkComposerNodeVector3D::run(void)
{
    if (!d->receiver_vec.isEmpty()) {

        d->vector = d->receiver_vec.data();
        d->x = (*d->vector)[0];
        d->y = (*d->vector)[1];
        d->z = (*d->vector)[2];

    } else {

        if (!d->vector)
            d->vector = new dtkVector3DReal();  

        if (!d->receiver_x.isEmpty())
            d->x = *d->receiver_x.data<qreal>();

        if (!d->receiver_y.isEmpty())
            d->y = *d->receiver_y.data<qreal>();

        if (!d->receiver_z.isEmpty())
            d->z = *d->receiver_z.data<qreal>();
        
        (*d->vector)[0] = d->x;
        (*d->vector)[1] = d->y;
        (*d->vector)[2] = d->z;
    }

    d->emitter_vec.setData(d->vector);
}
