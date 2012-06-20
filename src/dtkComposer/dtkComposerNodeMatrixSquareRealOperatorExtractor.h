/* dtkComposerNodeMatrixSquareRealOperatorExtractor.h ---
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

#ifndef dtkComposerNodeMatrixSquareRealOperatorExtractor_H
#define dtkComposerNodeMatrixSquareRealOperatorExtractor_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeMatrixSquareRealOperatorExtractorPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareRealOperatorExtractor : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMatrixSquareRealOperatorExtractor(void);
    ~dtkComposerNodeMatrixSquareRealOperatorExtractor(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "matrixSquare_real_extractor";
    }

    inline QString titleHint(void) {
        return "MatrixSquare Real Extractor";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeMatrixSquareRealOperatorExtractorPrivate *d;
};

#endif

