/* dtkComposerNodeVector3D.cpp ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 10:19:40 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May  3 13:22:50 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 60
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
    dtkComposerTransmitterVariant  receiver_z;

public:
    dtkComposerTransmitterEmitter<dtkVector3DReal> emitter_vec;

    dtkComposerTransmitterEmitter<qreal> emitter_x;
    dtkComposerTransmitterEmitter<qreal> emitter_y;
    dtkComposerTransmitterEmitter<qreal> emitter_z;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkComposerNodeVector3D::dtkComposerNodeVector3D(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeVector3DPrivate)
{
    this->appendReceiver(&d->receiver_vec);

    QList<QVariant::Type> variant_list;

    variant_list << QVariant::Double << QVariant::Int << QVariant::UInt << QVariant::LongLong << QVariant::ULongLong;
    d->receiver_x.setTypes(variant_list);
    d->receiver_y.setTypes(variant_list);
    d->receiver_z.setTypes(variant_list);

    this->appendReceiver(&d->receiver_x);
    this->appendReceiver(&d->receiver_y);
    this->appendReceiver(&d->receiver_z);

    this->appendEmitter(&d->emitter_vec);

    d->emitter_vec.setData(dtkVector3DReal(0, 0, 0));

    this->appendEmitter(&d->emitter_x);
    d->emitter_x.setData(0);
    this->appendEmitter(&d->emitter_y);
    d->emitter_y.setData(0);
    this->appendEmitter(&d->emitter_z);
    d->emitter_z.setData(0);
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

        dtkVector3DReal vec(d->receiver_vec.data());
        this->releaseReceivers();

        d->emitter_vec.setData(vec);
        d->emitter_x.setData(vec[0]);
        d->emitter_y.setData(vec[1]);
        d->emitter_z.setData(vec[2]);

    } else {

        dtkVector3DReal vec(qvariant_cast<qreal>(d->receiver_x.data()), qvariant_cast<qreal>(d->receiver_y.data()),qvariant_cast<qreal>(d->receiver_z.data()));
        this->releaseReceivers();

        d->emitter_vec.setData(vec);
        d->emitter_x.setData(vec[0]);
        d->emitter_y.setData(vec[1]);
        d->emitter_z.setData(vec[2]);
    }
}
