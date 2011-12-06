/* dtkComposerNodeLogic.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Nov  4 13:49:39 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec  6 14:30:06 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 31
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

class dtkComposerEdge;
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
    void  appendLeftRoute(dtkComposerEdge *route);
    void appendRightRoute(dtkComposerEdge *route);

    void  removeLeftRoute(dtkComposerEdge *route);
    void removeRightRoute(dtkComposerEdge *route);
    void  removeAllRoutes(void);

    void  appendLeftRelayRoute(dtkComposerEdge *route);
    void appendRightRelayRoute(dtkComposerEdge *route);

    void  removeLeftRelayRoute(dtkComposerEdge *route);
    void removeRightRelayRoute(dtkComposerEdge *route);
    void  removeAllRelayRoutes(void);

    void  appendLeftNode(dtkComposerNode *node);
    void appendRightNode(dtkComposerNode *node);

    void  removeLeftNode(dtkComposerNode *node);
    void removeRightNode(dtkComposerNode *node);
    void  removeAllNodes(void);

public:
    const QList<dtkComposerEdge *>&  leftRoutes(void) const;
    const QList<dtkComposerEdge *>& rightRoutes(void) const;

    const QList<dtkComposerEdge *>&  leftRelayRoutes(void) const;
    const QList<dtkComposerEdge *>& rightRelayRoutes(void) const;

    const QList<dtkComposerNode *>&  leftNodes(void) const;
    const QList<dtkComposerNode *>& rightNodes(void) const;

public:
    bool canConnectRoute(dtkComposerNodeProperty *source, dtkComposerNodeProperty *destination, dtkComposerNode *destin_node);

public:
    void onRouteDisconnected(dtkComposerNodeProperty *source, dtkComposerNodeProperty *destination, dtkComposerNode *destin_node);

public:
    bool isRoute(dtkComposerNodeProperty *source, dtkComposerNodeProperty *destination);

private:
    dtkComposerNodeLogicPrivate *d;
};

#endif
