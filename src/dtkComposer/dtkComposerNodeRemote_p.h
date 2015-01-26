/* dtkComposerNodeRemote_p.h ---
 *
 * Author: Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:19:20
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QtCore>
#include <QtNetwork>

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

class dtkDistributedController;
class dtkDistributedSlave;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemotePrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemotePrivate
{

public:
    dtkComposerTransmitterReceiver<QString> jobid_receiver;

public:
    dtkComposerTransmitterEmitter<QTcpSocket* > socket_emitter;

public:
    QDomDocument composition;
    QByteArray current_hash;
    QByteArray last_sent_hash;

public:
    dtkDistributedController *controller;

public:
    QTcpSocket *socket;
    dtkDistributedCommunicator *communicator;

public:
    dtkDistributedSlave *slave;
    qlonglong rank;

public:
    QString jobid;
    QString last_jobid;

public:
    QString title;

};
