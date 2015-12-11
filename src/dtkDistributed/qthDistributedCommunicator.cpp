// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#include "qthDistributedCommunicator.h"
#include "qthDistributedBufferManager.h"

#include <dtkDistributed>

#include <dtkCore/dtkSpinLock.h>

#include <dtkLog>

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// helper functions
// ///////////////////////////////////////////////////////////////////

template<typename T> struct max : public std::binary_function<T, T, T>
{
  /** @returns the maximum of x and y. */
  const T& operator()(const T& x, const T& y) const
  {
    return x < y? y : x;
  }
};

template<typename T> struct min : public std::binary_function<T, T, T>
{
  const T& operator()(const T& x, const T& y) const
  {
    return x < y? x : y;
  }
};

template <typename T> void applyOperation(T *output, T *input, qlonglong size,dtkDistributedCommunicator::OperationType operationType)
{

    dtkArray<T> result = dtkArray<T>::fromWritableRawData(output, size);
    const dtkArray<T> tmp = dtkArray<T>::fromRawData(input, size);

    switch (operationType)
    {
    case dtkDistributedCommunicator::Sum:
        std::transform(result.begin(), result.end(), tmp.begin(), result.begin(), std::plus<T>());
        break;
    case dtkDistributedCommunicator::Min:
        std::transform(result.begin(), result.end(), tmp.begin(), result.begin(), min<T>());
        break;
    case dtkDistributedCommunicator::Max:
        std::transform(result.begin(), result.end(), tmp.begin(), result.begin(), max<T>());
        break;
    case dtkDistributedCommunicator::Product:
        std::transform(result.begin(), result.end(), tmp.begin(), result.begin(), std::multiplies<T>());
        break;
    case dtkDistributedCommunicator::None:
        break;
    default:
        qWarning() << "operation" << operationType << "not implemented in qthread plugin";
        break;
    }
}

// ///////////////////////////////////////////////////////////////////
// helper class
// ///////////////////////////////////////////////////////////////////

class qthTask: public QRunnable
{

public:
    qthDistributedCommunicator *m_comm;
    QRunnable *m_task;
    qlonglong  m_wid;

    void run(void) {
        m_comm->setWid(m_wid);
        dtkTrace()<< "run task wid" << m_wid;
        m_comm->barrier();
        m_task->run();
        m_comm->barrier();
    }
};

// ///////////////////////////////////////////////////////////////////
// qthDistributedRequest
// ///////////////////////////////////////////////////////////////////

class qthDistributedRequest: public dtkDistributedRequest
{
public:
    qlonglong m_size;
    qint32    m_source;
    qint32    m_tag;
    void     *m_data;
    QMetaType::Type m_dataType;

public:
    qthDistributedRequest(void *&data, qint64 size, QMetaType::Type dataType, qint32 source, qint32 tag) {
        m_size     = size;
        m_dataType = dataType;
        m_source   = source;
        m_tag      = tag;
        m_data     = data;
    }
};

// ///////////////////////////////////////////////////////////////////
// Data "pimpl" class (not to be used directly)
// ///////////////////////////////////////////////////////////////////

class BarrierPrivate
{
public:
    BarrierPrivate(int count) : m_count(count), initial_count(count) {}

    void wait() {
        mutex.lock();
        --m_count;
        if (m_count > 0) {
            condition.wait(&mutex);
            mutex.unlock();
        } else {
            m_count=initial_count;
            mutex.unlock();
            condition.wakeAll();
        }
    }
private:
    Q_DISABLE_COPY(BarrierPrivate)
    int m_count;
    int initial_count;
    QMutex mutex;
    QWaitCondition condition;
};

// /////////////////////////////////////////////////////////////////
// class Barrier
// /////////////////////////////////////////////////////////////////

class Barrier {
public:
    // Create a barrier that will wait for count threads
    Barrier(int count) : d(new BarrierPrivate(count)) {}
    void wait() {
        d->wait();
    }

private:
    QSharedPointer<BarrierPrivate> d;
};

// ///////////////////////////////////////////////////////////////////
// class qthDistributedLocalMessage
// ///////////////////////////////////////////////////////////////////

