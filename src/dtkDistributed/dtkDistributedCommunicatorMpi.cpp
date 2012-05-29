/* dtkCommunicatorMpi.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:51:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: mar. mai 29 09:47:06 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 578
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

dtkDistributedCommunicatorMpi::dtkDistributedCommunicatorMpi(const dtkDistributedCommunicatorMpi& c)
{

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

void dtkDistributedCommunicatorMpi::receive(void *data, qint64 size, DataType dataType, qint16 source, int tag, int& from)
{
    MPI::Status status;
    MPI::COMM_WORLD.Recv(data, size, data_type(dataType), source, tag, status);
    from = status.Get_source();
}


/*!
 *  send a dtkAbstractData object; we need to send it's type (with the
 *  size type) and then serialize the object.
 */

void dtkDistributedCommunicatorMpi::send(dtkAbstractData *data, qint16 target, int tag)
{

    QString type = data->identifier();
    qint64  typeLength = type.length()+1;
    qint64  s=1;
    dtkDistributedCommunicator::send(&typeLength,s,target,tag);

    QByteArray typeArray = type.toAscii();
    char *typeChar = typeArray.data();
    dtkDistributedCommunicator::send(typeChar,typeLength,target,tag);

    QByteArray *array = data->serialize();
    if (!array) {
        dtkError() <<"serialization failed";
    } else {
        qint64   arrayLength = array->length();
        dtkDistributedCommunicator::send(&arrayLength,1,target,tag);
        dtkDistributedCommunicator::send(array->data(),arrayLength,target,tag);
    }
}

void dtkDistributedCommunicatorMpi::receive(dtkAbstractData *&data, qint16 source, int tag)
{
    qint64   typeLength;
    qint64   arrayLength;

    dtkDistributedCommunicator::receive(&typeLength,1,source,tag);
    char     type[typeLength];

    dtkDistributedCommunicator::receive(type, typeLength, source,tag);
    dtkDistributedCommunicator::receive(&arrayLength,1,source,tag);

    char     rawArray[arrayLength];
    dtkDistributedCommunicator::receive(rawArray, arrayLength, source,tag);

    if(!data) {
        data = dtkAbstractDataFactory::instance()->create(QString(type));
        if (!data) {
            dtkWarn() << "Can't instantiate object of type" << QString(type);
            return;
        }
    } else
        if(data->identifier() != QString(type))
            dtkWarn() << DTK_PRETTY_FUNCTION << "Warning, type mismatch";

    QByteArray array = QByteArray::fromRawData(rawArray, arrayLength);
    // FIXME: array is not null-terminated, does it matter ??

    data = data->deserialize(array);
    if (!data)
        dtkError() << "Warning: deserialization failed";
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

/*!
 *  send a QVariant
 */

void dtkDistributedCommunicatorMpi::send(const QVariant &v, qint16 target, int tag)
{
    int     type = (int)v.type();
    qint64  size = 1;
    dtkDistributedCommunicator::send(&type,1,target,tag);

    switch (v.type()) {
    case QVariant::Double: {
        double data = v.toDouble();
        dtkDistributedCommunicator::send(&data,size,target,tag);
        break;
    }
    case QVariant::LongLong: {
        qint64 data = v.toLongLong();
        dtkDistributedCommunicator::send(&data,size,target,tag);
        break;
    }
    case QVariant::String: {
        QString data = v.toString();
        this->send(data,target,tag);
        break;
    }
    case QVariant::UserType: {
        int typeId = QMetaType::type(v.typeName());
        dtkDistributedCommunicator::send(&typeId,size,target,tag);
        if (QString(v.typeName()) == "dtkAbstractData*") {
            dtkAbstractData *data = v.value<dtkAbstractData *>();
            this->send(data,target,tag);
        } else if (QString(v.typeName()) == "dtkVector3DReal") {
            dtkVector3DReal vector = v.value<dtkVector3DReal>();
            double array[3];
            for (int i=0; i<3; i++)
                array[i]= vector[i];
            dtkDistributedCommunicator::send(array,3,target,tag);
        } else if (QString(v.typeName()) == "dtkQuaternionReal") {
            dtkQuaternionReal q = v .value<dtkQuaternionReal>();
            double array[4];
            for (int i=0; i<4; i++)
                array[i]= q[i];
            dtkDistributedCommunicator::send(array,4,target,tag);
        } else {
            dtkError() << "unimplemendted type in send" << v.typeName();
        }
        return;
    }
    default:
        break;
    }
}

void dtkDistributedCommunicatorMpi::receive(QString &s, qint16 source, int tag)
{
    qint64   length;
    dtkDistributedCommunicator::receive(&length,1,source,tag);
    char     s_c[length];

    dtkDistributedCommunicator::receive(s_c, length, source,tag);
    s = QString(s_c);
}

void dtkDistributedCommunicatorMpi::receive(QVariant &v, qint16 source, int tag)
{
    int   type;
    dtkDistributedCommunicator::receive(&type,1,source,tag);

    switch (type) {
    case QVariant::Double: {
        double data;
        dtkDistributedCommunicator::receive(&data,1,source,tag);
        v=QVariant(data);
        break;
    }
    case QVariant::LongLong: {
        qint64 data;
        dtkDistributedCommunicator::receive(&data,1,source,tag);
        v=QVariant(data);
        break;
    }
    case QVariant::String: {
        QString data ;
        this->receive(data,source,tag);
        v=QVariant(data);
        break;
    }
    case QVariant::UserType: {
        int   typeId;
        dtkDistributedCommunicator::receive(&typeId,1,source,tag);
        if ( QString(QMetaType::typeName(typeId)) == "dtkVector3DReal") {
            double   values[3];
            dtkDistributedCommunicator::receive(values,3,source,tag);
            dtkVector3DReal vector;
            for (int i=0; i<3; i++)
                vector[i]= values[i];
            v = qVariantFromValue(vector);
        } else if (QString(QMetaType::typeName(typeId)) == "dtkQuaternionReal") {
            double   values[4];
            dtkDistributedCommunicator::receive(values,4,source,tag);
            dtkQuaternionReal quaternion;
            for (int i=0; i<4; i++)
                quaternion[i]= values[i];
            v = qVariantFromValue(quaternion);
        } else if (QString(QMetaType::typeName(typeId)) == "dtkAbstractData*") {
            dtkAbstractData *data = NULL;
            this->receive(data,source,tag);
            v = qVariantFromValue(data);
        } else {
            dtkError() << "unimplemendted type in receive" <<QMetaType::typeName(typeId);
        }
        return;
    }
    default:
        break;
    }

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
