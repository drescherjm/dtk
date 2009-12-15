/* dtkAbstractDataEdge.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Dec 11 11:04:22 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Dec 11 11:13:23 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
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

class dtkAbstractDataEdge : public dtkAbstractData
{
    Q_OBJECT

public:
             dtkAbstractDataEdge(dtkAbstractData *parent = 0);
    virtual ~dtkAbstractDataEdge(void);
};

#endif
