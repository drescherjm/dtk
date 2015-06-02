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

#include <dtkCoreSupport/dtkAbstractData.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafDataSupport declaration
// /////////////////////////////////////////////////////////////////

template <> class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeObject<dtkAbstractData> : public dtkComposerNodeLeafObject
{
public:
             dtkComposerNodeObject(void);
    virtual ~dtkComposerNodeObject(void);

public:
    bool createObject(const QString& implementation);

public:
    dtkAbstractData *data(void) const;

public:
    QStringList implementations(void) const;

    QString currentImplementation(void) const;

    bool implementationHasChanged(void) const;
    bool implementationHasChanged(const QString& implementation) const;

public:
    virtual bool enableDefaultImplementation(void) const;

    virtual bool isAbstractData(void) const = 0;

    virtual QString abstractDataType(void) const = 0;

protected:
    bool m_implementation_has_changed;
    dtkAbstractData *m_data;
};

typedef dtkComposerNodeObject<dtkAbstractData> dtkComposerNodeLeafDataSupport;

// 
// dtkComposerNodeLeafDataSupport.h ends here
