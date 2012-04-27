/* dtkComposerNodeQuaternion.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 13:06:02 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 27 17:57:10 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeQuaternion.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkMath>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeQuaternionPrivate
{
public:
    dtkComposerTransmitterReceiver<dtkQuaternionReal> receiver_quat;

    dtkComposerTransmitterReceiver<qreal> receiver_q0;
    dtkComposerTransmitterReceiver<qreal> receiver_q1;
    dtkComposerTransmitterReceiver<qreal> receiver_q2;
    dtkComposerTransmitterReceiver<qreal> receiver_q3;

public:
    dtkComposerTransmitterEmitter<dtkQuaternionReal> emitter_quat;

    dtkComposerTransmitterEmitter<qreal> emitter_q0;
    dtkComposerTransmitterEmitter<qreal> emitter_q1;
    dtkComposerTransmitterEmitter<qreal> emitter_q2;
    dtkComposerTransmitterEmitter<qreal> emitter_q3;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkComposerNodeQuaternion::dtkComposerNodeQuaternion(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeQuaternionPrivate)
{
    this->appendReceiver(&d->receiver_quat);

    this->appendReceiver(&d->receiver_q0);
    this->appendReceiver(&d->receiver_q1);
    this->appendReceiver(&d->receiver_q2);
    this->appendReceiver(&d->receiver_q3);

    this->appendEmitter(&d->emitter_quat);
    d->emitter_quat.setData(dtkQuaternionReal(0, 0, 0, 0));

    this->appendEmitter(&d->emitter_q0);
    d->emitter_q0.setData(0);
    this->appendEmitter(&d->emitter_q1);
    d->emitter_q1.setData(0);
    this->appendEmitter(&d->emitter_q2);
    d->emitter_q2.setData(0);
    this->appendEmitter(&d->emitter_q3);
    d->emitter_q3.setData(0);
}

dtkComposerNodeQuaternion::~dtkComposerNodeQuaternion(void)
{
    delete d;
    
    d = NULL;
}

QString dtkComposerNodeQuaternion::inputLabelHint(int port) 
{
    switch(port) {
    case 0:
        return "quat";
        break;
    case 1:
        return "q0";
        break;
    case 2:
        return "q1";
        break;
    case 3:
        return "q2";
        break;
    case 4:
        return "q3";
        break;
    default:
        break;
    }

    return dtkComposerNodeLeaf::inputLabelHint(port);
}

QString dtkComposerNodeQuaternion::outputLabelHint(int port)
{    
    switch(port) {
    case 0:
        return "quat";
        break;
    case 1:
        return "q0";
        break;
    case 2:
        return "q1";
        break;
    case 3:
        return "q2";
        break;
    case 4:
        return "q3";
        break;
    default:
        break;
    }

    return dtkComposerNodeLeaf::inputLabelHint(port);
}

void dtkComposerNodeQuaternion::run(void)
{
    if (!d->receiver_quat.isEmpty()) {

        dtkQuaternionReal quat(d->receiver_quat.data());
        
        d->emitter_quat.setData(quat);
        d->emitter_q0.setData(quat[0]);
        d->emitter_q1.setData(quat[1]);
        d->emitter_q2.setData(quat[2]);
        d->emitter_q3.setData(quat[3]);

    } else {

        dtkQuaternionReal quat(d->receiver_q0.data(), d->receiver_q1.data(), d->receiver_q2.data(), d->receiver_q3.data());

        d->emitter_quat.setData(quat);
        d->emitter_q0.setData(quat[0]);
        d->emitter_q1.setData(quat[1]);
        d->emitter_q2.setData(quat[2]);
        d->emitter_q3.setData(quat[3]);

    }
}
