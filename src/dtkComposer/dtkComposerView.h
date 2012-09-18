/* dtkComposerView.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:00:30
 * Version: $Id$
 * Last-Updated: jeu. sept. 13 17:51:49 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 26
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

#include <QtGui>

class dtkComposerViewPrivate;

class DTKCOMPOSER_EXPORT dtkComposerView : public QGraphicsView
{
    Q_OBJECT

public:
             dtkComposerView(QWidget *parent = 0);
    virtual ~dtkComposerView(void);

public:
    void scroll(int dx, int dy);

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
