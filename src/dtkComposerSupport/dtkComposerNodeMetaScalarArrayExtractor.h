/* dtkComposerNodeMetaScalarArrayExtractor.h --- 
 * 
 * Author: Régis Duvigneau
 * Copyright (C) 2008 - Regis Duvigneau, Inria.
 * Created: Thu Jul 19 11:27:03 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jul 19 11:27:54 2012 (+0200)
 *           By: Régis Duvigneau
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEMETASCALARARRAYEXTRACTOR_H
#define DTKCOMPOSERNODEMETASCALARARRAYEXTRACTOR_H

#include "dtkComposerSupportExport.h"

#include <dtkComposer/dtkComposerNodeLeaf.h>

class dtkComposerNodeMetaScalarArrayExtractorPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArrayExtractor interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeMetaScalarArrayExtractor : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMetaScalarArrayExtractor(void);
    ~dtkComposerNodeMetaScalarArrayExtractor(void);
    
public:
    void run(void);

public:
    inline QString type(void) {
        return "meta_scalar_array_extractor";
    }

    inline QString titleHint(void) {
        return "Meta Scalar Array Extractor";
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
    dtkComposerNodeMetaScalarArrayExtractorPrivate *d;
};

#endif

