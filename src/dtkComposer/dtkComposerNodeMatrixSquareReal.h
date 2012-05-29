/* dtkComposerNodeMatrixSquareReal.h ---
 *
 * Author: sblekout
 * Copyright (C) 2011 - babette lekouta, Inria.
 * Created: Thu Apr 26 10:10:43 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr 27 17:54:19 2012 (+0200)
 *           By: babette lekouta
 *     Update #: 9
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef dtkComposerNodeMatrixSquareReal_H
#define dtkComposerNodeMatrixSquareReal_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeMatrixSquareRealPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMatrixSquareReal : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMatrixSquareReal(void);
    ~dtkComposerNodeMatrixSquareReal(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "matrix_square_real";
    }

    inline QString titleHint(void) {
        return "Matrix Square Real";
    }

public:
    QString  inputLabelHint(int port);
    QString outputLabelHint(int port);

private:
    dtkComposerNodeMatrixSquareRealPrivate *d;
};

#endif
