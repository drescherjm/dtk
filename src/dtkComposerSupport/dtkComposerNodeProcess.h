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
#include "dtkComposerNodeLeafProcess.h"

class dtkComposerNodeProcessPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeProcess interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeProcess : public dtkComposerNodeLeafProcess
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

// 
// dtkComposerNodeProcess.h ends here
