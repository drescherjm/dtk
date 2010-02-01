/* dtkAbstractDataEdge.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Dec 11 11:04:22 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  1 22:16:09 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAEDGE_H
#define DTKABSTRACTDATAEDGE_H

#include "dtkAbstractData.h"

class dtkAbstractDataVertex;

class dtkAbstractDataEdge : public dtkAbstractData
{
    Q_OBJECT

public:
             dtkAbstractDataEdge(dtkAbstractData *parent = 0);
    virtual ~dtkAbstractDataEdge(void);

    virtual dtkAbstractDataVertex *source(void) = 0;
    virtual dtkAbstractDataVertex *destination(void) = 0;
};

#endif
