/* dtkAbstractDataImage.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  2 09:08:09 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 27 15:37:26 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 40
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
             dtkAbstractDataImage(const dtkAbstractDataImage& other);
    virtual ~dtkAbstractDataImage(void);

    void *image(void);

    virtual int            Dimension() const;
    virtual const QString& PixelType() const;

    virtual int xDimension(void);
    virtual int yDimension(void);
    virtual int zDimension(void);
    virtual int tDimension(void);

    virtual int minRangeValue(void);
    virtual int maxRangeValue(void);

    virtual int scalarValueCount(int value);
    virtual int scalarValueMinCount(void);
    virtual int scalarValueMaxCount(void);

private:
    dtkAbstractDataImagePrivate *d;
};

#endif
