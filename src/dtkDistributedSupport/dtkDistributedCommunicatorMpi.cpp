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

#include <dtkCoreSupport/dtkAbstractDataFactory.h>
#include <dtkLog/dtkLogger.h>

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
// dtkDistributedCommunicatorRequestMpiPrivate
// /////////////////////////////////////////////////////////////////

class dtkDistributedCommunicatorRequestMpiPrivate
{
public:
    dtkAbstractData *mdata;
    QByteArray *marray;
    QString *mstring;

public:
    MPI_Request request;
};


dtkDistributedCommunicatorRequestMpi::dtkDistributedCommunicatorRequestMpi(void) : dtkDistributedCommunicatorRequest(), d(new dtkDistributedCommunicatorRequestMpiPrivate)
{
    d->mdata   = NULL;
    d->marray  = NULL;
    d->mstring = NULL;
};

dtkDistributedCommunicatorRequestMpi::~dtkDistributedCommunicatorRequestMpi(void)
{
    delete d;
    d = NULL;
};

void dtkDistributedCommunicatorRequestMpi::wait(void)
{
    MPI_Status mpi_status;
    MPI_Wait(&(d->request), &mpi_status);
}

// /////////////////////////////////////////////////////////////////
// dtkDistributedCommunicatorMpiPrivate
// /////////////////////////////////////////////////////////////////

class dtkDistributedCommunicatorMpiPrivate
{
public:
    MPI_Comm parent_comm;
    MPI_Comm comm;

public:
    int size, rank;
};

