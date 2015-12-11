/* @(#)dtkDistributedCommunicator.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/07 13:59:41
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedCommunicator.h"
#include "dtkDistributedRequest.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedCommunicator
// /////////////////////////////////////////////////////////////////


/*!
  \class dtkDistributedCommunicator
  \inmodule dtkDistributed
  \brief dtkDistributedCommunicator is the interface for distributed computing.

  It can be used to spawn processes/threads on one or several hosts (depending on the implementation), execute code on each processes, and gives access to communications and synchronisations methods.

  The communication API is very similar to the MPI API (send, receive, broadcast, barrier, ...), but can be used without MPI ( a plugin based on qthreads is provided).

  \code
  dtkDistributedCommunicator *comm = dtkDistributed::communicator::instance();
  PingPongWork *runnable = new PingPongWork();
  QStringList hosts;
  // run ping pong on 2 process on localhost
  hosts << "localhost" << "localhost";
  comm->spawn(hosts,1);
  comm->exec(runnable);
  comm->unspawn();
  \endcode

*/

/*! \enum dtkDistributedCommunicator::OperationType
    \value None
    \value Min
    \value Max
    \value Sum
    \value Product
    \value BitwiseAnd
    \value BitwiseOr
    \value BitwiseXor
    \value LogicalAnd
    \value LogicalOr
    \value LogicalXor
*/

/*! \enum dtkDistributedCommunicator::MessageTag
    \value TagSend
    \value TagReceive
    \value TagReduce
*/

/*!
 *  Constructor
 */
dtkDistributedCommunicator::dtkDistributedCommunicator(void) : QObject()
{
}

/*!
 *  Destructor
 */
dtkDistributedCommunicator::~dtkDistributedCommunicator(void)
{
}

void dtkDistributedCommunicator::setWid(qint32)
{
}

bool dtkDistributedCommunicator::active(void)
{
    return false;
}

/*! \fn dtkDistributedCommunicator::spawn (QStringList hostnames, QString wrapper)

  Spawn a communicator on all hostnames. Optionnaly use a wrapper to spawn slaves. Special case: if the string list has only one value equal to "nospawn", then spawning is disabled. This can be useful if MPI spawning is not working well with others tools (debugguer or batch schedulers). This is used by the --no-spawn option of dtkDistributedApplication.

*/

/*! \fn dtkDistributedCommunicator::barrier (void)

  Blocks until all processes in the communicator have reached this method. Use it to synchronize all the processes.

*/

/*! \fn dtkDistributedCommunicator::exec (QRunnable *runnable)

  Execute the given \a runnable: each process in the communicator will call the run method of the given object.

*/

/*! \fn qint32 dtkDistributedCommunicator::rank (void)

  alias to wid()

  \sa wid()
*/

/*! \fn qint32 dtkDistributedCommunicator::wid (void)

  Return the worker id (aka rank) of the current process

  \sa rank()
*/

/*! \fn qint32 dtkDistributedCommunicator::size (void)

  Return the size of the communicator (number of processes spawned).

*/


void dtkDistributedCommunicator::send(char *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, QMetaType::Char, target, tag);
}

void dtkDistributedCommunicator::send(bool *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, QMetaType::Bool, target, tag);
}

void dtkDistributedCommunicator::send(int *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, QMetaType::Int, target, tag);
}

void dtkDistributedCommunicator::send(long *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, QMetaType::Long, target, tag);
}

void dtkDistributedCommunicator::send(qlonglong *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, QMetaType::LongLong, target, tag);
}

void dtkDistributedCommunicator::send(float *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, QMetaType::Float, target, tag);
}

void dtkDistributedCommunicator::send(double *data, qint64 size, qint32 target, qint32 tag)
{
    return this->send(data, size, QMetaType::Double, target, tag);
}

void dtkDistributedCommunicator::send(const QVariant &v, qint32 target, qint32 tag)
{
    QByteArray bytes;
    QDataStream stream(&bytes,QIODevice::WriteOnly);
    stream << v;
    this->send(bytes, target, tag);
}

void dtkDistributedCommunicator::broadcast(bool      *data, qint64 size, qint32 source)
{
    this->broadcast(data, size, QMetaType::Bool, source);
}

void dtkDistributedCommunicator::broadcast(int       *data, qint64 size, qint32 source)
{
    this->broadcast(data, size, QMetaType::Int, source);
}

void dtkDistributedCommunicator::broadcast(long      *data, qint64 size, qint32 source)
{
    this->broadcast(data, size, QMetaType::Long, source);
}

void dtkDistributedCommunicator::broadcast(qlonglong *data, qint64 size, qint32 source)
{
    this->broadcast(data, size, QMetaType::LongLong, source);
}

void dtkDistributedCommunicator::broadcast(float     *data, qint64 size, qint32 source)
{
    this->broadcast(data, size, QMetaType::Float, source);
}

