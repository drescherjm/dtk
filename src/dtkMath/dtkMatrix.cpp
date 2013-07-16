/* dtkMatrix.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 16:04:38 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Jul 16 18:08:04 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 158
 */

/* Change Log:
 * 
 */

#include "dtkMatrix.h"

dtkMatrix& dtkMatrix::operator=(dtkMatrix& other)
{
    return cln(other);
}

dtkMatrix& dtkMatrix::operator+=(dtkMatrix& other)
{
    return sum(other);
}

dtkMatrix& dtkMatrix::operator-=(dtkMatrix& other)
{
    return sub(other);
}

dtkMatrix& dtkMatrix::operator*=(dtkMatrix& other)
{
    return mul(other);
}

dtkMatrix& dtkMatrix::operator+(dtkMatrix& other)
{
    return add(other);
}

dtkMatrix& dtkMatrix::operator-(dtkMatrix& other)
{
    return rem(other);
}

dtkMatrix& dtkMatrix::operator*(dtkMatrix& other)
{
    return scl(other);
}

// dtkMatrix& operator+(dtkMatrix& lhs, dtkMatrix& rhs)
// {
//     return lhs.add(rhs);
// }

// dtkMatrix& operator-(dtkMatrix& lhs, dtkMatrix& rhs)
// {
//     return lhs.rem(rhs);
// }

// dtkMatrix& operator*(dtkMatrix& lhs, dtkMatrix& rhs)
// {
//     return lhs.scl(rhs);
// }

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
