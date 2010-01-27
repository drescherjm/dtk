/* dtkAbstractDataMeshSurfacic.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 11 12:40:15 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 27 18:46:31 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataMeshSurfacic.h>

class dtkAbstractDataMeshSurfacicPrivate
{
public:
};

dtkAbstractDataMeshSurfacic::dtkAbstractDataMeshSurfacic(void) : dtkAbstractDataMesh(), d(new dtkAbstractDataMeshSurfacicPrivate)
{

}

dtkAbstractDataMeshSurfacic::~dtkAbstractDataMeshSurfacic(void)
{
    delete d;

    d = NULL;
}

int dtkAbstractDataMeshSurfacic::countFaces(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return -1;
}
