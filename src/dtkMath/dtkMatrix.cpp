/* dtkMatrix.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 16:04:38 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Jul 18 16:17:53 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 353
 */

/* Change Log:
 * 
 */

#include "dtkMatrix.h"

dtkMatrix::dtkMatrix(void)
{
    this->dirty = false;
}

dtkMatrix::dtkMatrix(const dtkMatrix& other)
{
    this->dirty = false;
    this->cpy(other);
}

dtkMatrix::~dtkMatrix(void)
{

}

qulonglong dtkMatrix::colCount(void) const
{
    return 0;
}

qulonglong dtkMatrix::rowCount(void) const
{
    return 0;
}

QVariant dtkMatrix::at(qulonglong i, qulonglong j) const
{
    Q_UNUSED(i);
    Q_UNUSED(j);

    return QVariant();
}

void dtkMatrix::setAt(qulonglong i, qulonglong j, QVariant value)
{
    Q_UNUSED(i);
    Q_UNUSED(j);
    Q_UNUSED(value);    
}

void dtkMatrix::cpy(const dtkMatrix& other)
{
    Q_UNUSED(other);
}

dtkMatrix& dtkMatrix::cln(void)
{
    return *this;
}

dtkMatrix& dtkMatrix::sum(const dtkMatrix& other)
{
    return (*this);
}

dtkMatrix& dtkMatrix::sub(const dtkMatrix& other)
{
    return (*this);
}

dtkMatrix& dtkMatrix::mul(const dtkMatrix& other)
{
    return (*this);
}

void dtkMatrix::allocate(qulonglong r, qulonglong c)
{
    Q_UNUSED(r);
    Q_UNUSED(c);
}

void *dtkMatrix::buffer(void)
{
    return NULL;
}

dtkMatrix& dtkMatrix::operator=(const dtkMatrix& other)
{
    this->cpy(other);

    if(other.dirty)
	delete const_cast<dtkMatrix *>(&other);

    return (*this);
}

dtkMatrix& dtkMatrix::operator+=(const dtkMatrix& other)
{
    return sum(other);
}

dtkMatrix& dtkMatrix::operator-=(const dtkMatrix& other)
{
    return sub(other);
}

dtkMatrix& dtkMatrix::operator*=(const dtkMatrix& other)
{
    return mul(other);
}

dtkMatrix& operator+(const dtkMatrix& lhs, const dtkMatrix& rhs)
{
    dtkMatrix &r = const_cast<dtkMatrix &>(lhs).cln();
    r.dirty = true;
    r.sum(rhs);

    return r;
}

dtkMatrix& operator-(const dtkMatrix& lhs, const dtkMatrix& rhs)
{
    dtkMatrix &r = const_cast<dtkMatrix &>(lhs).cln();
    r.dirty = true;
    r.sub(rhs);

    return r;
}

dtkMatrix& operator*(const dtkMatrix& lhs, const dtkMatrix& rhs)
{
    dtkMatrix &r = const_cast<dtkMatrix &>(lhs).cln();
    r.dirty = true;
    r.mul(rhs);

    return r;
}

QDebug operator<<(QDebug debug, const dtkMatrix *matrix)
{
    debug << *matrix;

    return debug;
}

QDebug operator<<(QDebug debug, const dtkMatrix& matrix)
{
    debug.nospace() << "\n";
    for(qulonglong i = 0; i < matrix.rowCount(); i++) {
	debug.nospace() << "(";
	for(qulonglong j = 0; j < matrix.colCount(); j++) {
	    debug.nospace() << " " << matrix.at(i, j);
	}
	debug.nospace() << ")" << "\n";
    }

    return debug.space();
}
