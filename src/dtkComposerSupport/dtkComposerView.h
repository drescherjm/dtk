/* dtkComposerView.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:00:30
 * Version: $Id$
 * Last-Updated: Thu Nov  8 13:43:14 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERVIEW_H
#define DTKCOMPOSERVIEW_H

#include "dtkComposerSupportExport.h"

#include <QtWidgets>

class dtkComposerViewPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerView : public QGraphicsView
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

#endif
