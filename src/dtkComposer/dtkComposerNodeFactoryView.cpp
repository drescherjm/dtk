// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

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
    dtkWidgetsTagCloudController *controller;
    dtkWidgetsTagCloudScope *scope;
    dtkWidgetsTagCloudView *view;
};

dtkComposerNodeFactoryView::dtkComposerNodeFactoryView(QWidget *parent) : QWidget(parent), d(new dtkComposerNodeFactoryViewPrivate)
{
    d->factory = NULL;

    d->scope = new dtkWidgetsTagCloudScope(this);
    d->scope->toggle();

    d->view = new dtkWidgetsTagCloudView(this);

    d->controller = new dtkWidgetsTagCloudController;
    d->controller->attach(d->scope);
    d->controller->attach(d->view);
    d->controller->onUnionMode(false);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->scope);
    layout->addWidget(d->view);

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

//
// dtkComposerNodeFactoryView.cpp ends here
