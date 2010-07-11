/* dtkComposerScene.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:05:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Jul 11 23:26:10 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 43
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
class dtkComposerNodeProperty;
class dtkComposerScenePrivate;

class DTKCOMPOSER_EXPORT dtkComposerScene : public QGraphicsScene
{
    Q_OBJECT

public:
     dtkComposerScene(QObject *parent = 0);
    ~dtkComposerScene(void);

    void addNode(dtkComposerNode *node);

    QList<dtkComposerEdge *> edges(void);
    QList<dtkComposerNode *> nodes(void);
    QList<dtkComposerNode *> nodes(QString name);
    QList<dtkComposerNodeProperty *> properties(void);
    QList<dtkComposerNodeProperty *> properties(QString name);

signals:
    void dataSelected(dtkAbstractData *data);
    void processSelected(dtkAbstractProcess *process);
    void viewSelected(dtkAbstractView *view);

public slots:
    void start(void);
    void pause(void);
    void stop(void);

protected:
    dtkComposerNode *nodeAt(const QPointF& point) const;
    dtkComposerNodeProperty *propertyAt(const QPointF& point) const;

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

protected slots:
    void onSelectionChanged(void);

private:
    dtkComposerScenePrivate *d;
};

#endif
