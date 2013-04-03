/* dtk3DQuickView.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 21:49:58 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Apr  2 21:42:38 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 72
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtGui>
#include <QtQuick>

class dtk3DQuickViewPrivate;

class dtk3DQuickView : public QQuickItem, public QOpenGLFunctions
{
    Q_OBJECT

public:
     dtk3DQuickView(QQuickItem *parent = 0);
    ~dtk3DQuickView(void);
    
protected slots:
    void paint(void);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    void itemChange(ItemChange change, const ItemChangeData &);
    void geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry);

private:
    dtk3DQuickViewPrivate *d;
};

QML_DECLARE_TYPE(dtk3DQuickView)
