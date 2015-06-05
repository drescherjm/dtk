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

#include "dtkWidgetsViewController.h"

class dtkWidgetsViewControllerPrivate
{
public:
    QHash<QString, QWidget *> views;
};

dtkWidgetsViewController *dtkWidgetsViewController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkWidgetsViewController;

    return s_instance;
}

void dtkWidgetsViewController::insert(const QString& name, QWidget *view)
{
    d->views.insert(name, view);

    emit inserted(view, name);
}

QWidget *dtkWidgetsViewController::view(const QString& name)
{
    return d->views.value(name);
}

QStringList dtkWidgetsViewController::viewNames(void)
{
    return d->views.keys();
}

dtkWidgetsViewController::dtkWidgetsViewController(void) : QObject()
{
    d = new dtkWidgetsViewControllerPrivate;
}

dtkWidgetsViewController::~dtkWidgetsViewController(void)
{
    delete d;
}

dtkWidgetsViewController *dtkWidgetsViewController::s_instance = NULL;

//
// dtkWidgetsViewController.cpp ends here
