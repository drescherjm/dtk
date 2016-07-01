/* dtkComposerNodeFactoryView.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Apr 11 10:39:25 2013 (+0200)
 * Version: 
 * Last-Updated: ven. janv.  9 10:50:29 2015 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 141
 */

/* Change Log:
 * 
 */

#include "dtkComposerNodeFactory.h"
#include "dtkComposerNodeFactoryView.h"
#include "dtkComposerNodeMetaData.h"
#include "dtkComposerSceneNode.h"

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

    this->addNote();
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

    const QHash<QString, dtkComposerNodeMetaData *>& meta_datas = factory->metaDatas();
    QHash<QString, dtkComposerNodeMetaData *>::const_iterator cit = meta_datas.begin();
    QHash<QString, dtkComposerNodeMetaData *>::const_iterator cend = meta_datas.end();
    for(; cit != cend; ++cit) {
        dtkComposerNodeMetaData *md = *cit;
//        qDebug() << md->title() << md->description() << md->tags() << QString::number(md->kind()) << md->type();
        d->controller->addItem(md->title(), md->description(), md->tags(), "node", md->type());
    }
}

void dtkComposerNodeFactoryView::addNote(void)
{
    dtkComposerNodeMetaData *note_md = new dtkComposerNodeMetaData;
    if(note_md->setFromFile(":dtkComposer/dtkComposerNote.json")) {
        d->controller->addItem(note_md->title(), note_md->description(), note_md->tags(), "note", note_md->type());
    }
    delete note_md;
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

void dtkComposerNodeFactoryView::onShowNodeDocumentation(dtkComposerSceneNode *node)
{
    if(!node)
        return;

    dtkComposerNode* wrapee = node->wrapee();
    if(!wrapee)
        return;

    if (wrapee->nodeMetaData())
        d->view->onItemClicked(wrapee->nodeMetaData()->description());
}
