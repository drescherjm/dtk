/* dtk3DQuickView.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 21:49:58 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 16:51:49 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 95
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtGui>
#include <QtQuick>

class dtk3DQuickViewPrivate;

class dtk3DQuickView : public QQuickPaintedItem, public QOpenGLFunctions
{
    Q_OBJECT

public:
     dtk3DQuickView(QQuickItem *parent = 0);
    ~dtk3DQuickView(void);
    
protected slots:
    void paint(QPainter *painter);

private:
    dtk3DQuickViewPrivate *d;
};

QML_DECLARE_TYPE(dtk3DQuickView)
