/* dtk3DQuickView.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 21:49:58 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Apr  2 17:00:22 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 60
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
    void sync(void);

protected:
    void itemChange(ItemChange change, const ItemChangeData &);

private:
    dtk3DQuickViewPrivate *d;
};

QML_DECLARE_TYPE(dtk3DQuickView)
