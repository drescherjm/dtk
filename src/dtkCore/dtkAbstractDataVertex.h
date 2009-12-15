/* dtkAbstractDataVertex.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Dec 11 10:53:36 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Dec 11 11:09:44 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAVERTEX_H
#define DTKABSTRACTDATAVERTEX_H

#include "dtkAbstractData.h"

class dtkAbstractDataVertex : public dtkAbstractData
{
    Q_OBJECT

public:
             dtkAbstractDataVertex(dtkAbstractData *parent = 0);
    virtual ~dtkAbstractDataVertex(void);

    virtual int index(void) = 0;
    virtual float x(void) = 0;
    virtual float y(void) = 0;
    virtual float z(void) = 0;

    virtual void setIndex(int index) = 0;
    virtual void setX(float x) = 0;
    virtual void setY(float y) = 0;
    virtual void setZ(float z) = 0;
};

#endif // DTKABSTRACTDATAVERTEX_H
