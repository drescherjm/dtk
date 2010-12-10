/* dtkComposerScene.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:05:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Dec 10 23:56:30 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 108
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENE_H
#define DTKCOMPOSERSCENE_H

#include "dtkComposerExport.h"

#include <QtGui>

class dtkAbstractData;
class dtkAbstractProcess;
class dtkAbstractView;
class dtkComposerEdge;
class dtkComposerNode;
class dtkComposerNodeFactory;
class dtkComposerNodeProperty;
class dtkComposerScenePrivate;

class DTKCOMPOSER_EXPORT dtkComposerScene : public QGraphicsScene
{
    Q_OBJECT

public:
             dtkComposerScene(QObject *parent = 0);
    virtual ~dtkComposerScene(void);

    QList<dtkComposerEdge *> edges(void);
    QList<dtkComposerNode *> nodes(void);
    QList<dtkComposerNode *> nodes(QString name);
    QList<dtkComposerNodeProperty *> properties(void);
    QList<dtkComposerNodeProperty *> properties(QString name);

    void clear(void);

    bool  isModified(void);
    void setModified(bool modified);

    void    addEdge(dtkComposerEdge *edge);
    void    addNode(dtkComposerNode *node);
    void removeNode(dtkComposerNode *node);

    void setFactory(dtkComposerNodeFactory *factory);

    dtkComposerNode *createGroup(QList<dtkComposerNode *> nodes, QPointF position = QPointF());
    dtkComposerNode *createNode(QString type, QPointF position = QPointF());

    void explodeGroup(dtkComposerNode *node);

signals:
    void dataSelected(dtkAbstractData *data);
    void processSelected(dtkAbstractProcess *process);
    void viewSelected(dtkAbstractView *view);

    void nodeAdded(dtkComposerNode *node);
    void nodeRemoved(dtkComposerNode *node);
    void nodeSelected(dtkComposerNode *node);

    void compositionChanged(void);

    void centerOn(const QPointF&);
    void fitInView(const QRectF&);
    void pathChanged(dtkComposerNode *);

    void selectionCleared(void);

signals:
    void evaluationStarted(void);
    void evaluationStopped(void);

public slots:
   void startEvaluation(void);
   void stopEvaluation(void);

protected:
    dtkComposerNode *nodeAt(const QPointF& point) const;
    dtkComposerNodeProperty *propertyAt(const QPointF& point) const;

protected:
    void setCurrentNode(dtkComposerNode *node);

    void hideAllNodes(void);
    void showAllNodes(void);
    void showChildNodes(dtkComposerNode *node);
    void updateEdgesVisibility(void);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

protected slots:
    void onSelectionChanged(void);

private:
    dtkComposerScenePrivate *d;
};

#endif
