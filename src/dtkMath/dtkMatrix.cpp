/* dtkMatrix.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 16:04:38 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Jul 16 12:44:48 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 95
 */

/* Change Log:
 * 
 */

#include "dtkMatrix.h"

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
