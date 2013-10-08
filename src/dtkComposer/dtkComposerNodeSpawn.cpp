/* dtkComposerNodeSpawn.cpp ---
 *
 * Author: Nicolas Niclausse, Inria.
 * Created: 2013/09/30 17:15:12
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerNodeSpawn.h"
#include "dtkComposerNodeSpawn_p.h"

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkDistributed/dtkDistributedController.h>
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorMpi.h>
#include <dtkDistributed/dtkDistributedSlave.h>

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkJson>

#include <dtkMath/dtkMath.h>

#include <dtkLog/dtkLog.h>


// /////////////////////////////////////////////////////////////////
// dtkComposerNodeSpawn implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeSpawn::dtkComposerNodeSpawn(void) : dtkComposerNodeRemote(),  d(new dtkComposerNodeSpawnPrivate)
{
    this->removeReceiver(1);
    this->removeReceiver(0);
    this->removeEmitter(0);

    this->appendReceiver(&(d->size_receiver));
    this->setInputLabelHint("np", 0);

    this->appendReceiver(&(d->interval_comm_emitter));
    this->setInputLabelHint("internal communicator", 1);

    this->appendReceiver(&(d->rank_emitter));
    this->setInputLabelHint("rank", 2);

    this->appendEmitter(&(d->communicator_emitter));
    this->setOutputLabelHint("communicator", 0);


    d->is_parent    = true;
    d->communicator = NULL;
    d->rank = -1;
    d->np   = -1;
    d->rank_emitter.setData(&d->rank);

    d->application = "numComposerEvaluator"; //FIXME
}

dtkComposerNodeSpawn::~dtkComposerNodeSpawn(void)
{

    delete d;

    d = NULL;
}

QString dtkComposerNodeSpawn::type(void)
{
    return "spawn";
}

QString dtkComposerNodeSpawn::titleHint(void)
{
    return "Spawn";
}

bool dtkComposerNodeSpawn::isSlave(void)
{
    return !d->is_parent;
}

void dtkComposerNodeSpawn::setComposition(QDomDocument document)
{
    d->composition  = document;
    d->current_hash = QCryptographicHash::hash(d->composition.toByteArray(),QCryptographicHash::Md5);
}

void dtkComposerNodeSpawn::setCommunicator(dtkDistributedCommunicator *comm)
{
    d->communicator = comm;
    d->communicator_emitter.setData(d->communicator);

    d->is_parent = false;
}

void dtkComposerNodeSpawn::setInternalCommunicator(dtkDistributedCommunicator *comm)
{
    d->internal_comm = comm;
}

void dtkComposerNodeSpawn::begin(void)
{
    if (!d->communicator) {
        // we are running on the controller, for the first time:
        // need to spawn processes
        if (d->size_receiver.isEmpty()) {
            d->np =  QThread::idealThreadCount();
            dtkInfo() << "Set number of spawned proceses to" << d->np;
        } else {
            d->np = *d->size_receiver.data();
        }

        d->communicator = new dtkDistributedCommunicatorMpi;
        d->internal_comm = d->communicator->spawn(d->application, d->np);
        d->interval_comm_emitter.setData(d->internal_comm);
        d->rank = d->internal_comm->rank();


        if (!d->internal_comm) {
            dtkError() << "NULL internal communicator, spawn has failed !";
            return;
        }

    } else {
        dtkTrace() << "communicator exists,  no spawn";
    }

    int first_transmitter = 3;
    if (d->is_parent) {
        int rank =  dtkDistributedCommunicator::ROOT;

        if (d->current_hash != d->last_sent_hash){
            // send sub-composition to rank 0 on remote node
            QByteArray compo = d->composition.toByteArray();
            dtkDebug() << "running node remote begin statement on controller, send composition of size " << compo.size();
            d->communicator->broadcast(compo, rank);
            d->last_sent_hash=d->current_hash;
        } else {
            dtkDebug() << "composition hash hasn't changed, send 'not-modified' to slave";
            QByteArray data = QString("not-modified").toAscii();
            d->communicator->broadcast(data,  rank);
        }

        // then send transmitters data
        int max  = dtkComposerNodeComposite::receivers().count();
        for (int i = first_transmitter; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(dtkComposerNodeComposite::receivers().at(i));
            // FIXME: use our own transmitter variant list (see control nodes)
            QByteArray array = t->dataToByteArray();
            dtkDebug() << "sending transmitter" << i << "of size" << array.size();
            d->communicator->broadcast(array, rank);
        }
    } else if (d->communicator) {
        if (d->rank < 0) {
            dtkDebug() << "get rank/size on slave";
            d->interval_comm_emitter.setData(d->internal_comm);
            d->rank = d->internal_comm->rank();
            d->np = d->internal_comm->size();
            dtkDebug() << "rank/size"<< d->rank << d->np;
        }

        dtktrace() << "get transmitter data";
        // running on the slave, receive data and set transmitters
        int max  = dtkComposerNodeComposite::receivers().count();
        for (int i = first_transmitter; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(dtkComposerNodeComposite::receivers().at(i));
            QByteArray array ;
            qint16 parent_rank = 0;
            d->communicator->broadcast(array, parent_rank);
            t->setTwinned(false);
            t->setDataFrom(array);
            t->setTwinned(true);
        }
    } else {
        dtkError() << "No communicator on spawned node: can't run begin node";
    }
}

void dtkComposerNodeSpawn::end(void)
{
    qint16 tag = 0;
    if (d->is_parent) {
        dtkDebug() << "running node remote end statement on controller";
        int max  = this->emitters().count();
        for (int i = 1; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->emitters().at(i));

            QByteArray array;
            d->communicator->receive(array, dtkDistributedCommunicator::ANY_SOURCE, tag);

            t->setTwinned(false);
            t->setDataFrom(array);
            t->setTwinned(true);
        }
    } else if (d->communicator) {
        // running on the slave, send data and set transmitters
        dtkDebug() << "running node remote end statement on slave" << d->communicator->rank() ;

        int max  = this->emitters().count();
        qint16 parent_rank = 0;

        for (int i = 1; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->emitters().at(i));
            if (d->communicator->rank() == 0) {
                dtkDebug() << "end, send transmitter data (we are rank 0)";

                QByteArray array = t->dataToByteArray();

                if (!array.isEmpty()) {
                    d->communicator->send(array, parent_rank, tag);
                } else {
                    dtkError() << "serialization failed in transmitter";
                }
            }
        }
    } else {
        dtkError() << "No communicator and no controller on remote node: can't run end node";
    }

}


