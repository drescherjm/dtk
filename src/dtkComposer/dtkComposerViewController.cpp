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

class dtkComposerViewControllerPrivate
{
public:
    QHash<QString, QWidget *> views;
};

dtkComposerViewController *dtkComposerViewController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkComposerViewController;

    return s_instance;
}

void dtkComposerViewController::insert(const QString& name, QWidget *view)
{
    d->views.insert(name, view);

    emit inserted(view, name);
}

QWidget *dtkComposerViewController::view(const QString& name)
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
