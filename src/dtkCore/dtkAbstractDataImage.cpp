/* dtkAbstractDataImage.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  2 09:08:09 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Nov 14 14:12:08 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 53
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
