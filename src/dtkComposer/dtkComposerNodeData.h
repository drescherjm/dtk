/* @(#)dtkComposerNodeData.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/29 11:15:49
 * Version: $Id$
 * Last-Updated: Thu May 31 00:16:27 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEDATA_H
#define DTKCOMPOSERNODEDATA_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeDataPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeData : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeData(void);
    ~dtkComposerNodeData(void);

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeDataPrivate *d;
};

#endif
