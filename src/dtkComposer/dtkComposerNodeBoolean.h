/* dtkComposerNodeBoolean.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 25 10:04:24 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 25 13:57:18 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEBOOLEAN_H
#define DTKCOMPOSERNODEBOOLEAN_H

#include "dtkComposerNode.h"

class dtkComposerNodeBooleanPrivate;

class dtkComposerNodeBoolean : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeBoolean(dtkComposerNode *parent = 0);
    ~dtkComposerNodeBoolean(void);

    QVariant value(dtkComposerNodeProperty *property);

public:
    bool value(void);

    void setValue(bool value);

protected:
    void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void run(void);

private:
    dtkComposerNodeBooleanPrivate *d;
};

#endif
