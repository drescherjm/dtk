/* dtkComposerQuickView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:39:39 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 10:43:25 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickView"

#include <dtkComposer>

class dtkComposerQuickViewPrivate
{
public:
    dtkComposerView *view;
};

dtkComposerQuickView::dtkComposerQuickView(QQuickItem *parent) : QQuickPaintedItem(parent), d(new dtkComposerQuickViewPrivate)
{
    d->view = new dtkComposerView;
}

dtkComposerQuickView::~dtkComposerQuickView(void)
{
    delete d->view;
}

void dtkComposerQuickView::paint(QPainter *painter)
{
    d->view->render(painter);
}
