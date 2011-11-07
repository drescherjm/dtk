/* dtkComposerNodeGraphic.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Nov  2 17:10:36 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov  7 12:26:21 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 32
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEGRAPHIC_H
#define DTKCOMPOSERNODEGRAPHIC_H

#include "dtkComposerExport.h"

#include <QtCore>

class dtkComposerEdge;
class dtkComposerNode;
class dtkComposerNodeProperty;

class dtkComposerNodeGraphicPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeGraphic : public QObject
{
    Q_OBJECT

public:
     dtkComposerNodeGraphic(dtkComposerNode *node);
    ~dtkComposerNodeGraphic(void);

public:
    dtkComposerNode *node(void);

public:
    void  appendLeftProperty(dtkComposerNodeProperty *property);
    void appendRightProperty(dtkComposerNodeProperty *property);

    void  removeLeftProperty(dtkComposerNodeProperty *property);
    void removeRightProperty(dtkComposerNodeProperty *property);
    void removeAllProperties(void);

    void  appendLeftEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void appendRightEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

    void  removeLeftEdge(dtkComposerEdge *edge);
    void removeRightEdge(dtkComposerEdge *edge);
    void  removeAllEdges(void);

    void  appendLeftRelayEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void appendRightRelayEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

    void  removeLeftRelayEdge(dtkComposerEdge *edge);
    void removeRightRelayEdge(dtkComposerEdge *edge);
    void  removeAllRelayEdges(void);

public:
    dtkComposerNodeProperty  *leftProperty(const QString& name) const;
    dtkComposerNodeProperty *rightProperty(const QString& name) const;

    const QList<dtkComposerNodeProperty *>&  leftProperties(void) const;
    const QList<dtkComposerNodeProperty *>& rightProperties(void) const;

    const QList<dtkComposerEdge *>&  leftEdges(void) const;
    const QList<dtkComposerEdge *>& rightEdges(void) const;

    const QList<dtkComposerEdge *>&  leftRelayEdges(void) const;
    const QList<dtkComposerEdge *>& rightRelayEdges(void) const;

public:
    dtkComposerEdge *edge(dtkComposerNodeProperty *property) const;

    int edgeCount(dtkComposerNodeProperty *property) const;
    int indexOf(dtkComposerNodeProperty *property) const;

public:
    void    onEdgeConnected(dtkComposerEdge *edge);
    void onEdgeDisconnected(dtkComposerEdge *edge);
    

private:
    dtkComposerNodeGraphicPrivate *d;
    
};

#endif
