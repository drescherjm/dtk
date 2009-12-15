/* dtkAbstractDataTet.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Dec 11 11:04:22 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Dec 11 11:13:29 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATATET_H
#define DTKABSTRACTDATATET_H

#include "dtkAbstractData.h"

class dtkAbstractDataTet : public dtkAbstractData
{
    Q_OBJECT

public:
             dtkAbstractDataTet(dtkAbstractData *parent = 0);
    virtual ~dtkAbstractDataTet(void);
};

#endif
