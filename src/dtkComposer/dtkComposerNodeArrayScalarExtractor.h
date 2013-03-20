/* dtkComposerNodeArrayScalarExtractor.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 11:33:29 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 26 10:09:32 2012 (+0200)
 *           By: tkloczko
 *     Update #: 13
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEARRAYSCALAREXTRACTOR_H
#define DTKCOMPOSERNODEARRAYSCALAREXTRACTOR_H


#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeArrayScalarExtractorPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractor interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeArrayScalarExtractor : public dtkComposerNodeLeaf
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

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorSubArray interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarExtractorSubArrayPrivate;

class  dtkComposerNodeArrayScalarExtractorSubArray : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeArrayScalarExtractorSubArray(void);
    ~dtkComposerNodeArrayScalarExtractorSubArray(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_extractor_subarray";
    }

    inline QString titleHint(void) {
        return "Scalar array : extract subarray";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeArrayScalarExtractorSubArrayPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeArrayScalarExtractorArrayPart interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeArrayScalarExtractorArrayPartPrivate;

class  dtkComposerNodeArrayScalarExtractorArrayPart : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeArrayScalarExtractorArrayPart(void);
    ~dtkComposerNodeArrayScalarExtractorArrayPart(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "array_scalar_extractor_array_part";
    }

    inline QString titleHint(void) {
        return "Scalar array : extract array part";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeArrayScalarExtractorArrayPartPrivate *d;
};

#endif

