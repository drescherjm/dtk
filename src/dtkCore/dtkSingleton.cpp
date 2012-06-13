/**
 * \class dtkSingleton
 * \brief A thread safe singleton.
 * 
 * This class holds a single global instance of another class, allowing
 * singletons to be implemented. The instance is created on first use, and
 * returned using the instance() method.
 *
 * To avoid problems with race conditions, some thread safe locking is
 * introduced which prevents the instance() method creating more than one
 * object, or returning before the creation of the object is complete.
 *
 * Normally you should not need to access the class directly. Just use
 * the DTK_IMPLEMENT_SINGLETON macro.
 *
 * \sa    DTK_DECLARE_SINGLETON
 */

#include "dtkSingleton.h"

/** \file  dtkSingleton.h
    \brief Declare dtkSingleton and helpers.
    
    Details.
*/

/** \file  dtkSingleton.h
 *  \fn       template <class Function> void qCallOnce(Function func, QBasicAtomicInt& flag)
 *  \brief    Helper function that calls the function func once.
 */

/** \fn       void qCallOncePerThread(Function func)
 *  \brief    Helper function that calls the function func once for each thread.
 */

/** \fn       T& dtkSingleton::instance()
 *  \brief    return an instance of T.
 */

/** \fn       void dtkSingleton::init()
 *  \brief    Create an instance of T.
 */

/** \def      DTK_IMPLEMENT_SINGLETON( T )
 *  \brief    Macro to implement the instance() method of a class you wish to make singleton.
 *            Place this in your cpp file.
 *  \sa       DTK_DECLARE_SINGLETON( T )
 */