class qthDistributedLocalMessage
{
public:
    qthDistributedLocalMessage(void);
    qthDistributedLocalMessage(QVariant v, qint32 source, qint32 tag);
    qthDistributedLocalMessage(QByteArray a, qint32 source, qint32 tag);
    qthDistributedLocalMessage(void *buf, qlonglong bytesize, qint32 source, qint32 tag);
    virtual ~qthDistributedLocalMessage();

public:
    qint32 tag;
    qint32 source;
    QVariant variant;
    QByteArray array;
    void *buffer;
    qlonglong buffer_size;
};

// ///////////////////////////////////////////////////////////////////

qthDistributedLocalMessage::qthDistributedLocalMessage(void)
{
    buffer_size = 0;
    buffer      = NULL;
    this->tag = 0;
    this->source = -1;
}

qthDistributedLocalMessage::qthDistributedLocalMessage(QVariant v, qint32 source, qint32 tag)
{
    buffer_size = 0;
    buffer      = NULL;
    this->tag    = tag;
    this->source = source;
    this->variant   = v;
}

qthDistributedLocalMessage::qthDistributedLocalMessage(QByteArray a, qint32 source, qint32 tag)
{
    buffer_size = 0;
    buffer      = NULL;
    this->tag    = tag;
    this->source = source;
    this->array   = a;
}

qthDistributedLocalMessage::qthDistributedLocalMessage(void *b, qlonglong bytesize, qint32 source, qint32 tag)
{
    buffer_size  = bytesize;
    this->tag    = tag;
    this->source = source;
    this->buffer = malloc(bytesize);
    memcpy(this->buffer, b, bytesize);
}

qthDistributedLocalMessage::~qthDistributedLocalMessage(void)
{
    if (buffer)
        free(buffer);
}

// /////////////////////////////////////////////////////////////////
// qthDistributedCommunicatorPrivate
// /////////////////////////////////////////////////////////////////

class qthDistributedCommunicatorPrivate
{
public:
    qlonglong id;  // for buffers
    qlonglong size;
    QVector<void *> buffers;
    QVector<QReadWriteLock *> locks;
    QHash<QThread *, qint32 > wids;
    QVector< QList<qthDistributedLocalMessage *> > msgbox;
    QVector< QList<qthDistributedLocalMessage *> > freelist;
    QVector< dtkSpinLock *>  msg_mutex;
    QVector< qlonglong > size_map; //store the size of items
    QVector< bool >     is_locked;
    bool active;

public:
    QThreadPool pool;
public:
    QVector< qlonglong >  buffer_ids;
    QVector< QVector<qlonglong> >  buffer_map;
    QMutex  mutex; //global mutex

public:
    dtkDistributedBufferManager *buffer_manager;

public:
    Barrier *barrier;

public:
    bool initialized;
};

// /////////////////////////////////////////////////////////////////
// qthDistributedCommunicator
// /////////////////////////////////////////////////////////////////

qthDistributedCommunicator::qthDistributedCommunicator(void) : dtkDistributedCommunicator(), d(new qthDistributedCommunicatorPrivate)
{
    d->size = 1;
    d->id   = 0;
    d->active = false;
    d->barrier = NULL;
    d->initialized = false;
    d->buffer_manager = 0;
}

qthDistributedCommunicator::~qthDistributedCommunicator(void)
{
    d->mutex.lock();
    for (int i = 0; i < d->msg_mutex.size(); ++i) {
        if (d->msg_mutex[i])
            delete d->msg_mutex[i];
    }
    for (int i = 0; i < d->freelist.size(); ++i) {
        foreach(qthDistributedLocalMessage* msg,  d->freelist[i]) {
            if (msg)
                delete msg;
        }
        d->freelist[i].clear();
    }
    d->msg_mutex.clear();
    d->mutex.unlock();

    this->uninitialize();

    if (d->barrier)
        delete d->barrier;

    delete d;

    d = NULL;
}

void qthDistributedCommunicator::spawn(QStringList hostnames, QString wrapper, QMap<QString, QString> options)
{
    Q_UNUSED(wrapper);
    Q_UNUSED(options);

    qlonglong np = hostnames.count();

    dtkDebug() << "spawning" << np << "qthreads on "<< hostnames;

    if (!d->barrier)
        d->barrier = new Barrier(np);

    d->size    = np;
    if (dtkDistributed::app()->noGui())
        d->pool.setMaxThreadCount(np);
    else
        d->pool.setMaxThreadCount(np-1);
    d->pool.setExpiryTimeout(-1);
    d->buffer_ids.resize(np);
    d->buffer_map.resize(np);
    d->locks.resize(np);
    d->buffers.resize(np);
    d->msgbox.resize(np);
    d->freelist.resize(np);
    d->msg_mutex.resize(np);
    for (int i = 0; i < np; ++i) {
        dtkSpinLock *mutex = new dtkSpinLock;
        d->msg_mutex[i] = mutex;
        d->buffer_ids[i] = 0;
    }
}

