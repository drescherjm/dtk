/* dtkComposerNodeLeafProcess.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 14:08:02 2012 (+0200)
 * Version: $Id$
 * Last-Updated: ven. nov.  8 16:17:25 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELEAFPROCESS_H
#define DTKCOMPOSERNODELEAFPROCESS_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

#include <QStringList>

class dtkAbstractProcess;
class dtkComposerNodeLeafProcessPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafProcess interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeLeafProcess : public dtkComposerNodeLeaf
{
public:
             dtkComposerNodeLeafProcess(void);
    virtual ~dtkComposerNodeLeafProcess(void);

public:
    virtual bool enableDefaultImplementation(void) const;
    
    virtual bool isAbstractProcess(void) const = 0;

    virtual QString abstractProcessType(void) const = 0;

public:
    virtual void setProcess(dtkAbstractProcess *process) = 0;

    virtual dtkAbstractProcess *process(void) const = 0;

public:
    bool implementationHasChanged(const QString& implementation) const;

    QString currentImplementation(void) const;

    QStringList implementations(void);

public:
    dtkAbstractProcess *createProcess(const QString& implementation);

protected:
    void clearProcess(void);

private:
    dtkComposerNodeLeafProcessPrivate *d;
};

#endif
