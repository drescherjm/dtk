/* dtkComposerNodeNumberInteger.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: jeu. nov. 17 20:36:06 2011 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. nov. 17 21:47:30 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODENUMBERINTEGER_H
#define DTKCOMPOSERNODENUMBERINTEGER_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeNumber.h"

class dtkComposerNodeNumberIntegerPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberInteger : public dtkComposerNodeNumber
{
    Q_OBJECT

public:
     dtkComposerNodeNumberInteger(dtkComposerNode *parent = 0);
    ~dtkComposerNodeNumberInteger(void);

public slots:
    void touch(void);

protected:
    void pull(dtkComposerEdge *route, dtkComposerNodeProperty *property);
    void  run(void);
    void push(dtkComposerEdge *route, dtkComposerNodeProperty *property);

public:
    dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);

public:
    bool onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination);

    bool onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property);

private:
    dtkComposerNodeNumberIntegerPrivate *d;
};

#endif
