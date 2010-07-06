/* dtkComposerView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:06:52 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul  6 16:48:22 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERVIEW_H
#define DTKCOMPOSERVIEW_H

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtGui>

class DTKCOMPOSER_EXPORT dtkComposerView : public QGraphicsView
{
    Q_OBJECT

public:
     dtkComposerView(QWidget *parent = 0);
    ~dtkComposerView(void);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
};

#endif
