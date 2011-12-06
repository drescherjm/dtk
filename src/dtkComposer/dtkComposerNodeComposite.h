/* dtkComposerNodeComposite.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Dec  6 13:59:21 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec  6 16:15:52 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECOMPOSITE_H
#define DTKCOMPOSERNODECOMPOSITE_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeCompositePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeComposite : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeComposite(dtkComposerNode *parent = 0);
    ~dtkComposerNodeComposite(void);

/* public: */
/*     void setGhost(bool ghost); */

/* public: */
/*     void layout(void); */

private:
    dtkComposerNodeCompositePrivate *d;
};

#endif
