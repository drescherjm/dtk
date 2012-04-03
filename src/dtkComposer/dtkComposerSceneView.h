/* dtkComposerSceneView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Feb  5 15:23:02 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  6 14:11:04 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 31
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENEVIEW_H
#define DTKCOMPOSERSCENEVIEW_H

#include <QtGui>

class dtkComposerScene;
class dtkComposerSceneViewPrivate;

class dtkComposerSceneView : public QTreeView
{
    Q_OBJECT

public:
     dtkComposerSceneView(QWidget *parent = 0);
    ~dtkComposerSceneView(void);

public:
    void setScene(dtkComposerScene *scene);

public:
    void reset(void);

public slots:
    void clearSelection(void);

// public slots:
//     void select(QGraphicsItem *item);

protected slots:
    void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
    dtkComposerSceneViewPrivate *d;
};

#endif