void qthDistributedCommunicator::unspawn(void)
{
    d->id = 0;
}

void qthDistributedCommunicator::initialize(void)
{
    d->initialized = true;
}

// qthread communicators are always active
bool qthDistributedCommunicator::active(void)
{
    return d->active;
}

void qthDistributedCommunicator::exec(QRunnable *work)
{
    d->active = true;
    if (dtkDistributed::app()->noGui()) {
        for (int i = 0; i< d->size; ++i) {
            qthTask *task = new qthTask;
            task->m_wid  = i;
            task->m_comm = this;
            task->m_task = work;
            task->setAutoDelete(true);
            d->pool.start(task);
        }
    } else {
        dtkDebug() << "GUI application, run rank 0 in main thread";
        for (int i = 1; i< d->size; ++i) {
            qthTask *task = new qthTask;
            task->m_wid  = i;
            task->m_comm = this;
            task->m_task = work;
            task->setAutoDelete(true);
            d->pool.start(task);
        }
        dtkDebug() << "GUI application, run main thread code";
        qthTask task;
        task.m_wid  = 0;
        task.m_comm = this;
        task.m_task = work;
        task.run();
        dtkDebug() << "GUI application, done, wait for other threads";
    }
    d->pool.waitForDone();
    d->active = false;
}

bool qthDistributedCommunicator::initialized(void)
{
    return d->initialized;
}

void qthDistributedCommunicator::uninitialize(void)
{
    d->pool.waitForDone();
    d->wids.clear();
}

void qthDistributedCommunicator::barrier(void)
{
    if (!d->active)
        return;
    d->barrier->wait();
}

qint32 qthDistributedCommunicator::wid(void)
{
    if (!d->active)
        return 0;
    return d->wids.value(QThread::currentThread(),0);
}

void qthDistributedCommunicator::setWid(qint32 id)
{
    d->mutex.lock();
    d->wids.insert(QThread::currentThread(), id);
    d->mutex.unlock();
}

qint32 qthDistributedCommunicator::size(void)
{
    if (!d->active)
        return 1;
    return d->size;

}

dtkDistributedBufferManager *qthDistributedCommunicator::createBufferManager(void)
{
    this->barrier();
    d->mutex.lock();
    if (this->wid() == 0) {
        d->buffer_manager = new qthDistributedBufferManager(this);
    }
    d->mutex.unlock();
    this->barrier();

    return d->buffer_manager;
}

void qthDistributedCommunicator::destroyBufferManager(dtkDistributedBufferManager *& buffer_manager)
{
    this->barrier();
    d->mutex.lock();
    if (this->wid() == 0) {
        delete buffer_manager;
    }
    d->mutex.unlock();
    this->barrier();
    buffer_manager = NULL;
}

void qthDistributedCommunicator::send(void *data, qint64 size, QMetaType::Type dataType, qint32 target, qint32 tag)
{
    qint32 source = wid();
    qthDistributedLocalMessage *msg;

    dtkSpinLock *mutex = d->msg_mutex[target];
    qlonglong bytesize = size * QMetaType::sizeOf(dataType);

    mutex->lock();

    if (d->freelist[target].isEmpty()) {
        msg = new qthDistributedLocalMessage(data, bytesize , source, tag);
    } else {
        msg = d->freelist[target].takeFirst();
        msg->tag = tag;
        msg->source = source;
        if (msg->buffer_size != bytesize){
            msg->buffer = realloc(msg->buffer, bytesize);
            msg->buffer_size = bytesize;
        }
        memcpy(msg->buffer, data, bytesize);
    }
    d->msgbox[target].append(msg);
    mutex->unlock();
}

void qthDistributedCommunicator::send(QByteArray &array, qint32 target, qint32 tag)
{
    qint32 source = wid();
    qthDistributedLocalMessage *msg;

    dtkSpinLock *mutex = d->msg_mutex[target];

    mutex->lock();

    if (d->freelist[target].isEmpty()) {
        msg = new qthDistributedLocalMessage(array, source, tag);
    } else {
        msg = d->freelist[target].takeFirst();
        msg->tag = tag;
        msg->source = source;
        msg->array = array;
    }
    d->msgbox[target].append(msg);
    mutex->unlock();
}