void dtkDistributedCommunicator::broadcast(double    *data, qint64 size, qint32 source)
{
    this->broadcast(data, size, QMetaType::Double, source);
}

void dtkDistributedCommunicator::broadcast(char      *data, qint64 size, qint32 source)
{
    this->broadcast(data, size, QMetaType::Char, source);
}

void dtkDistributedCommunicator::receive(char *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, QMetaType::Char, source, tag);
}

void dtkDistributedCommunicator::receive(bool *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, QMetaType::Bool, source, tag);
}

void dtkDistributedCommunicator::receive(int *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, QMetaType::Int, source, tag);
}

void dtkDistributedCommunicator::receive(long *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, QMetaType::Long, source, tag);
}

void dtkDistributedCommunicator::receive(qlonglong *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, QMetaType::LongLong, source, tag);
}

void dtkDistributedCommunicator::receive(float *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, QMetaType::Float, source, tag);
}

void dtkDistributedCommunicator::receive(double *data, qint64 size, qint32 source, qint32 tag)
{
    return this->receive(data, size, QMetaType::Double, source, tag);
}

void dtkDistributedCommunicator::receive(QVariant &v, qint32 target, qint32 tag)
{
    QByteArray bytes;
    this->receive(bytes, target, tag);
    QDataStream stream(&bytes,QIODevice::ReadOnly);
    stream >> v;
}

void dtkDistributedCommunicator::receive(QVariant &v, qint32 target, qint32 tag, dtkDistributedCommunicatorStatus &status)
{
    QByteArray bytes;
    this->receive(bytes, target, tag, status);
    QDataStream stream(&bytes,QIODevice::ReadOnly);
    stream >> v;
}

dtkDistributedRequest *dtkDistributedCommunicator::ireceive(bool *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, QMetaType::Bool, source, tag);
}

dtkDistributedRequest *dtkDistributedCommunicator::ireceive(char *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, QMetaType::Char, source, tag);
}

dtkDistributedRequest *dtkDistributedCommunicator::ireceive(int *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, QMetaType::Int, source, tag);
}

dtkDistributedRequest *dtkDistributedCommunicator::ireceive(long *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, QMetaType::Long, source, tag);
}

dtkDistributedRequest *dtkDistributedCommunicator::ireceive(qint64 *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, QMetaType::LongLong, source, tag);
}

dtkDistributedRequest *dtkDistributedCommunicator::ireceive(float *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, QMetaType::Float, source, tag);
}

dtkDistributedRequest *dtkDistributedCommunicator::ireceive(double *data, qint64 size, qint32 source, int tag)
{
    return this->ireceive(data, size, QMetaType::Double, source, tag);
}

void dtkDistributedCommunicator::reduce(void   *send, void   *recv, qint64 size, QMetaType::Type dataType, OperationType operationType, qint32 target, bool all)
{
    qCritical() << "Default operator for reduce, not implemented";
}

void dtkDistributedCommunicator::reduce(bool *send, bool *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, QMetaType::Bool, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(char *send, char *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, QMetaType::Char, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(int *send, int *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, QMetaType::Int, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(qlonglong *send, qlonglong *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, QMetaType::LongLong, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(float *send, float *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, QMetaType::Float, operationType, target, all);
}

void dtkDistributedCommunicator::reduce(double *send, double *recv, qint64 size, OperationType operationType, qint32 target, bool all)
{
    return this->reduce(send, recv, size, QMetaType::Double, operationType, target, all);
}

void dtkDistributedCommunicator::gather(void   *send, void   *recv, qint64 size, QMetaType::Type dataType, qint32 target, bool all)
{
    qCritical() << "Default operator for gather, not implemented";
}

void dtkDistributedCommunicator::gather(bool *send, bool *recv, qint64 size, qint32 target, bool all)
{
    return this->gather(send, recv, size, QMetaType::Bool, target, all);
}

void dtkDistributedCommunicator::gather(char *send, char *recv, qint64 size, qint32 target, bool all)
{
    return this->gather(send, recv, size, QMetaType::Char, target, all);
}

void dtkDistributedCommunicator::gather(int *send, int *recv, qint64 size, qint32 target, bool all)
{
    return this->gather(send, recv, size, QMetaType::Int, target, all);
}

void dtkDistributedCommunicator::gather(qlonglong *send, qlonglong *recv, qint64 size, qint32 target, bool all)
{
    return this->gather(send, recv, size, QMetaType::LongLong, target, all);
}

void dtkDistributedCommunicator::gather(float *send, float *recv, qint64 size, qint32 target, bool all)
{
    return this->gather(send, recv, size, QMetaType::Float, target, all);
}

void dtkDistributedCommunicator::gather(double *send, double *recv, qint64 size, qint32 target, bool all)
{
    return this->gather(send, recv, size, QMetaType::Double, target, all);
}

