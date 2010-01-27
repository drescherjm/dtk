/* dtkAbstractDataMesh.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  2 09:08:09 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 27 18:43:09 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTMESHDATA_H
#define DTKABSTRACTMESHDATA_H

#include <dtkCore/dtkAbstractData.h>

class dtkAbstractDataMeshPrivate;

class DTKCORE_EXPORT dtkAbstractDataMesh : public dtkAbstractData
{
    Q_OBJECT

public:
             dtkAbstractDataMesh(void);
             dtkAbstractDataMesh(const  dtkAbstractDataMesh& other);
    virtual ~dtkAbstractDataMesh(void);

    void *mesh(void);

public:
    virtual int countIndices(void);
    virtual int countVertices(void);
    virtual int countEdges(void);

    virtual int *indices(void);

    virtual double *vertices(void);
    virtual double *vertex(int index);

private:
    dtkAbstractDataMeshPrivate *d;
};

#endif
