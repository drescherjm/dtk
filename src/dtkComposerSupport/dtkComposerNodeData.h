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
#include "dtkComposerNodeLeafDataSupport.h"

class dtkComposerNodeDataPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeData interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeData : public dtkComposerNodeLeafDataSupport
{
public:
     dtkComposerNodeData(void);
    ~dtkComposerNodeData(void);

public:
    bool isAbstractData(void) const;

    QString abstractDataType(void) const;

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

// 
// dtkComposerNodeData.h ends here
