/* dtkComposerScene.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:11:39
 * Version: $Id$
 * Last-Updated: Wed Feb 22 15:15:15 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 183
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

class dtkComposerMachine;
class dtkComposerFactory;
class dtkComposerGraph;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNote;
class dtkComposerScenePort;
class dtkComposerScenePrivate;
class dtkComposerStack;

class DTKCOMPOSER_EXPORT dtkComposerScene : public QGraphicsScene
{
    Q_OBJECT

public:
             dtkComposerScene(QObject *parent = 0);
    virtual ~dtkComposerScene(void);

// #pragma mark -
// #pragma mark - Setup

public:
    void setFactory(dtkComposerFactory *factory);
    void setMachine(dtkComposerMachine *machine);
    void setStack(dtkComposerStack *stack);
    void setGraph(dtkComposerGraph *graph);

// #pragma mark -
// #pragma mark - Composition depth management

public:
    dtkComposerSceneNodeComposite *root(void);
    dtkComposerSceneNodeComposite *current(void);

public:
    void setRoot(dtkComposerSceneNodeComposite *root);
    void setCurrent(dtkComposerSceneNode *node);
    void setCurrent(dtkComposerSceneNodeComposite *current);

// #pragma mark -
// #pragma mark - Scene management

public:
    void    addItem(QGraphicsItem *item);
    void removeItem(QGraphicsItem *item);

// #pragma mark -
// #pragma mark - Sigs

public slots:
    void modify(bool modified);

signals:
    void modified(bool);

signals:
    void selectedNode(dtkComposerSceneNode *node);
    void selectionCleared(void);
    // void selected(QGraphicsItem *item);

// #pragma mark -
// #pragma mark - Drag Drop Events

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

// #pragma mark -
// #pragma mark - Keyboard Events

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

// #pragma mark -
// #pragma mark - Mouse Events

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

// #pragma mark -
// #pragma mark - Geometric queries

protected:
    dtkComposerSceneNode *nodeAt(const QPointF& point, dtkComposerSceneNode *exclude) const;
    dtkComposerSceneNode *nodeAt(const QPointF& point) const;
    dtkComposerScenePort *portAt(const QPointF& point) const;
    dtkComposerSceneNodeComposite *parentAt(const QPointF& point) const;

// #pragma mark -
// #pragma mark - Internal sigs handling

protected slots:
    void onSelectionChanged(void);

private:
    dtkComposerScenePrivate *d;
};

#endif
