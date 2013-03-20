/* dtkComposerNodeVector3D.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 10:19:40 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Mon Jan  7 11:54:33 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 104
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
    dtkComposerTransmitterReceiver<dtkVector3DReal*> receiver_vec;

    dtkComposerTransmitterVariant receiver_x;
    dtkComposerTransmitterVariant receiver_y;
    dtkComposerTransmitterVariant receiver_z;

public:
    dtkComposerTransmitterEmitter<dtkVector3DReal*> emitter_vec;

    dtkComposerTransmitterEmitter<qreal> emitter_x;
    dtkComposerTransmitterEmitter<qreal> emitter_y;
    dtkComposerTransmitterEmitter<qreal> emitter_z;

public:
    dtkVector3DReal *vector;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVector3D::dtkComposerNodeVector3D(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DPrivate)
{
    d->vector = NULL;

    this->appendReceiver(&d->receiver_vec);

    QVector<const dtkComposerType*> variant_list;
    variant_list << dtkComposerTypeInfo<double>::type() << dtkComposerTypeInfo<qlonglong>::type();
    d->receiver_x.setDataTypes(variant_list);
    d->receiver_y.setDataTypes(variant_list);
    d->receiver_z.setDataTypes(variant_list);

    this->appendReceiver(&d->receiver_x);
    this->appendReceiver(&d->receiver_y);
    this->appendReceiver(&d->receiver_z);

    this->appendEmitter(&d->emitter_vec);

    this->appendEmitter(&d->emitter_x);
    this->appendEmitter(&d->emitter_y);
    this->appendEmitter(&d->emitter_z);
}

dtkComposerNodeVector3D::~dtkComposerNodeVector3D(void)
{
    if (d->vector)
        delete d->vector;

    d->vector = NULL;

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

        dtkVector3DReal *vector = d->receiver_vec.constData();

        if (!vector) {
            dtkError() << "dtkComposerNodeVector3D::" << Q_FUNC_INFO << "Input vector is not defined.";
            d->emitter_x.clearData();
            d->emitter_y.clearData();
            d->emitter_z.clearData();
            d->emitter_vec.clearData();
            return;
        }

        d->emitter_x.setData( (*vector)[0] );
        d->emitter_y.setData( (*vector)[1] );
        d->emitter_z.setData( (*vector)[2] );

        d->emitter_vec.setData(vector);

    } else {

        if(!d->vector)
            d->vector = new dtkVector3DReal();

        if(!d->receiver_x.isEmpty())
            (*d->vector)[0] = d->receiver_x.data<qreal>();
        else
            (*d->vector)[0] = 0.;

        if(!d->receiver_y.isEmpty())
            (*d->vector)[1] = d->receiver_y.data<qreal>();
        else
            (*d->vector)[1] = 0.;

        if(!d->receiver_z.isEmpty())
            (*d->vector)[2] = d->receiver_z.data<qreal>();
        else
            (*d->vector)[2] = 0.;

        d->emitter_x.setData( (*d->vector)[0] );
        d->emitter_y.setData( (*d->vector)[1] );
        d->emitter_z.setData( (*d->vector)[2] );

        d->emitter_vec.setData(d->vector);
    }
}
