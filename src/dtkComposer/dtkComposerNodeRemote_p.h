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


#include <QtCore>

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

class dtkDistributedController;
class dtkDistributedCommunicator;
class dtkDistributedCommunicatorTcp;
class dtkDistributedSlave;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemotePrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemotePrivate
{

public:
    dtkComposerTransmitterReceiver<QString> jobid_receiver;

public:
    dtkComposerTransmitterEmitter<dtkDistributedCommunicator > communicator_emitter;

public:
    QDomDocument composition;
    QByteArray current_hash;
    QByteArray last_sent_hash;

public:
    dtkDistributedController *controller;

public:
    dtkDistributedCommunicator *communicator;
    dtkDistributedCommunicatorTcp *server;

public:
    dtkDistributedSlave *slave;

public:
    QString jobid;
    QString last_jobid;

public:
    QString title;

};
