/* dtkComposerView.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:00:30
 * Version: $Id$
 * Last-Updated: Thu Apr 11 15:12:03 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 31
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QtGui>

class dtkComposerViewPrivate;

class dtkComposerView : public QGraphicsView
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
    void wheelEvent(QWheelEvent *event);

private:
    dtkComposerViewPrivate *d;

private:
    QPointF CurrentCenterPoint;
};

