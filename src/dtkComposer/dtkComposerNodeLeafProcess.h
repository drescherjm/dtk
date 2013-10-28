/* dtkComposerNodeLeafProcess.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 14:08:02 2012 (+0200)
 * Version: $Id$
 * Last-Updated: ven. oct. 25 15:51:00 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 8
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
    virtual bool enableDefaultImplementation(void) const;
    
    virtual bool isAbstractProcess(void) const = 0;

    virtual QString abstractProcessType(void) const = 0;

public:
    bool implementationHasChanged(const QString& implementation) const;

    QString currentImplementation(void) const;

    QStringList implementations(void);

public:
    dtkAbstractProcess *createProcess(const QString& implementation);

    dtkAbstractProcess *process(void);

private:
    dtkComposerNodeLeafProcessPrivate *d;
};

#endif
