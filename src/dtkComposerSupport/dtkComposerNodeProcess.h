/* @(#)dtkComposerNodeProcess.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/29 11:15:49
 * Version: $Id$
 * Last-Updated: lun. juin  1 15:12:07 2015 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 17
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEPROCESS_H
#define DTKCOMPOSERNODEPROCESS_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeafProcessSupport.h"

class dtkComposerNodeProcessPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProcess interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeProcess : public dtkComposerNodeLeafProcessSupport
{
public:
     dtkComposerNodeProcess(void);
    ~dtkComposerNodeProcess(void);

public:
    bool isAbstractProcess(void) const;

    QString abstractProcessType(void) const;

 public:
    void setProcess(dtkAbstractProcess *process);

    dtkAbstractProcess *process(void) const;

public:
    void run(void);

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeProcessPrivate *d;
};

#endif
