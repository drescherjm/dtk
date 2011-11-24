/* dtkComposerNodeNumberLongInteger.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: jeu. nov. 17 21:53:26 2011 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. nov. 17 21:54:24 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODENUMBERLONGINTEGER_H
#define DTKCOMPOSERNODENUMBERLONGINTEGER_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeNumber.h"

class dtkComposerNodeNumberLongIntegerPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberLongInteger : public dtkComposerNodeNumber
{
    Q_OBJECT

public:
     dtkComposerNodeNumberLongInteger(dtkComposerNode *parent = 0);
    ~dtkComposerNodeNumberLongInteger(void);

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
    dtkComposerNodeNumberLongIntegerPrivate *d;
};

#endif
