/* dtkComposerNodeLogic.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Nov  4 13:49:39 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 14 17:21:24 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 12
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

public:
    const QList<dtkComposerEdge *>&  leftRoutes(void) const;
    const QList<dtkComposerEdge *>& rightRoutes(void) const;

private:
    dtkComposerNodeLogicPrivate *d;
};

#endif
