/* tstWidget.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:21:15 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 21 19:21:20 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef TSTWIDGET_H
#define TSTWIDGET_H

#include <QtCore>
#include <QtGui>

class tstWidgetPrivate;

class tstWidget : public QWidget
{
    Q_OBJECT

public:
     tstWidget(QWidget *parent = 0);
    ~tstWidget(void);

    QSize sizeHint(void) const;

    void setTracker(QUrl tracker);

protected:
    bool event(QEvent *event);
    bool gestureEvent(QGestureEvent *event);
    void paintEvent(QPaintEvent *event);

protected:
    void panGestureEvent(QPanGesture *event);
    void pinchGestureEvent(QPinchGesture *event);
    void swipeGestureEvent(QSwipeGesture *event);
    void clearGestureEvent(QGesture *event);

private:
    tstWidgetPrivate *d;
};

#endif // TSTWIDGET_H
