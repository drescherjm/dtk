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

#include "dtkComposerExport.h"

#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeaf declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeafPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLeaf : public dtkComposerNode
{
public:
             dtkComposerNodeLeaf(void);
    virtual ~dtkComposerNodeLeaf(void);

public:
    virtual void setInputs(void);
    virtual void run(void);

public:
    void setAsHeader(bool header);
    void setAsFooter(bool footer);

public:
    bool isHeader(void);
    bool isFooter(void);

private:
    dtkComposerNodeLeafPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafObject declaration
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeLeafObject : public dtkComposerNodeLeaf
{
public:
             dtkComposerNodeLeafObject(void) {}
    virtual ~dtkComposerNodeLeafObject(void) {}

public:
    virtual bool createObject(const QString& implementation) = 0;

public:
    virtual QVariant variant(void) const { return QVariant(); }

public:
    virtual QStringList implementations(void) const = 0;

    virtual QString currentImplementation(void) const = 0;

    virtual bool implementationHasChanged(const QString& implementation) const = 0;
};

//
// dtkComposerNodeLeaf.h ends here
