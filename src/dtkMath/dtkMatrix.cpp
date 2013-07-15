/* dtkMatrix.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Jul 15 16:04:38 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Jul 15 16:06:47 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Change Log:
 * 
 */

#include "dtkMatrix.h"

class dtkMatrixPrivate
{
public:
};

dtkMatrix::dtkMatrix(QObject *parent) : QObject(), d(new dtkMatrixPrivate)
{
    
}

dtkMatrix::~dtkMatrix(void)
{
    delete d;
}
