/* dtkCommunicatorMpi.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:51:02 2010 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkDistributedCommunicatorMpi.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkLog/dtkLog.h>

#include <dtkMath>

#include <mpi.h>

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

MPI::Datatype data_type(dtkDistributedCommunicator::DataType type)
{
    switch(type) {
    case dtkDistributedCommunicator::dtkDistributedCommunicatorBool:   return MPI::BOOL;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorChar:   return MPI::CHAR;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorInt:    return MPI::INT;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorLong:   return MPI::LONG;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorInt64:  return MPI::LONG_LONG;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorFloat:  return MPI::FLOAT;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorDouble: return MPI::DOUBLE;
    default:
        dtkInfo() << "dtkCommunicatorMpi: data type not handled.";
        return MPI::BYTE;
    }
}

MPI::Op operation_type(dtkDistributedCommunicator::OperationType type)
{
    switch(type) {
    case dtkDistributedCommunicator::dtkDistributedCommunicatorMin:        return MPI::MIN;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorMax:        return MPI::MAX;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorSum:        return MPI::SUM;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorProduct:    return MPI::PROD;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorBitwiseAnd: return MPI::BAND;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorBitwiseOr:  return MPI::BOR;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorBitwiseXor: return MPI::BXOR;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorLogicalAnd: return MPI::LAND;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorLogicalOr:  return MPI::LOR;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorLogicalXor: return MPI::LXOR;
    default:
        dtkInfo() << "dtkCommunicatorMpi: operation type not handled.";
        return MPI::MIN;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkCommunicatorMpi
// /////////////////////////////////////////////////////////////////

class dtkDistributedCommunicatorMpiPrivate
{
public:

};

dtkDistributedCommunicatorMpi::dtkDistributedCommunicatorMpi(void) : dtkDistributedCommunicator(), d(new dtkDistributedCommunicatorMpiPrivate)
{

}

dtkDistributedCommunicatorMpi::~dtkDistributedCommunicatorMpi(void)
{
    delete d;

    d = NULL;
}

dtkDistributedCommunicatorMpi::dtkDistributedCommunicatorMpi(const dtkDistributedCommunicatorMpi& other)
{

}

dtkDistributedCommunicatorMpi& dtkDistributedCommunicatorMpi::operator=(const dtkDistributedCommunicatorMpi& other)
{
    return *this;
}

//! Mpi communicator initializer.
/*! 
 *  Initializes the MPI execution environment. This function must be
 *  called in every MPI program, must be called before any other MPI
 *  functions and must be called only once in an MPI program.
 * 
 *  \code
 *  dtkDistributedCommunicator *communicator = new dtkDistributedCommunicatorMpi;
 *  communicator->initialize();
 *  ...
 *  ...
 *  communicator->uninitialize();
 *  \endcode
 *
 * \sa uninitialize.
 */

void dtkDistributedCommunicatorMpi::initialize(void)
{
    int    argc = qApp->argc(); // These methods are obsolete but should be really exist in QCoreApplication
    char **argv = qApp->argv(); // These methods are obsolete but should be really exist in QCoreApplication

    MPI::Init(argc, argv);
}

bool dtkDistributedCommunicatorMpi::initialized(void)
{
    return MPI::Is_initialized();
}

//! Mpi communicator uninitializer.
/*! 
 *  Terminates the MPI execution environment. This function should be
 *  the last MPI routine called in every MPI program - no other MPI
 *  routines may be called after it.
 *
 *  \code
 *  dtkDistributedCommunicator *communicator = new dtkDistributedCommunicatorMpi;
 *  communicator->initialize();
 *  ...
 *  ...
 *  communicator->uninitialize();
 *  \endcode
 *
 * \sa initialize.
 */

void dtkDistributedCommunicatorMpi::uninitialize(void)
{
    MPI::Finalize();
}

//! 
/*! 
 *  Returns an elapsed wall clock time in seconds (double precision)
 *  on the calling processor.
 *
 *  \sa tick.
 */

double dtkDistributedCommunicatorMpi::time(void)
{
    return MPI::Wtime();
}

//! 
/*! 
 *  Returns the resolution in seconds (double precision) of time().
 * 
 *  \sa time.
 */

