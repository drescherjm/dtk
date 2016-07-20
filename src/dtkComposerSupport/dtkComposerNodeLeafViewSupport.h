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

#include <dtkCoreSupport/dtkAbstractView.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafViewSupport declaration
// /////////////////////////////////////////////////////////////////

template <> class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeObject<dtkAbstractView> : public dtkComposerNodeLeafObject
{
public:
    dtkComposerNodeObject(void);
    virtual ~dtkComposerNodeObject(void);

public:
    bool createObject(const QString& implementation);

public:
    QStringList implementations(void) const;

    QString currentImplementation(void) const;

    bool implementationHasChanged(void) const;
    bool implementationHasChanged(const QString& implementation) const;

public:
    virtual bool enableDefaultImplementation(void) const;

    virtual bool isAbstractView(void) const = 0;

    virtual QString abstractViewType(void) const = 0;

public:
    QImage screenshot(void) const;
    void setView(dtkAbstractView *view);

    virtual dtkAbstractView *view(void);

public:
    QVariant variant(void) const;
    dtkAbstractView *object(void) const;

protected:
    void clearView(void);

protected:
    bool m_implementation_has_changed;
    dtkAbstractView *m_view;
};

typedef dtkComposerNodeObject<dtkAbstractView> dtkComposerNodeLeafViewSupport;

//
// dtkComposerNodeLeafViewSupport.h ends here
