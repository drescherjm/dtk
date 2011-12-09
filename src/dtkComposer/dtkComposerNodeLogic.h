/* dtkComposerNodeLogic.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Nov  4 13:49:39 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Dec  9 23:49:57 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 36
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODELOGIC_H
#define DTKCOMPOSERNODELOGIC_H

#include "dtkComposerExport.h"

#include <QtCore>

class dtkComposerRoute;
class dtkComposerNode;
class dtkComposerNodeProperty;

class dtkComposerNodeLogicPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeLogic : public QObject
{
    Q_OBJECT

public:
     dtkComposerNodeLogic(dtkComposerNode *node);
    ~dtkComposerNodeLogic(void);

public:
    dtkComposerNode *node(void);

public:
    void  appendLeftRoute(dtkComposerRoute *route);
    void appendRightRoute(dtkComposerRoute *route);

    void  removeLeftRoute(dtkComposerRoute *route);
    void removeRightRoute(dtkComposerRoute *route);
    void  removeAllRoutes(void);

    void  appendLeftRelayRoute(dtkComposerRoute *route);
    void appendRightRelayRoute(dtkComposerRoute *route);

    void  removeLeftRelayRoute(dtkComposerRoute *route);
    void removeRightRelayRoute(dtkComposerRoute *route);
    void  removeAllRelayRoutes(void);

    void  appendLeftNode(dtkComposerNode *node);
    void appendRightNode(dtkComposerNode *node);

    void  removeLeftNode(dtkComposerNode *node);
    void removeRightNode(dtkComposerNode *node);
    void  removeAllNodes(void);

public:
    const QList<dtkComposerRoute *>&  leftRoutes(void) const;
    const QList<dtkComposerRoute *>& rightRoutes(void) const;

    const QList<dtkComposerRoute *>&  leftRelayRoutes(void) const;
    const QList<dtkComposerRoute *>& rightRelayRoutes(void) const;

    const QList<dtkComposerNode *>&  leftNodes(void) const;
    const QList<dtkComposerNode *>& rightNodes(void) const;

public:
    bool isRoute(dtkComposerNodeProperty *source, dtkComposerNodeProperty *destination);

public:
    bool    connectRoute(dtkComposerNodeProperty *source, dtkComposerNodeProperty *destination, dtkComposerNode *destin_node);
    bool disconnectRoute(dtkComposerNodeProperty *source, dtkComposerNodeProperty *destination, dtkComposerNode *destin_node);

private:
    dtkComposerNodeLogicPrivate *d;
};

#endif
