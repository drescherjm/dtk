/* dtkComposerQuickView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:39:39 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 13:38:49 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 47
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickScene"
#include "dtkComposerQuickView"

#include <dtkComposer>

class dtkComposerQuickViewPrivate
{
public:
    dtkComposerView *view;

public:
    bool initialized;
};

dtkComposerQuickView::dtkComposerQuickView(QQuickItem *parent) : QQuickPaintedItem(parent), d(new dtkComposerQuickViewPrivate)
{
    d->view = new dtkComposerView;

    d->initialized = false;
}

dtkComposerQuickView::~dtkComposerQuickView(void)
{
    delete d->view;
}

void dtkComposerQuickView::paint(QPainter *painter)
{
    if(!d->initialized) {
	d->initialized = true;

	foreach(QObject *object, this->children()) {
	    if(dtkComposerQuickScene *scene = qobject_cast<dtkComposerQuickScene *>(object))
		d->view->setScene(scene->scene());
	}
    }

    d->view->render(painter, this->contentsBoundingRect(), QRect(), Qt::IgnoreAspectRatio);
}
