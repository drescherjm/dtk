/* dtkComposerNodeVectorIntegerExtractor.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:33:29 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Wed Oct 10 18:08:59 (+0200)
 *           By: Thibaud Kloczko, Inria.
 *     Update #: 9
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEVECTORINTEGEREXTRACTOR_H
#define DTKCOMPOSERNODEVECTORINTEGEREXTRACTOR_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeVectorIntegerExtractorPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerExtractor : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorIntegerExtractor(void);
    ~dtkComposerNodeVectorIntegerExtractor(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "vector_real_extractor";
    }

    inline QString titleHint(void) {
        return "Vector Integer Extract";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeVectorIntegerExtractorPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeVectorIntegerExtractorSubVector interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeVectorIntegerExtractorSubVectorPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeVectorIntegerExtractorSubVector : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeVectorIntegerExtractorSubVector(void);
    ~dtkComposerNodeVectorIntegerExtractorSubVector(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "vectorIntegerExtractorSubVector";
    }

    inline QString titleHint(void) {
        return "Vector real : extract subvector";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeVectorIntegerExtractorSubVectorPrivate *d;
};

#endif

