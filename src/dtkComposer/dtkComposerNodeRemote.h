/* @(#)dtkComposerNodeRemote.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:15:12
 * Version: $Id$
 * Last-Updated: mar. avril 10 10:05:23 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 8
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEREMOTE_H
#define DTKCOMPOSERNODEREMOTE_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeComposite.h"

#include <QDomDocument>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemote declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemotePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeRemote : public dtkComposerNodeComposite
{
public:
             dtkComposerNodeRemote(void);
    virtual ~dtkComposerNodeRemote(void);

public:
    QString type(void);

public:
    QString titleHint(void);

public:
    void setComposition(QDomDocument document);

public:
    virtual void begin(void);
    virtual void end(void);

private:
    dtkComposerNodeRemotePrivate *d;
};


#endif /* DTKCOMPOSERNODEREMOTE_H */

