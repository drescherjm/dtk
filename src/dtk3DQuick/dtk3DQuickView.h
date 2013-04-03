/* dtk3DQuickView.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 21:49:58 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 11:59:51 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 87
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtGui>
#include <QtQuick>

class dtk3DQuickViewPrivate;

class dtk3DQuickView : public QQuickPaintedItem
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
