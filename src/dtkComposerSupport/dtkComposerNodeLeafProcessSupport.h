// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include "dtkComposerSupportExport.h"

#include <dtkComposer/dtkComposerNodeLeaf.h>
#include <dtkComposer/dtkComposerNodeObject.h>

#include <dtkCoreSupport/dtkAbstractProcess.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafProcessSupport declaration
// /////////////////////////////////////////////////////////////////

template <> class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeObject<dtkAbstractProcess> : public dtkComposerNodeLeafObject
{
public:
    dtkComposerNodeObject(void);
    virtual ~dtkComposerNodeObject(void);

public:
    bool createObject(const QString& implementation);

public:
    QStringList implementations(void) const;

    QString currentImplementation(void) const;

    bool implementationHasChanged(const QString& implementation) const;

public:
    virtual bool enableDefaultImplementation(void) const;

    virtual bool isAbstractProcess(void) const = 0;

    virtual bool isInteractive(void);

    virtual QString abstractProcessType(void) const = 0;

public:
    virtual void setProcess(dtkAbstractProcess *process) = 0;

    virtual dtkAbstractProcess *process(void) const = 0;

public:
    QVariant variant(void) const;
    dtkAbstractProcess *object(void) const;

protected:
    void clearProcess(void);

protected:
    QString m_implementation;
    dtkAbstractProcess *m_process;
};

typedef dtkComposerNodeObject<dtkAbstractProcess> dtkComposerNodeLeafProcessSupport;

//
// dtkComposerNodeLeafProcessSupport.h ends here
