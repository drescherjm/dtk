/* dtkAbstractDataMeshVolumic.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 11 12:38:11 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 27 18:45:21 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAMESHVOLUMIC_H
#define DTKABSTRACTDATAMESHVOLUMIC_H

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkAbstractDataMesh.h>

class dtkAbstractDataMeshVolumicPrivate;

class DTKCORE_EXPORT dtkAbstractDataMeshVolumic : public dtkAbstractDataMesh
{
    Q_OBJECT

public:
    dtkAbstractDataMeshVolumic(void);
   ~dtkAbstractDataMeshVolumic(void);

public:
   virtual int countFaces(void);
   virtual int countTets(void);

private:
   dtkAbstractDataMeshVolumicPrivate *d;
};

#endif
