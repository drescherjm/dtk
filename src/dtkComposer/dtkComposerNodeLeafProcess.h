/* dtkComposerNodeLeafProcess.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 14:08:02 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 28 14:13:55 2012 (+0200)
 *           By: tkloczko
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELEAFPROCESS_H
#define DTKCOMPOSERNODELEAFPROCESS_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

#include <QStringList>

class dtkAbstractProcess;
class dtkComposerNodeLeafProcessPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafProcess interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeLeafProcess : public dtkComposerNodeLeaf
{
public:
             dtkComposerNodeLeafProcess(void);
    virtual ~dtkComposerNodeLeafProcess(void);

public:
    virtual bool isAbstractProcess(void) const = 0;

    virtual QString abstractProcessType(void) const = 0;

public:
    QString currentImplementation(void);

    QStringList implementations(void);

public:
    dtkAbstractProcess *createProcess(const QString& implementation);

    dtkAbstractProcess *process(void);

private:
    dtkComposerNodeLeafProcessPrivate *d;
};

#endif
