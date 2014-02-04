/* dtkComposerNodeLeafProcess.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 14:08:02 2012 (+0200)
 * Version: $Id$
 * Last-Updated: 2012 Fri Nov 16 16:17:30 (+0100)
 *           By: Thibaud Kloczko, Inria.
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELEAFPROCESS_H
#define DTKCOMPOSERNODELEAFPROCESS_H


#include "dtkComposerNodeLeaf.h"

#include <QStringList>

class dtkAbstractProcess;
class dtkComposerNodeLeafProcessPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafProcess interface
// /////////////////////////////////////////////////////////////////

class  dtkComposerNodeLeafProcess : public dtkComposerNodeLeaf
{
public:
             dtkComposerNodeLeafProcess(void);
    virtual ~dtkComposerNodeLeafProcess(void);

public:
    virtual bool enableDefaultImplementation(void) const;
    
    virtual bool isAbstractProcess(void) const = 0;

    virtual QString abstractProcessType(void) const = 0;

public:
    bool implementationHasChanged(void) const;

    QString currentImplementation(void) const;

    QStringList implementations(void);

public:
    dtkAbstractProcess *createProcess(const QString& implementation);

    dtkAbstractProcess *process(void);

private:
    dtkComposerNodeLeafProcessPrivate *d;
};

#endif
