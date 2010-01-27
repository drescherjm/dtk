/* dtkAbstractDataMeshSurfacic.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 11 12:38:11 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 27 18:45:06 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAMESHSURFACIC_H
#define DTKABSTRACTDATAMESHSURFACIC_H

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkAbstractDataMesh.h>

class dtkAbstractDataMeshSurfacicPrivate;

class DTKCORE_EXPORT dtkAbstractDataMeshSurfacic : public dtkAbstractDataMesh
{
    Q_OBJECT

public:
    dtkAbstractDataMeshSurfacic(void);
   ~dtkAbstractDataMeshSurfacic(void);

public:
   virtual int countFaces(void);

private:
   dtkAbstractDataMeshSurfacicPrivate *d;
};

#endif
