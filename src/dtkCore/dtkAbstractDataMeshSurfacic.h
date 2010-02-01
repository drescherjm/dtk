/* dtkAbstractDataMeshSurfacic.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 11 12:38:11 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  1 22:19:58 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAMESHSURFACIC_H
#define DTKABSTRACTDATAMESHSURFACIC_H

#include <dtkCore/dtkAbstractDataMesh.h>

class dtkAbstractDataFace;
class dtkAbstractDataMeshSurfacicPrivate;

class DTKCORE_EXPORT dtkAbstractDataMeshSurfacic : public dtkAbstractDataMesh
{
    Q_OBJECT

public:
    dtkAbstractDataMeshSurfacic(void);
   ~dtkAbstractDataMeshSurfacic(void);

public:
   virtual int countFaces(void) = 0;

   virtual QList<dtkAbstractDataFace *> faces(void) = 0;

private:
   dtkAbstractDataMeshSurfacicPrivate *d;
};

#endif
