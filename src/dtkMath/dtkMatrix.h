/* dtkMatrix.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 15:58:33 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Jul 16 18:07:51 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 277
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkCore>

#include "dtkMatrix_p.h"

class dtkMatrix : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qulonglong colCount READ colCount)
    Q_PROPERTY(qulonglong rowCount READ rowCount)

public:
    virtual qulonglong colCount(void) const = 0;
    virtual qulonglong rowCount(void) const = 0;

public:
    virtual QVariant at(qulonglong i, qulonglong j) const = 0;
    virtual void setAt(qulonglong i, qulonglong j, QVariant value) = 0;

public:
    virtual dtkMatrix& cln(dtkMatrix& other) = 0;
    virtual dtkMatrix& sum(dtkMatrix& other) = 0;
    virtual dtkMatrix& sub(dtkMatrix& other) = 0;
    virtual dtkMatrix& mul(dtkMatrix& other) = 0;
    virtual dtkMatrix& add(dtkMatrix& other) = 0;
    virtual dtkMatrix& rem(dtkMatrix& other) = 0;
    virtual dtkMatrix& scl(dtkMatrix& other) = 0;

public:
    virtual void allocate(qulonglong r, qulonglong c) = 0;

public:
    virtual void *buffer(void) = 0;

public:
    dtkMatrix& operator =(dtkMatrix& other);
    dtkMatrix& operator +(dtkMatrix& other);
    dtkMatrix& operator -(dtkMatrix& other);
    dtkMatrix& operator *(dtkMatrix& other);
    dtkMatrix& operator+=(dtkMatrix& other);
    dtkMatrix& operator-=(dtkMatrix& other);
    dtkMatrix& operator*=(dtkMatrix& other);
};

// dtkMatrix& operator+(dtkMatrix& lhs, dtkMatrix& rhs);
// dtkMatrix& operator-(dtkMatrix& lhs, dtkMatrix& rhs);
// dtkMatrix& operator*(dtkMatrix& lhs, dtkMatrix& rhs);

QDebug operator<<(QDebug debug, const dtkMatrix *matrix);
QDebug operator<<(QDebug debug, const dtkMatrix& matrix);

DTK_DECLARE_OBJECT(dtkMatrix*)
DTK_DECLARE_PLUGIN(dtkMatrix)
DTK_DECLARE_PLUGIN_FACTORY(dtkMatrix)
DTK_DECLARE_PLUGIN_MANAGER(dtkMatrix)
