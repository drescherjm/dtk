/* dtkComposerNodeMetaVector3DArray.h --- 
 * 
 * Author: Jeremie Labroquere
 * Copyright (C) 2011 - Jeremie Labroquere, Inria.
 * Created: Mon Aug  6 14:25:15 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Mon Jan 14 12:30:37 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEMETAVECTOR3DARRAY_H
#define DTKCOMPOSERNODEMETAVECTOR3DARRAY_H



#include <dtkComposer/dtkComposerNodeLeaf.h>

class dtkComposerNodeMetaVector3DArrayPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaVector3DArray interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeMetaVector3DArray : public dtkComposerNodeLeaf
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

