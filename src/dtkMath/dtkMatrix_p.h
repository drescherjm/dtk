/* dtkMatrix_p.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 17:36:33 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Jul 16 14:52:03 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

template <typename T> class dtkMatrixPrivate
{
public:
             dtkMatrixPrivate(void);
             dtkMatrixPrivate(qulonglong r, qulonglong c);
    virtual ~dtkMatrixPrivate(void);

public:
    T at(qulonglong i, qulonglong j);

public:
    void allocate(qulonglong c, qulonglong r);

public:
    T *buffer;

public:
    qulonglong r_count;
    qulonglong c_count;
};

#include "dtkMatrix.tpp"
