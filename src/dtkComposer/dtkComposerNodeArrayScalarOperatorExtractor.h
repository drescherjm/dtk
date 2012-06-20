/* dtkComposerNodeArrayScalarOperatorExtractor.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:33:29 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 15 11:37:39 2012 (+0200)
 *           By: sblekout
 *     Update #: 2
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef dtkComposerNodeArrayScalarOperatorExtractor_H
#define dtkComposerNodeArrayScalarOperatorExtractor_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeArrayScalarOperatorExtractorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeArrayScalarOperatorExtractor : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeArrayScalarOperatorExtractor(void);
    ~dtkComposerNodeArrayScalarOperatorExtractor(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_extractor";
    }

    inline QString titleHint(void) {
        return "Scalar Array Extractor";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeArrayScalarOperatorExtractorPrivate *d;
};

#endif

