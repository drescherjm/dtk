/* dtkAbstractDataMeshVolumic.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 11 12:38:11 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:28:15 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 9
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

private:
   dtkAbstractDataMeshVolumicPrivate *d;
};

#endif
