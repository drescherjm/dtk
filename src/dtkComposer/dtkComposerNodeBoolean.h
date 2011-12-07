/* dtkComposerNodeBoolean.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 25 10:04:24 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 14:29:30 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 26
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

    bool value(void);

protected:
    void pull(dtkComposerRoute *route, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerRoute *route, dtkComposerNodeProperty *property);

public:
    dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);

public:
    bool onLeftRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *destination);
    bool onRightRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property);

public:
    bool interactive(void);

    void setLabelText(bool value);

private:
    dtkComposerNodeBooleanPrivate *d;
};

#endif
