/* dtkMatrix.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 15:58:33 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Jul 22 12:17:04 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 341
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
             dtkMatrix(void);
    virtual ~dtkMatrix(void);

public:
    virtual qulonglong colCount(void) const = 0;
    virtual qulonglong rowCount(void) const = 0;

public:
    virtual QVariant at(qulonglong i, qulonglong j) const = 0;
    virtual void setAt(qulonglong i, qulonglong j, QVariant value) = 0;

public:
    virtual void       cpy(const dtkMatrix& other) = 0;
    virtual dtkMatrix& cln(void) = 0;
    virtual dtkMatrix& sum(const dtkMatrix& other) = 0;
    virtual dtkMatrix& sub(const dtkMatrix& other) = 0;
    virtual dtkMatrix& mul(const dtkMatrix& other) = 0;

public:
    virtual void allocate(qulonglong r, qulonglong c) = 0;

public:
    virtual void *buffer(void) = 0;

public:
    dtkMatrix& operator =(const dtkMatrix& other);
    dtkMatrix& operator+=(const dtkMatrix& other);
    dtkMatrix& operator-=(const dtkMatrix& other);
    dtkMatrix& operator*=(const dtkMatrix& other);

protected:
    dtkMatrix& lazyClone(void);

public:
    friend dtkMatrix& operator+(const dtkMatrix& lhs, const dtkMatrix& rhs);
    friend dtkMatrix& operator-(const dtkMatrix& lhs, const dtkMatrix& rhs);
    friend dtkMatrix& operator*(const dtkMatrix& lhs, const dtkMatrix& rhs);

public:
    bool dirty;
};

dtkMatrix& operator+(const dtkMatrix& lhs, const dtkMatrix& rhs);
dtkMatrix& operator-(const dtkMatrix& lhs, const dtkMatrix& rhs);
dtkMatrix& operator*(const dtkMatrix& lhs, const dtkMatrix& rhs);

QDebug operator<<(QDebug debug, const dtkMatrix *matrix);
QDebug operator<<(QDebug debug, const dtkMatrix& matrix);

DTK_DECLARE_OBJECT(dtkMatrix*)
DTK_DECLARE_PLUGIN(dtkMatrix)
DTK_DECLARE_PLUGIN_FACTORY(dtkMatrix)
DTK_DECLARE_PLUGIN_MANAGER(dtkMatrix)
