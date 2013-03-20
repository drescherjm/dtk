/* dtkComposerNodeQuaternion.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Apr 26 13:06:02 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Tue Jan  8 09:29:16 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 48
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
    dtkComposerTransmitterReceiver<dtkQuaternionReal*> receiver_quat;

    dtkComposerTransmitterReceiver<qreal> receiver_q0;
    dtkComposerTransmitterReceiver<qreal> receiver_q1;
    dtkComposerTransmitterReceiver<qreal> receiver_q2;
    dtkComposerTransmitterReceiver<qreal> receiver_q3;

public:
    dtkComposerTransmitterEmitter<dtkQuaternionReal*> emitter_quat;

    dtkComposerTransmitterEmitter<qreal> emitter_q0;
    dtkComposerTransmitterEmitter<qreal> emitter_q1;
    dtkComposerTransmitterEmitter<qreal> emitter_q2;
    dtkComposerTransmitterEmitter<qreal> emitter_q3;

public:
    dtkQuaternionReal *quat;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkComposerNodeQuaternion::dtkComposerNodeQuaternion(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeQuaternionPrivate)
{
    d->quat = NULL;

    this->appendReceiver(&d->receiver_quat);

    this->appendReceiver(&d->receiver_q0);
    this->appendReceiver(&d->receiver_q1);
    this->appendReceiver(&d->receiver_q2);
    this->appendReceiver(&d->receiver_q3);

    this->appendEmitter(&d->emitter_quat);

    this->appendEmitter(&d->emitter_q0);
    this->appendEmitter(&d->emitter_q1);
    this->appendEmitter(&d->emitter_q2);
    this->appendEmitter(&d->emitter_q3);
}

dtkComposerNodeQuaternion::~dtkComposerNodeQuaternion(void)
{
    if (d->quat)
        delete d->quat;
    d->quat = NULL;

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

        dtkQuaternionReal *quat = d->receiver_quat.constData();

        if (!quat) {
            dtkError() << "dtkComposerNodeQuaternion::" << Q_FUNC_INFO << "Input quaternion is not defined.";
            d->emitter_q0.clearData();
            d->emitter_q1.clearData();
            d->emitter_q2.clearData();
            d->emitter_q3.clearData();
            d->emitter_quat.clearData();
            return;
        }

        d->emitter_q0.setData( (*quat)[0] );
        d->emitter_q1.setData( (*quat)[1] );
        d->emitter_q2.setData( (*quat)[2] );
        d->emitter_q3.setData( (*quat)[3] );

        d->emitter_quat.setData(quat);

    } else {

        if (!d->quat)
            d->quat = new dtkQuaternionReal();  

        if (!d->receiver_q0.isEmpty())
            (*d->quat)[0] = d->receiver_q0.data();
        else
            (*d->quat)[0] = 0.;

        if (!d->receiver_q1.isEmpty())
            (*d->quat)[1] = d->receiver_q1.data();
        else
            (*d->quat)[1] = 0.;

        if (!d->receiver_q2.isEmpty())
            (*d->quat)[2] = d->receiver_q2.data();
        else
            (*d->quat)[2] = 0.;

        if (!d->receiver_q3.isEmpty())
            (*d->quat)[3] = d->receiver_q3.data();
        else
            (*d->quat)[3] = 0.;

        d->emitter_q0.setData( (*d->quat)[0] );
        d->emitter_q1.setData( (*d->quat)[1] );
        d->emitter_q2.setData( (*d->quat)[2] );
        d->emitter_q3.setData( (*d->quat)[3] );

        d->emitter_quat.setData(d->quat);
    }
}
