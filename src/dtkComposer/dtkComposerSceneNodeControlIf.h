/* dtkComposerSceneNodeControlIf.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 16:19:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  8 16:23:33 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODECONTROLIF_H
#define DTKCOMPOSERSCENENODECONTROLIF_H

#include "dtkComposerSceneNodeControl.h"

class dtkComposerSceneNodeControlIfPrivate;

class dtkComposerSceneNodeControlIf : public dtkComposerSceneNodeControl
{
public:
     dtkComposerSceneNodeControlIf(void);
    ~dtkComposerSceneNodeControlIf(void);

public:
    virtual QString type(void) = 0;

private:
    dtkComposerSceneNodeControlIfPrivate *d;
};

#endif
