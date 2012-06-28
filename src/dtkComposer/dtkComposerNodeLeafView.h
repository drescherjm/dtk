/* dtkComposerNodeLeafView.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 14:38:07 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 28 14:38:30 2012 (+0200)
 *           By: tkloczko
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELEAFVIEW_H
#define DTKCOMPOSERNODELEAFVIEW_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

#include <QStringList>

class dtkAbstractView;
class dtkComposerNodeLeafViewPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafView interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeLeafView : public dtkComposerNodeLeaf
{
public:
             dtkComposerNodeLeafView(void);
    virtual ~dtkComposerNodeLeafView(void);

public:
    virtual bool isAbstractView(void) const = 0;

    virtual QString abstractViewType(void) const = 0;

public:
    QString currentImplementation(void);

    QStringList implementations(void);

public:
    dtkAbstractView *createView(const QString& implementation);

    dtkAbstractView *view(void);

private:
    dtkComposerNodeLeafViewPrivate *d;
};

#endif