double dtkDistributedCommunicatorMpi::tick(void)
{
    return MPI::Wtick();
}

//! 
/*! 
 *  Determines the rank of the calling process within the
 *  communicator. Initially, each process will be assigned a unique
 *  integer rank between 0 and number of processors - 1 within the
 *  communicator.
 *
 *  \sa size.
 */

int dtkDistributedCommunicatorMpi::rank(void)
{
    return MPI::COMM_WORLD.Get_rank();
}

//!  
/*! 
 *  Determines the number of processes in the group associated with a
 *  communicator.
 *
 *  \sa rank.
 */

int dtkDistributedCommunicatorMpi::size(void)
{
    return MPI::COMM_WORLD.Get_size();
}

//! 
/*! 
 *  Returns the name of the processor.
 */

QString dtkDistributedCommunicatorMpi::name(void) const
{
    int len; char name[MPI_MAX_PROCESSOR_NAME];

    memset(name,0,MPI_MAX_PROCESSOR_NAME);
    MPI::Get_processor_name(name,len);
    memset(name+len,0,MPI_MAX_PROCESSOR_NAME-len);

    return QString(name);
}

//! Standard-mode, blocking send.
/*! 
 *  Basic blocking send operation. Routine returns only after the
 *  application buffer in the sending task is free for reuse.
 */

void dtkDistributedCommunicatorMpi::send(void *data, qint64 size, DataType dataType, qint16 target, int tag)
{
    MPI::COMM_WORLD.Send(data, size, data_type(dataType), target, tag);
}

//! Standard-mode, blocking receive.
/*! 
 *  Receive a message and block until the requested data is available
 *  in the application buffer in the receiving task.
 */

void dtkDistributedCommunicatorMpi::receive(void *data, qint64 size, DataType dataType, qint16 source, int tag)
{
    MPI::COMM_WORLD.Recv(data, size, data_type(dataType), source, tag);
}

void dtkDistributedCommunicatorMpi::receive(void *data, qint64 size, DataType dataType, qint16 source, int tag, dtkDistributedCommunicatorStatus& status)
{
    MPI::Status mpi_status;
    MPI::COMM_WORLD.Recv(data, size, data_type(dataType), source, tag, mpi_status);
    status.setCount( mpi_status.Get_count(data_type(dataType)));
    status.setTag(mpi_status.Get_tag());
    status.setSource(mpi_status.Get_source());
    status.setError(mpi_status.Get_error());
}


/*!
 *  send a dtkAbstractData object; we need to send it's type (with the
 *  size type) and then serialize the object.
 */

void dtkDistributedCommunicatorMpi::send(dtkAbstractData *data, qint16 target, int tag)
{

    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << data->identifier();
// FIXME: handle container
    QByteArray *array_tmp = data->serialize();
    if (array_tmp->count() > 0 ) {
        array.append(*array_tmp);
        dtkDistributedCommunicator::send(array,target,tag);
    } else {
        dtkError() <<"serialization failed";
    }
}

void dtkDistributedCommunicatorMpi::receive(dtkAbstractData *&data, qint16 source, int tag)
{
    QByteArray array;

    dtkDistributedCommunicator::receive(array, source, tag);

    if( array.count() > 0) {
        QDataStream stream(&array, QIODevice::ReadOnly);
        QString typeName ;
        stream >> typeName;

        qlonglong  header_length=sizeof(int)+2*typeName.size();

        data = dtkAbstractDataFactory::instance()->create(typeName);
        if (!data) {
            dtkWarn() << "Can't instantiate object of type" << QString(typeName);
            return;
        }

        if (!data->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length))) {
            dtkError() << "Warning: deserialization failed";
        } else {
            dtkDebug() << "deserialization succesful";
        }
    }
}

/*!
 *  send a QString
 */

void dtkDistributedCommunicatorMpi::send(const QString &s, qint16 target, int tag)
{
    qint64  length = s.length()+1;
    qint64  size_l=1;
    dtkDistributedCommunicator::send(&length,size_l,target,tag);

    QByteArray Array = s.toAscii();
    char *char_array = Array.data();
    dtkDistributedCommunicator::send(char_array,length,target,tag);
}

