/* dtkComposerNodeMetaVector3DArrayExtractor.h --- 
 * 
 * Author: Jeremie Labroquere
 * Copyright (C) 2011 - Jeremie Labroquere, Inria.
 * Created: Mon Aug  6 15:39:13 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  9 11:52:42 2012 (+0200)
 *           By: sprinter
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEMETAVECTOR3DARRAYEXTRACTOR_H
#define DTKCOMPOSERNODEMETAVECTOR3DARRAYEXTRACTOR_H

#include "dtkComposerExport.h"
#include "dtkComposerMetatype.h"

#include <dtkComposer/dtkComposerNodeLeaf.h>

class dtkComposerNodeMetaVector3DArrayExtractorPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaVector3DArrayExtractor interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeMetaVector3DArrayExtractor : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMetaVector3DArrayExtractor(void);
    ~dtkComposerNodeMetaVector3DArrayExtractor(void);
    
public:
    void run(void);

public:
    inline QString type(void) {
        return "meta_vector3D_array_extractor";
    }

    inline QString titleHint(void) {
        return "Meta Vector3D Array Extractor";
    }

public:
    inline QString inputLabelHint(int port) {

        if(port == 0)
            return "arrays";

        if(port == 1)
            return "index";

        return "input";
    }

    inline QString outputLabelHint(int port) {

        if(port == 0)
            return "array";

        return "output";
    }

private:
    dtkComposerNodeMetaVector3DArrayExtractorPrivate *d;
};

#endif

