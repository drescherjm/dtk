/* dtkAbstractDataVertex.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Dec 11 11:01:04 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  1 22:44:49 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAbstractDataVertex.h"

dtkAbstractDataVertex::dtkAbstractDataVertex(dtkAbstractData *parent) : dtkAbstractData(parent)
{

}

dtkAbstractDataVertex::~dtkAbstractDataVertex(void)
{

}

dtkAbstractDataVertex::operator double *(void)
{
    double *coordinates = new double[3];
    coordinates[0] = this->x();
    coordinates[1] = this->y();
    coordinates[2] = this->z();
    
    return coordinates;
}
