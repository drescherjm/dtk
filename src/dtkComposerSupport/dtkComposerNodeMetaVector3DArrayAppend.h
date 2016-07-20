/* dtkComposerNodeMetaVector3DArrayAppend.h ---
 *
 * Author: Jeremie Labroquere
 * Copyright (C) 2011 - Jeremie Labroquere, Inria.
 * Created: Mon Aug  6 15:25:59 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  9 11:54:53 2012 (+0200)
 *           By: sprinter
 *     Update #: 3
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEMETAVECTOR3DARRAYAPPEND_H
#define DTKCOMPOSERNODEMETAVECTOR3DARRAYAPPEND_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerMetatype.h"

#include <dtkComposerNodeLeaf.h>

class dtkComposerNodeMetaVector3DArrayAppendPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaVector3DArrayAppend interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeMetaVector3DArrayAppend : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeMetaVector3DArrayAppend(void);
    ~dtkComposerNodeMetaVector3DArrayAppend(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "meta_vector3D_array_append";
    }

    inline QString titleHint(void) {
        return "Meta Vector3D Array Append";
    }

public:
    inline QString inputLabelHint(int port) {

        if (port == 0)
            return "arrays";

        if (port == 1)
            return "array";

        return "input";
    }

    inline QString outputLabelHint(int port) {

        if (port == 0)
            return "arrays";

        return "output";
    }

private:
    dtkComposerNodeMetaVector3DArrayAppendPrivate *d;
};

#endif

