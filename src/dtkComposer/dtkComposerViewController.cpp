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

#include "dtkComposerViewController.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerNode.h"

class dtkComposerViewControllerPrivate
{
public:
    QHash<QString, dtkComposerViewWidget *> views;
};

dtkComposerViewController *dtkComposerViewController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkComposerViewController;

    return s_instance;
}

void dtkComposerViewController::insert(dtkComposerSceneNode *node)
{
    d->views.insert(node->title(), node->wrapee()->widget());

    emit inserted(node->wrapee()->widget(), node->title());
}

dtkComposerViewWidget *dtkComposerViewController::view(const QString& name)
{
    return d->views.value(name);
}

QStringList dtkComposerViewController::viewNames(void)
{
    return d->views.keys();
}

dtkComposerViewController::dtkComposerViewController(void) : QObject()
{
    d = new dtkComposerViewControllerPrivate;
}

dtkComposerViewController::~dtkComposerViewController(void)
{
    delete d;
}

dtkComposerViewController *dtkComposerViewController::s_instance = NULL;

//
// dtkComposerViewController.cpp ends here
