/* dtkComposerScene.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:05:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 10 18:35:16 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENE_H
#define DTKCOMPOSERSCENE_H

#include <QtGui>

class dtkAbstractData;
class dtkAbstractProcess;
class dtkAbstractView;
class dtkComposerNode;
class dtkComposerNodeProperty;
class dtkComposerScenePrivate;

class dtkComposerScene : public QGraphicsScene
{
    Q_OBJECT

public:
     dtkComposerScene(QObject *parent = 0);
    ~dtkComposerScene(void);

    void addNode(const QString& type);

signals:
    void dataSelected(dtkAbstractData *data);
    void processSelected(dtkAbstractProcess *process);
    void viewSelected(dtkAbstractView *view);

protected:
    dtkComposerNode *nodeAt(const QPointF& point) const;
    dtkComposerNodeProperty *propertyAt(const QPointF& point) const;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

protected slots:
    void onSelectionChanged(void);

private:
    dtkComposerScenePrivate *d;
};

#endif
