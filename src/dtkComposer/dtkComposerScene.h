/* dtkComposerScene.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:05:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Mar  3 18:51:19 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 151
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
class dtkComposerNodeControlBlock;
class dtkComposerNodeFactory;
class dtkComposerNodeProperty;
class dtkComposerNote;
class dtkComposerScenePrivate;

class DTKCOMPOSER_EXPORT dtkComposerScene : public QGraphicsScene
{
    Q_OBJECT

public:
             dtkComposerScene(QObject *parent = 0);
    virtual ~dtkComposerScene(void);

    QList<dtkComposerNote *> notes(void);
    QList<dtkComposerEdge *> edges(void);
    QList<dtkComposerNode *> nodes(void);
    QList<dtkComposerNode *> nodes(QString name);
    QList<dtkComposerNodeProperty *> properties(void);
    QList<dtkComposerNodeProperty *> properties(QString name);

    QList<dtkComposerNode *> startNodes(void);
    QList<dtkComposerNode *>   endNodes(void);

    void touch(void);
    void clear(void);

    bool  isModified(void);
    void setModified(bool modified);

    void    addEdge(dtkComposerEdge *edge);
    void    addNode(dtkComposerNode *node);
    void    addNote(dtkComposerNote *note);
    void removeEdge(dtkComposerEdge *edge);
    void removeNode(dtkComposerNode *node);
    void removeNote(dtkComposerNote *note);

    void setFactory(dtkComposerNodeFactory *factory);

    dtkComposerNode *createGroup(QList<dtkComposerNode *> nodes, QPointF position = QPointF());
    dtkComposerNode *createNode(QString type, QPointF position = QPointF());
    dtkComposerNote *createNote(QString text, QPointF position = QPointF(), QSizeF size = QSizeF());

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

public slots:
   void copy(void);
   void paste(void);

protected:
    dtkComposerNode *nodeAt(const QPointF& point) const;
    dtkComposerNodeProperty *propertyAt(const QPointF& point) const;

protected:
    void setCurrentNode(dtkComposerNode *node);

    void hideAllNodes(void);
    void showAllNodes(void);
    void showChildNodes(dtkComposerNode *node);
    void updateEdgesVisibility(void);

    QList<dtkComposerNodeControlBlock *> hoveredControlBlocks(dtkComposerNode *node);
    QList<dtkComposerNodeControlBlock *> hoveredControlBlocks(dtkComposerNode *node, QList<QGraphicsItem *> parents);

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
    static bool s_evaluate;

private:
    friend class dtkComposerNode;

    dtkComposerScenePrivate *d;
};

#endif