void dtkDistributedCommunicatorMpi::send(QByteArray &array, qint16 target, int tag)
{
    qint64   arrayLength = array.length();
    dtkDistributedCommunicator::send(array.data(), arrayLength, target, tag);

}

void dtkDistributedCommunicatorMpi::receive(QString &s, qint16 source, int tag)
{
    qint64   length;
    dtkDistributedCommunicator::receive(&length,1,source,tag);
    char     s_c[length];

    dtkDistributedCommunicator::receive(s_c, length, source,tag);
    s = QString(s_c);
}

void dtkDistributedCommunicatorMpi::receive(QByteArray &array, qint16 source, int tag)
{
    dtkDistributedCommunicatorStatus status;
    this->receive(array, source, tag, status);
}

void dtkDistributedCommunicatorMpi::receive(QByteArray &array, qint16 source, int tag, dtkDistributedCommunicatorStatus& status )
{
    MPI::Status mpi_status;
    MPI::COMM_WORLD.Probe(source, tag, mpi_status);
    qint64   count = mpi_status.Get_count(MPI::CHAR);
    status.setCount(count);
    status.setTag(mpi_status.Get_tag());
    status.setSource(mpi_status.Get_source());
    status.setError(mpi_status.Get_error());
    dtkTrace() << "probe mpi: count/source/tag : " << status.count() << status.source() << status.tag();
    array.resize(count);
    dtkDistributedCommunicator::receive(array.data(), count, source, tag);

}

//! Barrier.
/*!
 *  Creates a barrier synchronization. Each task, when reaching the
 *  barrier call, blocks until all tasks in the group reach the same
 *  barrier call.
 */

void dtkDistributedCommunicatorMpi::barrier(void)
{
    MPI::COMM_WORLD.Barrier();
}

//! Broadcast.
/*! 
 *  Broadcasts (sends) a message from the process with rank "source"
 *  to all other processes in the group.
 */

void dtkDistributedCommunicatorMpi::broadcast(void *data, qint64 size, DataType dataType, qint16 source)
{
    MPI::COMM_WORLD.Bcast(data, size, data_type(dataType), source); 
}

//! Gather.
/*! 
 *  Gathers distinct messages from each task in the group to a single
 *  destination task. This routine is the reverse operation of
 *  scatter. If all is true, target is not taken into account.
 *
 *  \sa scatter.
 */

void dtkDistributedCommunicatorMpi::gather(void *send, void *recv, qint64 size, DataType dataType, qint16 target, bool all)
{
    if(all)
        MPI::COMM_WORLD.Allgather(send, size, data_type(dataType), recv, size, data_type(dataType));
    else
        MPI::COMM_WORLD.Gather(send, size, data_type(dataType), recv, size, data_type(dataType), target);
}

//! Scatter.
/*! 
 *  Distributes distinct messages from a single source task to each
 *  task in the group.
 *
 *  \sa gather.
 */

void dtkDistributedCommunicatorMpi::scatter(void *send, void *recv, qint64 size, DataType dataType, qint16 source)
{
    MPI::COMM_WORLD.Scatter(send, size, data_type(dataType), recv, size, data_type(dataType), source);
}

//! Reduce.
/*! 
 *  Applies a reduction operation on all tasks in the group and places
 *  the result in one task. If all is true, target is not taken into
 *  account.
 *
 *  \sa dtkDistributedCommunicator::OperationType.
 */

void dtkDistributedCommunicatorMpi::reduce(void *send, void *recv, qint64 size, DataType dataType, OperationType operationType, qint16 target, bool all)
{
    if(all)
        MPI::COMM_WORLD.Allreduce(send, recv, size, data_type(dataType), operation_type(operationType));
    else
        MPI::COMM_WORLD.Reduce(send, recv, size, data_type(dataType), operation_type(operationType), target);
}

// /////////////////////////////////////////////////////////////////
// Documentation
// /////////////////////////////////////////////////////////////////

//! \class dtkDistributedCommunicatorMpi
/*! 
 *  \brief A mpi based dtk communicator.
 */
