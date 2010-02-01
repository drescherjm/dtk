/* dtkAbstractDataMeshVolumic.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 11 12:38:11 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  1 22:21:04 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAMESHVOLUMIC_H
#define DTKABSTRACTDATAMESHVOLUMIC_H

#include <dtkCore/dtkAbstractDataMesh.h>

class dtkAbstractDataFace;
class dtkAbstractDataCell;
class dtkAbstractDataMeshVolumicPrivate;

class DTKCORE_EXPORT dtkAbstractDataMeshVolumic : public dtkAbstractDataMesh
{
    Q_OBJECT

public:
    dtkAbstractDataMeshVolumic(void);
   ~dtkAbstractDataMeshVolumic(void);

public:
   virtual int countFaces(void) = 0;
   virtual int countCells(void) = 0;

   virtual QList<dtkAbstractDataFace *> faces(void) = 0;
   virtual QList<dtkAbstractDataCell *> cells(void) = 0;

private:
   dtkAbstractDataMeshVolumicPrivate *d;
};

#endif
