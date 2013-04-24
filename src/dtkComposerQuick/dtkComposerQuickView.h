/* dtkComposerQuickView.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:36:56 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 12:57:35 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>
#include <QtGui>
#include <QtQuick>

class dtkComposerQuickViewPrivate;

class dtkComposerQuickView : public QQuickPaintedItem
{
    Q_OBJECT

public:
     dtkComposerQuickView(QQuickItem *parent = 0);
    ~dtkComposerQuickView(void);

protected slots:
    void paint(QPainter *painter);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event);
#endif

private:
    dtkComposerQuickViewPrivate *d;
};

QML_DECLARE_TYPE(dtkComposerQuickView)
