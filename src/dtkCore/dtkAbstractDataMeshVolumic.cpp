/* dtkAbstractDataMeshVolumic.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 11 12:40:15 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:28:43 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataMeshVolumic.h>

class dtkAbstractDataMeshVolumicPrivate
{
public:
};

dtkAbstractDataMeshVolumic::dtkAbstractDataMeshVolumic(void) : dtkAbstractDataMesh(), d(new dtkAbstractDataMeshVolumicPrivate)
{

}

dtkAbstractDataMeshVolumic::~dtkAbstractDataMeshVolumic(void)
{
    delete d;

    d = NULL;
}
