/* dtkComposerNodeNumberInteger.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: jeu. nov. 17 20:36:06 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec  6 14:42:05 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 12
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
    bool  onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property);
    bool onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property);

public:
    bool  onLeftRouteDisconnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination);
    bool onRightRouteDisconnected(dtkComposerEdge *route, dtkComposerNodeProperty *source);

private:
    dtkComposerNodeNumberIntegerPrivate *d;
};

#endif
