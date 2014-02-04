/* dtkComposerNodeLeafView.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 14:38:07 2012 (+0200)
 * Version: $Id$
 * Last-Updated: lun. oct. 14 12:27:20 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELEAFVIEW_H
#define DTKCOMPOSERNODELEAFVIEW_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

#include <QStringList>

class dtkAbstractView;
class dtkComposerNodeLeafViewPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafView interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeLeafView : public dtkComposerNodeLeaf
{
public:
             dtkComposerNodeLeafView(void);
    virtual ~dtkComposerNodeLeafView(void);

public:
    virtual bool enableDefaultImplementation(void) const;

    virtual bool isAbstractView(void) const = 0;

    virtual QString abstractViewType(void) const = 0;

public:
    bool implementationHasChanged(void) const;

    QString currentImplementation(void);

    QStringList implementations(void);

public:
    QImage screenshot(void) const;
    void setView(dtkAbstractView *view);

public:
    virtual dtkAbstractView *createView(const QString& implementation);
    virtual dtkAbstractView *view(void);

private:
    dtkComposerNodeLeafViewPrivate *d;
};

#endif
