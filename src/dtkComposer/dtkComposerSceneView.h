/* dtkComposerSceneView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Feb  5 15:23:02 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  5 15:49:31 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
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

private:
    dtkComposerSceneViewPrivate *d;
};

#endif
