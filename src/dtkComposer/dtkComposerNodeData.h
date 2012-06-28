/* @(#)dtkComposerNodeData.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/29 11:15:49
 * Version: $Id$
 * Last-Updated: Thu Jun 28 11:59:09 2012 (+0200)
 *           By: tkloczko
 *     Update #: 11
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
#include "dtkComposerNodeLeafData.h"

class dtkComposerNodeDataPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeData : public dtkComposerNodeLeafData
{
public:
     dtkComposerNodeData(void);
    ~dtkComposerNodeData(void);

public:
    bool isAbstractData(void) const { return true; }

    virtual QString abstractDataType(void) const { return "dtkAbstractData"; }

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
