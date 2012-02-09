/* dtkComposerGraphView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:42:13 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  9 15:48:56 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERGRAPHVIEW_H
#define DTKCOMPOSERGRAPHVIEW_H

#include <QtGui>

class dtkComposerGraphViewPrivate;

class dtkComposerGraphView : public QGraphicsView
{
    Q_OBJECT

public:
     dtkComposerGraphView(QWidget *parent = 0);
    ~dtkComposerGraphView(void);

private:
    dtkComposerGraphViewPrivate *d;
};

#endif
