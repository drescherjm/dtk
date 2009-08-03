/* dtkAbstractDataMeshSurfacic.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 11 12:38:11 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:24:43 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
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

private:
   dtkAbstractDataMeshSurfacicPrivate *d;
};

#endif
