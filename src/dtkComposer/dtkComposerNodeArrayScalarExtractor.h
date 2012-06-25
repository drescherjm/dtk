/* dtkComposerNodeArrayScalarExtractor.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:33:29 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jun 25 12:34:57 2012 (+0200)
 *           By: tkloczko
 *     Update #: 6
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEARRAYSCALAREXTRACTOR_H
#define DTKCOMPOSERNODEARRAYSCALAREXTRACTOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeArrayScalarExtractorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeArrayScalarExtractor : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeArrayScalarExtractor(void);
    ~dtkComposerNodeArrayScalarExtractor(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_extractor";
    }

    inline QString titleHint(void) {
        return "Scalar array extract";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeArrayScalarExtractorPrivate *d;
};

#endif

