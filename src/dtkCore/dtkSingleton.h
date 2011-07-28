/* dtkSingleton.h ---
 *
 * Author: Michael Knopke
 * Code taken from: http://developer.qt.nokia.com/wiki/Qt_thread-safe_singleton
 * License: http://creativecommons.org/licenses/by-sa/2.5/
 * Created: July 28 10:28:00 2011 (+0100)
 */

/* Commentary:

Example usage:

{ mySingleton.h }

    // forward templated class
    class template<T>
    class dtkSingleton;

    class MySingleton
    {
        public:
        // return instance using the singleton
        static MySingleton* instance();

        // constructor needs to be public, as the scopedpointer inside the singleton does the deletion
        ~MySingleton() {};

        protected:
        // hide the constructor
        MySingleton() {};

        // class method example
        void doSomething() {...};

        private:

        // declare the singleton as a friend so it can construct us
        friend class dtkSingleton<MySingleton>;
    };

{ mySingleton.cpp }

#include <dtkCore/dtkSingleton>

MySingleton* MySingleton::instance()
{
    return &dtkSingleton<MySingleton>::instance();
}


 */

/* Change log:
 *
 */

#ifndef DTKSINGLETON_H
#define DTKSINGLETON_H
 
#include <QtCore/QtGlobal>
#include <QtCore/QScopedPointer>
#include <QtCore/QAtomicInt>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <QtCore/QThreadStorage>
#include <QtCore/QThread>

namespace dtkSingletonHelper {
    enum ECallOnce {
        CO_Request,
        CO_InProgress,
        CO_Finished
    };
 
    Q_GLOBAL_STATIC(QThreadStorage<QAtomicInt*>, once_flag)
}
 
template <class Function>
        inline static void qCallOnce(Function func, QBasicAtomicInt& flag)
{
    using namespace dtkSingletonHelper;
    int protectFlag = flag.fetchAndStoreAcquire(flag);
    if (protectFlag == CO_Finished)
        return;
    if (protectFlag == CO_Request && flag.testAndSetRelaxed(protectFlag,
                                                            CO_InProgress)) {
        func();
        flag.fetchAndStoreRelease(CO_Finished);
    }
    else {
        do {
            QThread::yieldCurrentThread();
        }
        while (!flag.testAndSetAcquire(CO_Finished, CO_Finished));
    }
}
 
template <class Function>
        inline static void qCallOncePerThread(Function func)
{
    using namespace dtkSingletonHelper;
    if (!once_flag()->hasLocalData()) {
        once_flag()->setLocalData(new QAtomicInt(CO_Request));
        qCallOnce(func, *once_flag()->localData());
    }
}

template <class T>
class dtkSingleton
{
public:
    static T& instance()
    {
        qCallOnce(init, flag);
        return *tptr;
    }
 
    static void init()
    {
        tptr.reset(new T);
    }
 
private:
    dtkSingleton() {};
    ~dtkSingleton() {};
    Q_DISABLE_COPY(dtkSingleton)
 
    static QScopedPointer<T> tptr;
    static QBasicAtomicInt flag;

};
 
template<class T> QScopedPointer<T> dtkSingleton<T>::tptr(0);
template<class T> QBasicAtomicInt dtkSingleton<T>::flag
                            = Q_BASIC_ATOMIC_INITIALIZER(dtkSingletonHelper::CO_Request);
                            

                             

#endif //DTKSINGLETON
