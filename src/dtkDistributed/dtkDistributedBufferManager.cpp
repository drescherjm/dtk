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

/*!
  \class dtkDistributedBufferManager
  \inmodule dtkDistributed
  \brief dtkDistributedBufferManager is the interface for distributed buffer memory management.

  dtkDistributedBufferManager unifies the way a distributed buffer is
  managed whatever the kind of parallelism (e.g. MPI, multi-thread,
  etc).
  
  For each implementation of the communicator, there is an
  implementation of buffer manager. This communicator is in charge for
  creating and destroying the manager:

  \code
  dtkDistributedCommunicator *comm = dtkDistributed::communicator()::instance();
  dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();
  comm->destroyBufferManager(buffer_manager);
  \endcode

  The dtkDistributedBufferManager provides methods to:
  \list
  \li allocate/deallocate a distributed buffer, 
  \li lock/unlock the buffer owned by a given process, 
  \li get data stored in a local or remote part of the buffer
  \li put (ie set) data into a local or remote part of the buffer.
  \endlist

  Here is an example showing how to use the buffer manager:

  \code
  dtkDistributedCommunicator *comm = dtkDistributed::communicator::instance();   
  qlonglong pu_count = comm->size();
  qlonglong wid = comm->wid();
  
  dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();
  qlonglong N = 1000001;
  qlonglong *array = NULL;
  array = buffer_manager->allocate<qlonglong>(N);
  
  comm->barrier();
  if (comm->wid() == 0) {
     for(qlonglong i = 0; i < pu_count * N; ++i) {
        buffer_manager->put(i/N, i%N, &i);
     }
  }
  comm->barrier();

  buffer_manager->rlock(wid);
  for(qlonglong i = 0; i < N; ++i) {
     if (array[i] != (i + wid * N)) 
        qDebug() << "Value" << array[i] << "is incorrect." << (i + wid * N) << "was expected instead."
  }
  buffer_manager->unlock(wid);

  comm->barrier();
  if (comm->wid() == 0) {
     qlonglong temp;
     for(qlonglong i = 0; i < N * pu_count; ++i) {
        buffer_manager->get(i/N, i%N, &temp);
        if (temp != i) 
           qDebug() << "Value" << temp << "is incorrect." << i << "was expected instead."
     }
  }

  buffer_manager->deallocate(array);
  comm->destroyBufferManager(buffer_manager);

  \endcode

 */

/*! \fn dtkDistributedBufferManager::~dtkDistributedBufferManager(void)

    Virtual destructutor.
*/
    
/*! \fn T *dtkDistributedBufferManager::allocate(qlonglong capacity);

    Returns a buffer of type \c T and size \a capacity.

    \sa deallocate()
*/
    
/*! \fn void  dtkDistributedBufferManager::deallocate(T *& buffer);

    Deallocates \a buffer and makes it pointing to null pointer.

    \sa allocate()
*/
   
/*! \fn void *dtkDistributedBufferManager::allocate(qlonglong objectSize, qlonglong capacity)

    Protected function that returns a buffer which bitsize is \a objectSize * \a capacity.
*/
   
/*! \fn void  dtkDistributedBufferManager::deallocate(void *buffer, qlonglong objectSize)
  
    Protected function that deallocates \a buffer whose type has size \a objectSize.
*/
   
/*! \fn void dtkDistributedBufferManager::rlock(qlonglong wid)

    Locks for read the buffer managed by process \a wid.

    \sa wlock(), unlock(), locked()
 */

/*! \fn void dtkDistributedBufferManager::rlock(void)

    Locks for read the buffer managed by all processes.

    \sa wlock(), unlock(), locked()
 */

/*! \fn void dtkDistributedBufferManager::wlock(qlonglong wid)

    Locks for write the buffer managed by process \a wid.

    \sa rlock(), unlock(), locked()
*/

/*! \fn void dtkDistributedBufferManager::wlock(void)

    Locks for write the buffer managed by all processes.

    \sa rlock(), unlock(), locked()
*/
   
/*! \fn void dtkDistributedBufferManager::unlock(qlonglong wid)

    Unlocks the buffer managed by process \a wid.

    \sa rlock(), wlock(), locked()
 */

/*! \fn void dtkDistributedBufferManager::unlock(void)

    Unlocks all the buffers.

    \sa rlock(), wlock(), locked()
 */

/*! \fn bool dtkDistributedBufferManager::locked(qlonglong wid)

    Returns true if the buffer of process \a wid has been previously locked.

    \sa rlock(), wlock(), unlock()
*/
   
/*! \fn void dtkDistributedBufferManager::get(qint32 from, qlonglong position, void *array, qlonglong count = 1)

    Copies \a count items from the part of the buffer owned by process \a from starting at index \a position into \a array.

    \sa put()
 */
   
/*! \fn void dtkDistributedBufferManager::put(qint32 dest, qlonglong position, void *array, qlonglong count = 1)

    Copies \a count items of \a array into the part of the buffer owned by process \a dest starting at index \a position.

    \sa get()
 */

// 
// dtkDistributedBufferManager.cpp ends here
