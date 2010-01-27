/* dtkAbstractDataImage.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  2 09:08:09 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 27 15:36:59 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 61
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataImage.h>

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataImagePrivate
// /////////////////////////////////////////////////////////////////

class dtkAbstractDataImagePrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataImage
// /////////////////////////////////////////////////////////////////

dtkAbstractDataImage::dtkAbstractDataImage(void) : dtkAbstractData(), d(new dtkAbstractDataImagePrivate)
{

}

dtkAbstractDataImage::dtkAbstractDataImage(const dtkAbstractDataImage& other): dtkAbstractData(other), d(new dtkAbstractDataImagePrivate)
{

}

dtkAbstractDataImage::~dtkAbstractDataImage(void)
{
    delete d;

    d = NULL;
}

void *dtkAbstractDataImage::image(void)
{
    return this->data();
}

int dtkAbstractDataImage::xDimension(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 0;
}

int dtkAbstractDataImage::yDimension(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 0;
}

int dtkAbstractDataImage::zDimension(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 0;
}

int dtkAbstractDataImage::minRangeValue(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 0;
}

int dtkAbstractDataImage::maxRangeValue(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 0;
}

int dtkAbstractDataImage::scalarValueCount(int value)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(value);

    return 0;
}

int dtkAbstractDataImage::scalarValueMinCount(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 0;
}

int dtkAbstractDataImage::scalarValueMaxCount(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 0;
}
