/* dtkComposerNodeNumberLong.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: jeu. nov. 17 21:53:26 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 15:14:46 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
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

class dtkComposerNodeNumberLongPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeNumberLong : public dtkComposerNodeNumber
{
    Q_OBJECT

public:
     dtkComposerNodeNumberLong(dtkComposerNode *parent = 0);
    ~dtkComposerNodeNumberLong(void);

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
    dtkComposerNodeNumberLongPrivate *d;
};

#endif