dtkDistributedCommunicatorMpi::dtkDistributedCommunicatorMpi(void) : dtkDistributedCommunicator(), d(new dtkDistributedCommunicatorMpiPrivate)
{
    d->comm = MPI_COMM_WORLD;
    d->rank = -1;
    d->size = 0;
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


dtkDistributedCommunicator *dtkDistributedCommunicatorMpi::spawn(QString cmd, qlonglong np)
{

    this->initialize();

    MPI_Comm parentcomm, intercomm;
    MPI_Comm_get_parent(&(d->comm));
    QStringList args = qApp->arguments();

    if (d->comm == MPI_COMM_NULL) {
        qDebug() << "I'm the parent";
        int    argc = args.count();
        char **argv=(char**)malloc(sizeof(char*)*(2));

        argv[0] = const_cast<char*>("--spawn");
        argv[1] = NULL;
        int errs[np];
        MPI_Info info;
        MPI_Info_create(&info );

        QByteArray host = QString("localhost").toLocal8Bit();

        for (qlonglong i =0; i < np; ++i) {
            MPI_Info_set(info, const_cast<char*>("add-host"),host.data());
        }

        QByteArray wdir = qApp->applicationDirPath().toLocal8Bit();
        MPI_Info_set(info, const_cast<char*>("wdir"), wdir.data());

        QByteArray appname = cmd.toLocal8Bit();

        MPI_Comm_spawn( appname.data(), argv ,np, info, 0, MPI_COMM_WORLD, &(d->comm), errs );
        MPI_Barrier(d->comm);
    } else {
        MPI_Barrier(d->comm);
    }
    // create another communicator for COMM_WORLD
    return new dtkDistributedCommunicatorMpi;

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
    MPI_Comm_rank(d->comm, &d->rank);
    return d->rank;
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
    MPI_Comm_size(d->comm, &d->size);
    return d->size;
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
    MPI_Send(data, size, data_type(dataType), target, tag, d->comm);
}

void dtkDistributedCommunicatorMpi::isend(void *data, qint64 size, DataType dataType, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    dtkDistributedCommunicatorRequestMpi *mpi_req = dynamic_cast<dtkDistributedCommunicatorRequestMpi *>(req);

    if (mpi_req) {
        MPI_Isend(data, size, data_type(dataType), target, tag, d->comm, &(mpi_req->d->request));
    
    } else {
        MPI_Request request;
        MPI_Isend(data, size, data_type(dataType), target, tag, d->comm, &request);
    }
}

void dtkDistributedCommunicatorMpi::isend(dtkAbstractData *data, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << data->identifier();
    // FIXME: handle container
    QByteArray *array_tmp = data->serialize();
    if (array_tmp->count() > 0 ) {
        array.append(*array_tmp);
        dtkDistributedCommunicatorMpi::isend(array, target, tag, req);
    } else {
        dtkError() <<"serialization failed";
    }
};

void dtkDistributedCommunicatorMpi::isend(const QString& s, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    QByteArray Array = s.toUtf8();
    return dtkDistributedCommunicatorMpi::isend(Array, target, tag, req);
};

void dtkDistributedCommunicatorMpi::isend(QByteArray& array, qint16 target, int tag, dtkDistributedCommunicatorRequest *req)
{
    qint64 arrayLength = array.length();
    this->isend(array.data(), arrayLength, dtkDistributedCommunicator::dtkDistributedCommunicatorChar, target, tag, req);
};

void dtkDistributedCommunicatorMpi::ireceive(void *data, qint64 size, DataType dataType, qint16 source, int tag, dtkDistributedCommunicatorRequest *req)
{
    dtkDistributedCommunicatorRequestMpi *mpi_req = dynamic_cast<dtkDistributedCommunicatorRequestMpi *>(req);

    if (mpi_req) {
        MPI_Irecv(data, size, data_type(dataType), source, tag, d->comm, &(mpi_req->d->request));
    
    } else {
        MPI_Request request;
        MPI_Irecv(data, size, data_type(dataType), source, tag, d->comm, &request);
    }
};

//! Standard-mode, blocking receive.
/*! 
 *  Receive a message and block until the requested data is available
 *  in the application buffer in the receiving task.
 */

void dtkDistributedCommunicatorMpi::receive(void *data, qint64 size, DataType dataType, qint16 source, int tag)
{
    MPI_Status status;
    MPI_Recv(data, size, data_type(dataType), source, tag, d->comm, &status);
}

void dtkDistributedCommunicatorMpi::receive(void *data, qint64 size, DataType dataType, qint16 source, int tag, dtkDistributedCommunicatorStatus& status)
{
    MPI_Status mpi_status;
    MPI_Recv(data, size, data_type(dataType), source, tag, d->comm, &mpi_status);

    int nelements;
    MPI_Get_count(&mpi_status, data_type(dataType), &nelements);

    status.setCount( nelements);

    status.setTag(mpi_status.MPI_TAG);
    status.setSource(mpi_status.MPI_SOURCE);
    status.setError(mpi_status.MPI_ERROR);
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
        dtkDistributedCommunicatorMpi::send(array,target,tag);
    } else {
        dtkError() <<"serialization failed";
    }
}

void dtkDistributedCommunicatorMpi::receive(dtkAbstractData *&data, qint16 source, int tag)
{
    QByteArray array;

    dtkDistributedCommunicatorMpi::receive(array, source, tag);

    if( array.count() > 0) {
        QDataStream stream(&array, QIODevice::ReadOnly);
        QString typeName ;
        stream >> typeName;

        qlonglong  header_length=sizeof(int)+2*typeName.size();

        data = dtkAbstractDataFactory::instance()->create(typeName);
        if (!data) {
            dtkWarning() << "Can't instantiate object of type" << QString(typeName);
            return;
        }

        if (!data->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length))) {
            dtkError() << "Warning: deserialization failed";
        } else {
            dtkDebug() << "deserialization succesful";
        }
    }
}

