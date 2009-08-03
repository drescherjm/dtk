/* dtkAbstractDataImageDicom.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Jun  2 11:10:29 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:21:12 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataImageDicom.h>

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataImageDicomPrivate
// /////////////////////////////////////////////////////////////////

class dtkAbstractDataImageDicomPrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataImageDicom
// /////////////////////////////////////////////////////////////////

dtkAbstractDataImageDicom::dtkAbstractDataImageDicom(void) : dtkAbstractDataImage(), d(new dtkAbstractDataImageDicomPrivate)
{

}

dtkAbstractDataImageDicom::dtkAbstractDataImageDicom(const  dtkAbstractDataImageDicom& other): dtkAbstractDataImage(other), d(new dtkAbstractDataImageDicomPrivate)
{

}

dtkAbstractDataImageDicom::~dtkAbstractDataImageDicom(void)
{
    delete d;

    d = NULL;
}
