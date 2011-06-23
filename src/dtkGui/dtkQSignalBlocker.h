/* dtkQSignalBlocker.h --- 
 * 
 * Author: John Stark
 * Copyright (C) 2011- John Stark, Inria.
 * Created: 20-06-2011
 * Version: $Id$
 *     Update #: 1
 */

/* Commentary: 
 *
 */

/* Change log:
 * 
 */
//=============================================================================
#ifndef DTKQSIGNALBLOCKER_H
#define DTKQSIGNALBLOCKER_H

#include <QObject>

class dtkQSignalBlocker
{
public:
    explicit dtkQSignalBlocker( QObject * o ) : m_object(o) {
        m_object->blockSignals(true);
    }

    ~dtkQSignalBlocker() {
        m_object->blockSignals(false);
    }

    void blockSignals(bool v) { m_object->blockSignals(v); }

private:
    QObject * m_object;
private:
    dtkQSignalBlocker( const dtkQSignalBlocker & ); // Not implemented.
    dtkQSignalBlocker & operator=( const dtkQSignalBlocker & ); // Not implemented.
};
#endif // DTKQSIGNALBLOCKER_H
