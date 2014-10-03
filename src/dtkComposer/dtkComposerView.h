/* dtkComposerView.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:00:30
 * Version: $Id$
 * Last-Updated: Fri Apr 19 16:21:35 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 38
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

class dtkComposerViewPrivate;

class DTKCOMPOSER_EXPORT  dtkComposerView : public QGraphicsView
{
    Q_OBJECT

public:
             dtkComposerView(QWidget *parent = 0);
    virtual ~dtkComposerView(void);

public:
    QAction *searchAction(void);

public:
    void scroll(int dx, int dy);

public slots:
    void search(void);

signals:
    void scrolled(void);

protected:
    void scrollContentsBy(int dx, int dy);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event);
#endif

private:
    dtkComposerViewPrivate *d;

private:
    friend class dtkComposerQuickView;
};
