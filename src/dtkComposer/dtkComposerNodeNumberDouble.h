/* dtkComposerNodeNumberDouble.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: jeu. nov. 17 22:11:52 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 15:14:28 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
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

public:
    const QVariant::Type genre(void) const;

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
