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

#include "dtkDistributedArray.h"

/*!
  \class dtkDistributedArray
  \inmodule dtkDistributed
  \brief The 

  
*/

/*! \fn dtkDistributedArray::dtkDistributedArray(const qlonglong& size)
\internal 
*/

/*! \fn dtkDistributedArray::dtkDistributedArray(const qlonglong& size, dtkDistributedMapper *mapper)
\internal 
*/

/*! \fn dtkDistributedArray::dtkDistributedArray(const qlonglong& size, const T& init_value)
\internal 
*/

/*! \fn dtkDistributedArray::dtkDistributedArray(const qlonglong& size, const T *array)
\internal 
*/

/*! \fn dtkDistributedArray::dtkDistributedArray(const dtkArray<T> &array)
\internal 
*/

/*! \fn dtkDistributedArray::dtkDistributedArray(const dtkDistributedArray& other)
\internal 
*/

/*! \fn dtkDistributedArray::~dtkDistributedArray(void)
\internal 
*/

/*! \fn dtkDistributedArray& dtkDistributedArray::operator = (const dtkDistributedArray& other)
\internal 
*/

/*! \fn void dtkDistributedArray::remap(dtkDistributedMapper *remapper)
   \internal 
*/

/*! \fn void dtkDistributedArray::rlock(qint32 owner)
  \internal 
*/

/*! \fn void dtkDistributedArray::wlock(qint32 owner)
  \internal 
*/

/*! \fn void dtkDistributedArray::unlock(qint32 owner)
  \internal 
*/

/*! \fn void dtkDistributedArray::rlock(void)
  \internal 
*/

/*! \fn void dtkDistributedArray::wlock(void)
  \internal 
*/

/*! \fn void dtkDistributedArray::unlock(void)
  \internal 
*/

/*! \fn bool dtkDistributedArray::empty(void) const
\internal 
*/

/*! \fn qlonglong dtkDistributedArray::size(void) const
\internal 
*/

/*! \fn void dtkDistributedArray::clearCache(void) const
  \internal 
*/

/*! \fn void dtkDistributedArray::fill(const T& value)
\internal 
*/

/*! \fn void dtkDistributedArray::setAt(const qlonglong& index, const T& value)
\internal 
*/

/*! \fn void dtkDistributedArray::setAt(const qlonglong& index, T *array, const qlonglong& size)
\internal 
*/

/*! \fn T dtkDistributedArray::at(const qlonglong& index) const
\internal 
*/

/*! \fn T dtkDistributedArray::first(void) const
\internal 
*/

/*! \fn T dtkDistributedArray::last(void) const
\internal
*/

/*! \fn T dtkDistributedArray::operator[](const qlonglong& index) const
\internal 
*/

/*! \fn void dtkDistributedArray::addAssign(const qlonglong& index, const T& value)
  \internal 
*/

/*! \fn void dtkDistributedArray::subAssign(const qlonglong& index, const T& value)
  \internal 
*/

/*! \fn void dtkDistributedArray::mulAssign(const qlonglong& index, const T& value)
  \internal 
*/

/*! \fn void dtkDistributedArray::divAssign(const qlonglong& index, const T& value)
  \internal 
*/

/*! \fn void dtkDistributedArray::addAssign(const qlonglong& index, T* array, const qlonglong& count)
  \internal 
*/

/*! \fn void dtkDistributedArray::subAssign(const qlonglong& index, T* array, const qlonglong& count)
  \internal 
*/

/*! \fn void dtkDistributedArray::mulAssign(const qlonglong& index, T* array, const qlonglong& count)
  \internal 
*/

/*! \fn void dtkDistributedArray::divAssign(const qlonglong& index, T* array, const qlonglong& count)
  \internal 
*/

/*! \fn void dtkDistributedArray::copyIntoArray(const qlonglong& from, T *array, qlonglong& size) const
  \internal 
*/

/*! \fn iterator dtkDistributedArray::begin(iterator = iterator())

*/

/*! \fn iterator dtkDistributedArray::end(iterator = iterator())

*/

/*! \fn const_iterator dtkDistributedArray::begin(const_iterator = const_iterator()) const

*/

/*! \fn const_iterator dtkDistributedArray::end(const_iterator = const_iterator()) const

*/

/*! \fn const_iterator dtkDistributedArray::cbegin(const_iterator = const_iterator()) const

*/

/*! \fn const_iterator dtkDistributedArray::cend(const_iterator = const_iterator()) const

*/

/*! \fn const T *dtkDistributedArray::data(void) const

*/

/*! \fn T *dtkDistributedArray::data(void)

*/

/*! \fn const T *dtkDistributedArray::constData(void) const

*/

/*! \fn navigator dtkDistributedArray::toNavigator(void) const
\internal 
*/

/*! \fn void dtkDistributedArray::stats(void) const
  \internal 
*/


// 
// dtkDistributedArray.cpp ends here
