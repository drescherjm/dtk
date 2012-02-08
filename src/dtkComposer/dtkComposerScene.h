/* dtkComposerScene.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:11:39
 * Version: $Id$
 * Last-Updated: Wed Feb  8 10:39:18 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 112
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

public:
    void setFactory(dtkComposerFactory *factory);
    void setMachine(dtkComposerMachine *machine);
    void setStack(dtkComposerStack *stack);

public:
    void    addNode(dtkComposerSceneNode *node);
    void removeNode(dtkComposerSceneNode *node);

    void    addEdge(dtkComposerSceneEdge *edge);
    void removeEdge(dtkComposerSceneEdge *edge);

    void    addNote(dtkComposerSceneNote *note);
    void removeNote(dtkComposerSceneNote *note);

public:
    dtkComposerSceneNodeComposite *root(void);
    dtkComposerSceneNodeComposite *current(void);

public:
    void clear(void);

public:
    void setCurrent(dtkComposerSceneNode *node);
    void setCurrent(dtkComposerSceneNodeComposite *current);
    void setRoot(dtkComposerSceneNodeComposite *root);

signals:
    void reset(void);

signals:
    void modified(bool);

signals:
    void selectedNode(dtkComposerSceneNode *node);
    void selectionCleared(void);

    // void selected(QGraphicsItem *item);

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

protected:
    dtkComposerSceneNode *nodeAt(const QPointF& point) const;
    dtkComposerScenePort *portAt(const QPointF& point) const;

protected slots:
    void onSelectionChanged(void);

private:
    dtkComposerScenePrivate *d;
};

#endif
