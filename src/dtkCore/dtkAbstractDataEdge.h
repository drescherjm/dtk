/* dtkAbstractDataEdge.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Dec 11 11:04:22 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb  2 16:41:23 2010 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 11
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

    virtual void setSource(dtkAbstractDataVertex *source) = 0;
    virtual void setDestination(dtkAbstractDataVertex *destination) = 0;
};

#endif
