/* dtkComposerNodeMetaScalarArrayExtractor.h ---
 *
 * Author: Régis Duvigneau
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

#include "dtkComposerNodeLeaf.h"

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

