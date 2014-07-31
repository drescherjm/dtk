/* dtkSpinLock.h ---
 *
 * Author: Nicolas Niclausse
 * Created: 29 jul 2014
 */


#pragma once

#include <QAtomicInt>

//
// https://gist.github.com/aperezdc/5582452

class dtkSpinLock: private QAtomicInt
{
public:
    class Acquire {
    public:
    Acquire(dtkSpinLock& spinLock): m_spinLock(spinLock)
        { m_spinLock.lock(); }

        ~Acquire()
        { m_spinLock.unlock(); }

    private:
        dtkSpinLock& m_spinLock;

// Disable copy constructor and assignment operator
        Acquire& operator=(const Acquire&);
        Acquire(const Acquire&);
    };

dtkSpinLock(): QAtomicInt(Unlocked) {}

    void lock() {
        while (!testAndSetOrdered(Unlocked, Locked));
    }

    void unlock() {
        while (!testAndSetOrdered(Locked, Unlocked));
    }

    bool tryLock() {
        return testAndSetOrdered(Unlocked, Locked);
    }

private:
    static const int Unlocked = 1;
    static const int Locked = 0;
};
