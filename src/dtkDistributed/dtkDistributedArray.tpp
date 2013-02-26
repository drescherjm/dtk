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

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template<typename T> dtkDistributedArray<T>::dtkDistributedArray(const qlonglong& count) : dtkDistributedContainerIndexed<T>(), dtkDistributedContainerSequence<T>(), m_count(count), m_buffer_count(count/2)
{
    handler.setArray(this);
}

template<typename T> dtkDistributedArray<T>::dtkDistributedArray(const dtkDistributedArray<T>& other)
{

}

template<typename T> dtkDistributedArray<T>::~dtkDistributedArray(void)
{

}

template<typename T> QString dtkDistributedArray<T>::identifier(void) const 
{ 
    return "dtkDistributedArray"; 
}

template<typename T> dtkDistributedArray<T> *dtkDistributedArray<T>::clone(void)
{
    return new dtkDistributedArray<T>(*this);
}

template<typename T> void dtkDistributedArray<T>::clear(void)
{

}

template<typename T> bool dtkDistributedArray<T>::empty(void) const
{
    return false;
}

template<typename T> qlonglong dtkDistributedArray<T>::count(void) const
{
    return handler.count();
}

