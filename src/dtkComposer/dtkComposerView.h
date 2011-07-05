/* dtkComposerView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:06:52 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul  5 18:50:08 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 34
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
    virtual ~dtkComposerView(void);

    void setBackgroundColor(const QColor &color);
    
public slots:
    void onCenterOn(const QPointF& point);
    void onFitInView(const QRectF& rect);

protected:
    void scrollContentsBy(int dx, int dy);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};

#endif
