/* dtkMatrix.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 16:04:38 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Jul 15 17:41:41 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 70
 */

/* Change Log:
 * 
 */

#include "dtkMatrix.h"
#include "dtkMatrix_p.h"

dtkMatrix::dtkMatrix(QObject *parent) : QObject(), d(new dtkMatrixPrivate)
{

}

void dtkMatrix::setType(Type type)
{
    switch(type) {
    case Integer:
	d->buffer = new int[10];
	for(int i = 0; i < 10; i++)
	    static_cast<int *>(d->buffer)[i] = i;
	break;
    case Double:
	d->buffer = new double[10];
	for(int i = 0; i < 10; i++)
	    static_cast<double *>(d->buffer)[i] = i;
	break;
    }
}

dtkMatrix::~dtkMatrix(void)
{
    delete d;
}
