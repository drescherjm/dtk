/* dtkAbstractDataMesh.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  2 09:08:09 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 27 18:42:09 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 63
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataMesh.h>
#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataMeshPrivate
// /////////////////////////////////////////////////////////////////

class dtkAbstractDataMeshPrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataMesh
// /////////////////////////////////////////////////////////////////

dtkAbstractDataMesh::dtkAbstractDataMesh(void) : dtkAbstractData(), d(new dtkAbstractDataMeshPrivate)
{

}

dtkAbstractDataMesh::dtkAbstractDataMesh(const  dtkAbstractDataMesh& other): dtkAbstractData(other), d(new dtkAbstractDataMeshPrivate)
{

}

dtkAbstractDataMesh::~dtkAbstractDataMesh(void)
{
    delete d;

    d = NULL;
}

void *dtkAbstractDataMesh::mesh(void)
{
    return this->data();
}

int dtkAbstractDataMesh::countIndices(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return -1;
}

int dtkAbstractDataMesh::countVertices(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return -1;
}

int dtkAbstractDataMesh::countEdges(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return -1;
}

int *dtkAbstractDataMesh::indices(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

double *dtkAbstractDataMesh::vertices(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

double *dtkAbstractDataMesh::vertex(int index)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(index);

    return NULL;
}
