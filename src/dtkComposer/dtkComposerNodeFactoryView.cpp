/* dtkComposerNodeFactoryView.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Apr 11 10:39:25 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr 11 10:42:57 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 14
 */

/* Change Log:
 * 
 */

#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeFactoryView.h"

// #include <dtkGui/dtkSplitter.h>
// #include <dtkGui/dtkTagCloud.h>

class dtkComposerNodeFactoryViewPrivate
{
public:
    dtkComposerNodeFactory *factory;

public:
    // dtkTagScope *scope;
    // dtkTagCloud *cloud;
    // dtkItemView *view;

public:
    // dtkTagController *controller;
};

dtkComposerNodeFactoryView::dtkComposerNodeFactoryView(QWidget *parent) : QWidget(parent), d(new dtkComposerNodeFactoryViewPrivate)
{
    d->factory = NULL;

    // d->scope = new dtkTagScope(this);
    // d->scope->toggle();

    // d->cloud = new dtkTagCloud(this);
    // d->cloud->setSortingType(dtkTagCloud::Alpha);
    // d->cloud->setSortingOrder(dtkTagCloud::Asc);
    // d->cloud->setFontSize(14);
    // d->cloud->setFontRange(10);

    // d->view = new dtkItemView(this);

    // d->controller = new dtkTagController;
    // d->controller->attach(d->scope);
    // d->controller->attach(d->view);
    // d->controller->attach(d->cloud);
    // d->controller->onUnionMode(false);

    // dtkSplitter *splitter = new dtkSplitter(this);
    // splitter->addWidget(d->cloud);
    // splitter->addWidget(d->view);
    // splitter->setOrientation(Qt::Vertical);
    // splitter->setSizes(QList<int>() << 150 << 350);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    // layout->addWidget(d->scope);
    // layout->addWidget(splitter);
}

dtkComposerNodeFactoryView::~dtkComposerNodeFactoryView(void)
{
    //delete d->controller;
    delete d;

    d = NULL;
}

void dtkComposerNodeFactoryView::setFactory(dtkComposerNodeFactory *factory)
{
    d->factory = factory;

    // foreach(QString node, factory->nodes())
    //     d->controller->addItem(node, factory->descriptions().value(node), factory->tags().value(node), "node", factory->types().value(node));
 
    // d->controller->addItem("Note", "<p>Notes help to identify and annotate some parts of a composition.</p>", QStringList() << "note", "note", "");
}

void dtkComposerNodeFactoryView::setDark(void)
{
    //d->scope->setDark();
    // d->view->setDark();
}
