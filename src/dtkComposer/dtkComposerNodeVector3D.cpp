/* dtkComposerNodeVector3D.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 10:19:40 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 27 17:57:25 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 50
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

    dtkComposerTransmitterReceiver<qreal> receiver_x;
    dtkComposerTransmitterReceiver<qreal> receiver_y;
    dtkComposerTransmitterReceiver<qreal> receiver_z;

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

        d->emitter_vec.setData(vec);
        d->emitter_x.setData(vec[0]);
        d->emitter_y.setData(vec[1]);
        d->emitter_z.setData(vec[2]);

    } else {

        dtkVector3DReal vec(d->receiver_x.data(), d->receiver_y.data(), d->receiver_z.data());

        d->emitter_vec.setData(vec);
        d->emitter_x.setData(vec[0]);
        d->emitter_y.setData(vec[1]);
        d->emitter_z.setData(vec[2]);

    }
}
