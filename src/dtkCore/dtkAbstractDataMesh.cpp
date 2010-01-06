/* dtkAbstractDataMesh.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  2 09:08:09 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan  5 15:23:13 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 41
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDataMesh.h>

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
    return -1;
}

int dtkAbstractDataMesh::countVertices(void)
{
    return -1;
}

int dtkAbstractDataMesh::countNormals(void)
{
    return -1;
}

int dtkAbstractDataMesh::countColors(void)
{
    return -1;
}

int *dtkAbstractDataMesh::indices(void)
{
    return NULL;
}

double *dtkAbstractDataMesh::vertices(void)
{
    return NULL;
}

double *dtkAbstractDataMesh::normals(void)
{
    return NULL;
}

double *dtkAbstractDataMesh::colors(void)
{
    return NULL;
}
