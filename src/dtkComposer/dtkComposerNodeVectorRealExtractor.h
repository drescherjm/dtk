/* dtkComposerNodeVectorRealExtractor.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:33:29 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jun 25 11:55:25 2012 (+0200)
 *           By: tkloczko
 *     Update #: 5
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEVECTORREALEXTRACTOR_H
#define DTKCOMPOSERNODEVECTORREALEXTRACTOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeVectorRealExtractorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeVectorRealExtractor : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeVectorRealExtractor(void);
    ~dtkComposerNodeVectorRealExtractor(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_extractor";
    }

    inline QString titleHint(void) {
        return "Vector Real Extract";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeVectorRealExtractorPrivate *d;
};

#endif

