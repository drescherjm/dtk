/* dtk3DQuickView.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 21:49:58 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 10:44:31 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 129
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtk3D>

#include <QtGui>
#include <QtQuick>

class dtk3DQuickViewPrivate;

class dtk3DQuickView : public QQuickPaintedItem, public QOpenGLFunctions
{
    Q_OBJECT

public:
     dtk3DQuickView(QQuickItem *parent = 0);
    ~dtk3DQuickView(void);
    
public:
    dtk3DView *view(void);

public:
    Q_INVOKABLE void fit(void);
    Q_INVOKABLE void fitFromTop(void);
    Q_INVOKABLE void fitFromBack(void);
    Q_INVOKABLE void fitFromLeft(void);
    Q_INVOKABLE void fitFromFront(void);
    Q_INVOKABLE void fitFromRight(void);
    Q_INVOKABLE void fitFromBottom(void);

public:
    Q_INVOKABLE void togglePickPainting(void);

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
    dtk3DQuickViewPrivate *d;
};

QML_DECLARE_TYPE(dtk3DQuickView)