void dtkDistributedCommunicatorMpi::broadcast(dtkAbstractData *&data, qint16 source)
{
    QByteArray array;
    if (d->rank == source) {
        QDataStream stream(&array, QIODevice::WriteOnly);
        stream << data->identifier();
        // FIXME: handle container
        QByteArray *array_tmp = data->serialize();
        if (array_tmp->count() > 0 ) {
            array.append(*array_tmp);
        } else {
            dtkError() <<"serialization failed" ;
        }
    }
    this->broadcast(array, source);
    if (d->rank != source) {
        if( array.count() > 0) {
            QDataStream stream(&array, QIODevice::ReadOnly);
            QString typeName ;
            stream >> typeName;

            qlonglong  header_length=sizeof(int)+2*typeName.size();

            data = dtkAbstractDataFactory::instance()->create(typeName);
            if (!data) {
                dtkWarning() << "Can't instantiate object of type" << QString(typeName);
                return;
            }

            if (!data->deserialize(QByteArray::fromRawData(array.data()+header_length,array.size()-header_length))) {
                dtkError() << "Warning: deserialization failed";
            } else {
                dtkDebug() << "deserialization succesful";
            }
        }
    }
}


/*!
 *  send a QString
 */

void dtkDistributedCommunicatorMpi::send(const QString &s, qint16 target, int tag)
{
    QByteArray Array = s.toUtf8();
    dtkDistributedCommunicatorMpi::send(Array, target, tag);
}

void dtkDistributedCommunicatorMpi::receive(QString &s, qint16 source, int tag)
{
    QByteArray array;
    this->receive(array, source, tag);
    s = QString(array);
}

void dtkDistributedCommunicatorMpi::broadcast(QString &s, qint16 source)
{
    QByteArray array;
    if (d->rank == source) {
        array = s.toUtf8();
    }
    this->broadcast(array, source);
    if (d->rank != source) {
        s = QString(array);
    }
}


void dtkDistributedCommunicatorMpi::send(QByteArray &array, qint16 target, int tag)
{
    qint64   arrayLength = array.length();
    dtkDistributedCommunicator::send(array.data(), arrayLength, target, tag);

}

void dtkDistributedCommunicatorMpi::receive(QByteArray &array, qint16 source, int tag)
{
    dtkDistributedCommunicatorStatus status;
    this->receive(array, source, tag, status);
}

void dtkDistributedCommunicatorMpi::broadcast(QByteArray &array, qint16 source)
{
    MPI_Comm mpi_comm = d->comm;

    int size;
    if (source == ROOT ) {
        size = array.size();
    }
    MPI_Bcast(&size, 1, data_type(dtkDistributedCommunicatorInt), source, mpi_comm);
    if (source != ROOT ) {
        array.resize(size);
    }
    MPI_Bcast(array.data(), size, data_type(dtkDistributedCommunicatorChar), source, mpi_comm);
}

void dtkDistributedCommunicatorMpi::receive(QByteArray &array, qint16 source, int tag, dtkDistributedCommunicatorStatus& status )
{
    MPI_Status mpi_status;
    MPI_Probe(source, tag, d->comm, &mpi_status);

    int count;
    MPI_Get_count(&mpi_status, MPI::CHAR, &count);

    status.setCount(count);

    status.setTag(mpi_status.MPI_TAG);
    status.setSource(mpi_status.MPI_SOURCE);
    status.setError(mpi_status.MPI_ERROR);
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
    MPI_Barrier(d->comm);
}

//! Broadcast.
/*!
 *  Broadcasts (sends) a message from the process with rank "source"
 *  to all other processes in the group.
 */

void dtkDistributedCommunicatorMpi::broadcast(void *data, qint64 size, DataType dataType, qint16 source)
{
    MPI_Bcast(data, size, data_type(dataType), source, d->comm);
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
        MPI_Allgather(send, size, data_type(dataType), recv, size, data_type(dataType), d->comm);
    else
        MPI_Gather(send, size, data_type(dataType), recv, size, data_type(dataType), target, d->comm);
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
    MPI_Scatter(send, size, data_type(dataType), recv, size, data_type(dataType), source, d->comm);
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
        MPI_Allreduce(send, recv, size, data_type(dataType), operation_type(operationType), d->comm);
    else
        MPI_Reduce(send, recv, size, data_type(dataType), operation_type(operationType), target, d->comm);
}

// /////////////////////////////////////////////////////////////////
// Documentation
// /////////////////////////////////////////////////////////////////

//! \class dtkDistributedCommunicatorMpi
/*! 
 *  \brief A mpi based dtk communicator.
 */
