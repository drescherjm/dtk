/* dtkComposerNodeBoolean.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 25 10:04:24 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 16 15:19:49 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEBOOLEAN_H
#define DTKCOMPOSERNODEBOOLEAN_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

class dtkComposerNodeBooleanPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeBoolean : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeBoolean(dtkComposerNode *parent = 0);
    ~dtkComposerNodeBoolean(void);

protected:
    void pull(dtkComposerEdge *route, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *route, dtkComposerNodeProperty *property);

public:
    dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);

public:
    bool setReceiver(dtkComposerEdge *route, dtkComposerNodeProperty *destination);

    bool onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property);

public:
    bool interactive(void);

    void setLabelText(bool value);

private:
    dtkComposerNodeBooleanPrivate *d;
};

#endif
