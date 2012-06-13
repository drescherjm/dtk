/* dtkComposerView.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:00:30
 * Version: $Id$
 * Last-Updated: Thu Apr 19 11:11:43 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 25
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

private:
    dtkComposerViewPrivate *d;

private:
    QPointF CurrentCenterPoint;
};

#endif
