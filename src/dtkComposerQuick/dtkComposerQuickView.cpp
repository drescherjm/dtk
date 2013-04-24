/* dtkComposerQuickView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:39:39 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 17:08:25 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 87
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

    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::AllButtons);
    this->setFlag(QQuickItem::ItemHasContents, true);
    this->setFocus(true);
    this->setRenderTarget(QQuickPaintedItem::FramebufferObject);
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

    d->view->render(painter, this->contentsBoundingRect(), QRect());
}

void dtkComposerQuickView::keyPressEvent(QKeyEvent *event)
{
    if(!d->view)
	return;

    d->view->keyPressEvent(event);

    this->update();
}

void dtkComposerQuickView::mouseMoveEvent(QMouseEvent *event)
{
    if(!d->view)
	return;

    d->view->mouseMoveEvent(event);

    this->update();
}

void dtkComposerQuickView::mousePressEvent(QMouseEvent *event)
{
    if(!d->view)
	return;

    d->view->mousePressEvent(event);

    this->update();
}

void dtkComposerQuickView::mouseReleaseEvent(QMouseEvent *event)
{
    if(!d->view)
	return;

    d->view->mouseReleaseEvent(event);

    this->update();
}

#ifndef QT_NO_WHEELEVENT
void dtkComposerQuickView::wheelEvent(QWheelEvent *event)
{
    if(!d->view)
	return;

    d->view->wheelEvent(event);

    this->update();
}
#endif
