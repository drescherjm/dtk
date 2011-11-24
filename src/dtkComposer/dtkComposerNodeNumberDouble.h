/* dtkComposerNodeNumberDouble.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: jeu. nov. 17 22:11:52 2011 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. nov. 17 22:12:49 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODENUMBERDOUBLE_H
#define DTKCOMPOSERNODENUMBERDOUBLE_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeNumber.h"

class dtkComposerNodeNumberDoublePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberDouble : public dtkComposerNodeNumber
{
    Q_OBJECT

public:
     dtkComposerNodeNumberDouble(dtkComposerNode *parent = 0);
    ~dtkComposerNodeNumberDouble(void);

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
    dtkComposerNodeNumberDoublePrivate *d;
};

#endif