void qthDistributedCommunicator::broadcast(void *data,  qint64 size, QMetaType::Type dataType, qint32 source)
{
    if (d->size == 1)
        return;

    qint32 me = wid();
    qthDistributedLocalMessage *msg ;
    qlonglong bytesize = size * QMetaType::sizeOf(dataType);
    if (me == source) {

        if (d->freelist[source].isEmpty()) {
            msg = new qthDistributedLocalMessage(data, bytesize, source, dtkDistributedCommunicator::BCAST_TAG);
        } else {
            msg = d->freelist[source].takeFirst();
            msg->source = source;
            msg->tag    = dtkDistributedCommunicator::BCAST_TAG;
            if (msg->buffer_size != bytesize){
                msg->buffer = realloc(msg->buffer, bytesize);
                msg->buffer_size = bytesize;
            }
            memcpy(msg->buffer, data, bytesize);
        }

        for (int i = 0; i < d->size; ++i) {
            if (i != source) {
                d->msg_mutex[i]->lock();
                d->msgbox[i].append(msg);
                d->msg_mutex[i]->unlock();
            }
        }
        barrier();
        d->freelist[source].append(msg);
        //FIXME:should we lock the freelist ?
    } else {
        QList< qthDistributedLocalMessage* > *box = &(d->msgbox[me]);

        while (true) { // busy wait for a message

            d->msg_mutex[me]->lock();
            int size = box->size();
            for (int i = 0; i < size; ++i) {
                msg = box->at(i);
                if (msg->tag == dtkDistributedCommunicator::BCAST_TAG) {
                    msg = d->msgbox[me].takeAt(i);
                    d->msg_mutex[me]->unlock();
                    // FIXME: handle null pointer ?
                    memcpy(data, msg->buffer, bytesize);

                    d->barrier->wait();
                    return;
                }
            }
            d->msg_mutex[me]->unlock();
        }
    }
}
void qthDistributedCommunicator::broadcast(QByteArray &array, qint32 source)
{
    if (d->size == 1)
        return;
    QVariant v(array);
    this->broadcast(v, source);
    qint32 me = wid();
    if (me != source) {
        array = v.toByteArray();
    }
}

void qthDistributedCommunicator::broadcast(QVariant &v, qint32 source)
{
    if (d->size == 1)
        return;
    qint32 me = wid();
    qthDistributedLocalMessage *msg ;
    if (me == source) {

        if (d->freelist[source].isEmpty()) {
            msg = new qthDistributedLocalMessage(v, source, dtkDistributedCommunicator::BCAST_TAG);
        } else {
            msg = d->freelist[source].takeFirst();
            msg->source = source;
            msg->tag    = dtkDistributedCommunicator::BCAST_TAG;
            msg->variant = v;
        }

        for (int i = 0; i < d->size; ++i) {
            if (i != source) {
                d->msg_mutex[i]->lock();
                d->msgbox[i].append(msg);
                d->msg_mutex[i]->unlock();
            }
        }
        barrier();
        d->freelist[source].append(msg);
        //FIXME:should we lock the freelist ?
    } else {
        QList< qthDistributedLocalMessage* > *box = &(d->msgbox[me]);

        while (true) { // busy wait for a message

            d->msg_mutex[me]->lock();
            int size = box->size();
            for (int i = 0; i < size; ++i) {
                msg = box->at(i);
                if (msg->tag == dtkDistributedCommunicator::BCAST_TAG) {
                    msg = d->msgbox[me].takeAt(i);
                    d->msg_mutex[me]->unlock();

                    v = msg->variant;
                    d->barrier->wait();
                    return;
                }
            }
            d->msg_mutex[me]->unlock();
        }
    }
}

void qthDistributedCommunicator::receive(void *data, qint64 size, QMetaType::Type dataType, qint32 source, qint32 tag)
{
    qint32 target = wid();

    dtkSpinLock *mutex = d->msg_mutex[target];

    qthDistributedLocalMessage *msg ;

    QList< qthDistributedLocalMessage* > *box =&( d->msgbox[target]);
    qlonglong bytesize = size * QMetaType::sizeOf(dataType);

    while (true) { // busy wait for a message
        mutex->lock();
        int bsize = box->size();
        for (int i = 0; i < bsize; ++i) {
            msg = box->at(i);
            if (msg->tag == tag && msg->source == source ) {
                memcpy(data, msg->buffer, bytesize);
                d->msgbox[target].removeAt(i);
                d->freelist[target].append(msg);
                mutex->unlock();
                return;
            }
        }
        mutex->unlock();
    }
}

