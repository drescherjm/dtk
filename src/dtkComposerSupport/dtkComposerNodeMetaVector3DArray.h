/* dtkComposerNodeMetaVector3DArray.h --- 
 * 
 * Author: Jeremie Labroquere
 * Copyright (C) 2011 - Jeremie Labroquere, Inria.
 * Created: Mon Aug  6 14:25:15 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  9 11:55:31 2012 (+0200)
 *           By: sprinter
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEMETAVECTOR3DARRAY_H
#define DTKCOMPOSERNODEMETAVECTOR3DARRAY_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerMetatype.h"

#include <dtkComposerNodeLeaf.h>

class dtkComposerNodeMetaVector3DArrayPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaVector3DArray interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeMetaVector3DArray : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMetaVector3DArray(void);
    ~dtkComposerNodeMetaVector3DArray(void);
    
public:
    void run(void);

public:
    inline QString type(void) {
        return "meta_vector3D_array";
    }

    inline QString titleHint(void) {
        return "Meta Vector3D Array";
    }

public:
    QString outputLabelHint(int port);

private:
    dtkComposerNodeMetaVector3DArrayPrivate *d;
};

#endif

