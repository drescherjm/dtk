/* dtkMatrix.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 15:58:33 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Jul 18 16:04:57 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 325
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
             dtkMatrix(const dtkMatrix& other);
    virtual ~dtkMatrix(void);

public:
    virtual qulonglong colCount(void) const;
    virtual qulonglong rowCount(void) const;

public:
    virtual QVariant at(qulonglong i, qulonglong j) const;
    virtual void setAt(qulonglong i, qulonglong j, QVariant value);

public:
    virtual void       cpy(const dtkMatrix& other);
    virtual dtkMatrix& cln(void);
    virtual dtkMatrix& sum(const dtkMatrix& other);
    virtual dtkMatrix& sub(const dtkMatrix& other);
    virtual dtkMatrix& mul(const dtkMatrix& other);

public:
    virtual void allocate(qulonglong r, qulonglong c);

public:
    virtual void *buffer(void);

public:
    dtkMatrix& operator =(const dtkMatrix& other);
    dtkMatrix& operator+=(const dtkMatrix& other);
    dtkMatrix& operator-=(const dtkMatrix& other);
    dtkMatrix& operator*=(const dtkMatrix& other);

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