void qthDistributedCommunicator::receive(QByteArray &array, qint32 source, qint32 tag, dtkDistributedCommunicatorStatus& status )
{
    receive(array, source, tag);
}

void qthDistributedCommunicator::receive(QByteArray &array, qint32 source, qint32 tag)
{
    qint32 target = wid();

    dtkSpinLock *mutex = d->msg_mutex[target];

    qthDistributedLocalMessage *msg ;

    QList< qthDistributedLocalMessage* > *box =&( d->msgbox[target]);

    while (true) { // busy wait for a message
        mutex->lock();
        int size = box->size();
        for (int i = 0; i < size; ++i) {
            msg = box->at(i);
            if (msg->tag == tag && msg->source == source ) {
                array = msg->array;
                d->msgbox[target].removeAt(i);
                d->freelist[target].append(msg);
                mutex->unlock();
                return;
            }
        }
        mutex->unlock();
    }
}

dtkDistributedRequest *qthDistributedCommunicator::ireceive(void *data, qint64 size, QMetaType::Type dataType, qint32 source, qint32 tag)
{
    return new qthDistributedRequest(data, size, dataType, source, tag);
}

void qthDistributedCommunicator::gather(void *send, void *recv, qint64 size, QMetaType::Type dataType, qint32 root, bool all)
{
    qint32 wid  = this->wid();
    qint32 world_size = this->size();

    qlonglong bytesize = size * QMetaType::sizeOf(dataType);
    barrier();
    if (wid == root){
        char *offset_ptr = static_cast<char*>(recv) ;
        for(qlonglong i = 0; i < d->size; ++i ){
            if (i != root) {
                offset_ptr += bytesize;
                receive(static_cast<void*>(offset_ptr), size, dataType, i, TagGather);
            } else {
                memcpy(recv, send, bytesize);
            }
        }
        if (all) {
            broadcast(recv, size * world_size, dataType, root);
        }

    } else {
        this->send(send, size, dataType, root, TagGather);
        if (all) {
            broadcast(recv, size * world_size, dataType, root);
        }
    }
}

void qthDistributedCommunicator::reduce(void *send, void *recv, qint64 size, QMetaType::Type dataType, OperationType operationType, qint32 root, bool all)
{
    qint32 wid = this->wid();

    qlonglong bytesize = size * QMetaType::sizeOf(dataType);
    barrier();
    if (wid == root){
        void *buffer = malloc(bytesize);
        memcpy(recv, send, bytesize);
        for(qlonglong i =0; i < d->size; ++i ){
            if (i != root) {
                receive(buffer, size, dataType, i, TagReduce);
                switch (dataType)
                {
                case QMetaType::LongLong:
                case QMetaType::Long:
                    applyOperation(static_cast<qlonglong *>(recv), static_cast<qlonglong *>(buffer), size, operationType);
                    break;
                case QMetaType::Int:
                    applyOperation(static_cast<int *>(recv), static_cast<int *>(buffer), size, operationType);
                    break;
                case QMetaType::Double:
                    applyOperation(static_cast<double *>(recv), static_cast<double *>(buffer), size, operationType);
                    break;
                case QMetaType::Float:
                    applyOperation(static_cast<float *>(recv), static_cast<float *>(buffer), size, operationType);
                    break;
                default:
                    qWarning() << "type"<< dataType << "is not handle in reduce";
                    break;
                }
            }
        }
        if (all) {
            broadcast(recv, size, dataType, root);
        }
        free(buffer);

    } else {
        this->send(send, size, dataType, root, TagReduce);
        if (all) {
            broadcast(recv, size, dataType, root);
        }
    }
}


void qthDistributedCommunicator::wait(dtkDistributedRequest *dtkreq)
{
    qthDistributedRequest *req= dynamic_cast<qthDistributedRequest*>(dtkreq);
    receive(req->m_data, req->m_size, req->m_dataType, req->m_source, req->m_tag);

}

//
// qthDistributedCommunicator.cpp ends here
