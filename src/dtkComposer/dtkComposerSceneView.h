/* dtkComposerSceneView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Feb  5 15:23:02 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:08:01 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtGui>

class dtkComposerScene;
class dtkComposerSceneViewPrivate;

class DTKCOMPOSER_EXPORT dtkComposerSceneView : public QTreeView
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

