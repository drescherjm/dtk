/* dtkAbstractDataImage.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  2 09:08:09 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:15:16 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 38
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataImage.h>

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

dtkAbstractDataImage::dtkAbstractDataImage(const  dtkAbstractDataImage& other): dtkAbstractData(other), d(new dtkAbstractDataImagePrivate)
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
