/* dtkSingleton.h ---
 *
 * Author: Michael Knopke
 * Code taken from: http://developer.qt.nokia.com/wiki/Qt_thread-safe_singleton
 * License: http://creativecommons.org/licenses/by-sa/2.5/
 * Created: July 28 10:28:00 2011 (+0100)
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

#define DTK_IMPLEMENT_SINGLETON( T )            \
    T * T::instance()                           \
    {                                           \
        return &(dtkSingleton<T>::instance());  \
    }

#endif //DTKSINGLETON
