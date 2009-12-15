/* dtkAbstractDataFace.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Dec 11 11:04:22 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Dec 11 11:13:43 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAFACE_H
#define DTKABSTRACTDATAFACE_H

#include "dtkAbstractData.h"

class dtkAbstractDataFace : public dtkAbstractData
{
    Q_OBJECT

public:
             dtkAbstractDataFace(dtkAbstractData *parent = 0);
    virtual ~dtkAbstractDataFace(void);
};

#endif
