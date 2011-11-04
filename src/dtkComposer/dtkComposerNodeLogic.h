/* dtkComposerNodeLogic.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Nov  4 13:49:39 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Nov  4 14:29:05 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 10
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
    QList<dtkComposerEdge *>  leftRoutes(void);
    QList<dtkComposerEdge *> rightRoutes(void);    

private:
    dtkComposerNodeLogicPrivate *d;
};

#endif
