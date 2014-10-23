/* dtkComposerNodeFactoryView.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Apr 11 10:39:25 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 16:09:35 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 55
 */

/* Change Log:
 * 
 */

#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeFactoryView.h"

#include <dtkWidgets/dtkWidgetsTagCloud>
#include <dtkWidgets/dtkWidgetsTagCloudController>
#include <dtkWidgets/dtkWidgetsTagCloudScope>
#include <dtkWidgets/dtkWidgetsTagCloudView>

class dtkComposerNodeFactoryViewPrivate
{
public:
    dtkComposerNodeFactory *factory;

public:
    dtkWidgetsTagCloud *cloud;
    dtkWidgetsTagCloudController *controller;
    dtkWidgetsTagCloudScope *scope;
    dtkWidgetsTagCloudView *view;
};

dtkComposerNodeFactoryView::dtkComposerNodeFactoryView(QWidget *parent) : QWidget(parent), d(new dtkComposerNodeFactoryViewPrivate)
{
    d->factory = NULL;

    d->scope = new dtkWidgetsTagCloudScope(this);
    d->scope->toggle();

    d->cloud = new dtkWidgetsTagCloud(this);
    d->cloud->setSortingType(dtkWidgetsTagCloud::Alpha);
    d->cloud->setSortingOrder(dtkWidgetsTagCloud::Asc);
    d->cloud->setFontSize(17);
    d->cloud->setFontRange(15);

    d->view = new dtkWidgetsTagCloudView(this);

    d->controller = new dtkWidgetsTagCloudController;
    d->controller->attach(d->scope);
    d->controller->attach(d->view);
    d->controller->attach(d->cloud);
    d->controller->onUnionMode(false);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(d->cloud);
    splitter->addWidget(d->view);
    splitter->setOrientation(Qt::Vertical);
    splitter->setHandleWidth(1);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->scope);
    layout->addWidget(splitter);
}

dtkComposerNodeFactoryView::~dtkComposerNodeFactoryView(void)
{
    delete d->controller;
    delete d;

    d = NULL;
}

void dtkComposerNodeFactoryView::setFactory(dtkComposerNodeFactory *factory)
{
    d->factory = factory;

    foreach(QString node, factory->keys())
        d->controller->addItem(node, "description", QStringList() << node, "node", node);

    d->controller->addItem("Note", "<p>Notes help to identify and annotate some parts of a composition.</p>", QStringList() << "note", "note", "");
}

void dtkComposerNodeFactoryView::setDark(void)
{
    d->scope->setDark();
    d->view->setDark();
}

dtkWidgetsTagCloudView *dtkComposerNodeFactoryView::itemView(void) const
{
    return d->view;
}

dtkWidgetsTagCloud *dtkComposerNodeFactoryView::cloudView(void) const
{
    return d->cloud;
}

dtkWidgetsTagCloudScope *dtkComposerNodeFactoryView::scopeView(void) const
{
    return d->scope;
}
