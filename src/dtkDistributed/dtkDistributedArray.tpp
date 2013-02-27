/* dtkDistributedArray.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Mon Feb 18 08:30:17 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

//#prama once


class dtkDistributedCommunicator;

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template<typename T> dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& count, dtkDistributedWorker *worker) : m_handler(new dtkDistributedArrayHandler<T>(count, worker))
{

}

template<typename T> dtkDistributedArray<T>::~dtkDistributedArray(void)
{
    if (m_handler)
        delete m_handler;
}

template<typename T> void dtkDistributedArray<T>::clear(void)
{
    return m_handler->clear();
}

template<typename T> bool dtkDistributedArray<T>::empty(void) const
{
    return m_handler->empty();
}

template<typename T> qlonglong dtkDistributedArray<T>::count(void) const
{
    return m_handler->count();
}

template<typename T> void dtkDistributedArray<T>::set(const qlonglong& index, const T& value)
{
    m_handler->set(index, value);
}

template<typename T> T dtkDistributedArray<T>::at(const qlonglong& index) const
{
    return m_handler->at(index);
}

template<typename T> T dtkDistributedArray<T>::first(void) const
{
    return m_handler->first();
}

template<typename T> T dtkDistributedArray<T>::last(void) const
{
    return m_handler->last();
}

template<typename T> dtkDistributedMapper *dtkDistributedArray<T>::mapper(void)
{
    return m_handler->m_mapper;
}

template<typename T> dtkDistributedArrayItem<T> dtkDistributedArray<T>::operator [] (const qlonglong& index)
{
    return dtkDistributedArrayItem<T>(this, index);
}

