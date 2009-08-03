/* dtkAbstractDataImage.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  2 09:08:09 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:14:15 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 33
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTIMAGEDATA_H
#define DTKABSTRACTIMAGEDATA_H

#include <dtkCore/dtkAbstractData.h>

class dtkAbstractDataImagePrivate;

class DTKCORE_EXPORT dtkAbstractDataImage : public dtkAbstractData
{
    Q_OBJECT

public:
             dtkAbstractDataImage(void);
             dtkAbstractDataImage(const  dtkAbstractDataImage& other);
    virtual ~dtkAbstractDataImage(void);

    void *image(void);

    virtual int xDimension(void) { return 0; }
    virtual int yDimension(void) { return 0; }
    virtual int zDimension(void) { return 0; }

    virtual int minRangeValue(void) { return 0; }
    virtual int maxRangeValue(void) { return 0; }

    virtual int scalarValueCount(int value) { return 0; }
    virtual int scalarValueMinCount(void) { return 0; }
    virtual int scalarValueMaxCount(void) { return 0; }

private:
    dtkAbstractDataImagePrivate *d;
};

#endif
