/* dtkComposerNodeVectorRealOperatorExtractor.h ---
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

#ifndef dtkComposerNodeVectorRealOperatorExtractor_H
#define dtkComposerNodeVectorRealOperatorExtractor_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeVectorRealOperatorExtractorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealOperatorExtractor : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVectorRealOperatorExtractor(void);
    ~dtkComposerNodeVectorRealOperatorExtractor(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_extractor";
    }

    inline QString titleHint(void) {
        return "Vector Real Extractor";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeVectorRealOperatorExtractorPrivate *d;
};

#endif

