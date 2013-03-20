/* dtkComposerNodeMetaVector3DArrayExtractor.h --- 
 * 
 * Author: Jeremie Labroquere
 * Copyright (C) 2011 - Jeremie Labroquere, Inria.
 * Created: Mon Aug  6 15:39:13 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2013 Mon Jan 14 12:31:00 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEMETAVECTOR3DARRAYEXTRACTOR_H
#define DTKCOMPOSERNODEMETAVECTOR3DARRAYEXTRACTOR_H



#include <dtkComposer/dtkComposerNodeLeaf.h>

class dtkComposerNodeMetaVector3DArrayExtractorPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaVector3DArrayExtractor interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeMetaVector3DArrayExtractor : public dtkComposerNodeLeaf
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

