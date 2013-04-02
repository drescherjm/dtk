/* dtk3DQuickView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 22:19:13 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  1 22:40:18 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickView.h"

#include <dtk3D>

#include <Qt3D/QGLPainter>

class dtk3DQuickViewPrivate
{
public:
    dtk3DView *view;
};

dtk3DQuickView::dtk3DQuickView(QQuickItem *parent) : QQuickPaintedItem(parent), d(new dtk3DQuickViewPrivate)
{
    d->view = new dtk3DView;
}

dtk3DQuickView::~dtk3DQuickView(void)
{
    delete d;
}

void dtk3DQuickView::paint(QPainter *painter)
{
    QGLPainter gl_painter(painter);

    d->view->paintGL(&gl_painter);
}
