/* dtk3DQuickView.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 21:49:58 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr  4 10:48:27 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 103
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

protected slots:
    void paint(QPainter *painter);

private:
    dtk3DQuickViewPrivate *d;
};

QML_DECLARE_TYPE(dtk3DQuickView)
