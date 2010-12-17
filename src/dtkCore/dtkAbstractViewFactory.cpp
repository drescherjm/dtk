/* dtkAbstractViewFactory.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:54:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jul  6 19:20:49 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 119
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkAbstractViewAnimator.h>
#include <dtkCore/dtkAbstractViewNavigator.h>
#include <dtkCore/dtkAbstractViewInteractor.h>

typedef QHash<QString, QList<dtkAbstractView*> > dtkAbstractViewHash;

class dtkAbstractViewFactoryPrivate
{
public:
    dtkAbstractViewHash views;

    dtkAbstractViewFactory::dtkAbstractViewCreatorHash           creators;
    dtkAbstractViewFactory::dtkAbstractViewAnimatorCreatorHash   animators;
    dtkAbstractViewFactory::dtkAbstractViewNavigatorCreatorHash  navigators;
    dtkAbstractViewFactory::dtkAbstractViewInteractorCreatorHash interactors;
};

dtkAbstractViewFactory *dtkAbstractViewFactory::instance(void)
{
    if(!s_instance)
        s_instance = new dtkAbstractViewFactory;

    return s_instance;
}

dtkAbstractView *dtkAbstractViewFactory::create(const QString& type)
{
    if(!d->creators.contains(type))
        return NULL;

    dtkAbstractView *view = d->creators[type]();

    foreach(dtkAbstractViewTypeHandler key, d->animators.keys())
        if(key.second.contains(type) || key.second.contains("any"))
            view->addAnimator(d->animators[key]());

    foreach(dtkAbstractViewTypeHandler key, d->navigators.keys())
        if(key.second.contains(type) || key.second.contains("any"))
            view->addNavigator(d->navigators[key]());

    foreach(dtkAbstractViewTypeHandler key, d->interactors.keys())
        if(key.second.contains(type) || key.second.contains("any"))
            view->addInteractor(d->interactors[key]());

    view->setObjectName(QString("%1%2").arg(view->metaObject()->className()).arg(d->views[type].count()));

    d->views[type] << view;

    emit created(view, type);

    return view;
}

dtkAbstractViewAnimator *dtkAbstractViewFactory::animator(const QString& type)
{
    foreach(dtkAbstractViewTypeHandler key, d->animators.keys())
        if (key.first == type)
            return d->animators[key]();

    return 0l;
}

dtkAbstractViewNavigator *dtkAbstractViewFactory::navigator(const QString& type)
{
    foreach(dtkAbstractViewTypeHandler key, d->navigators.keys())
        if (key.first == type)
            return d->navigators[key]();

    return 0l;
}

dtkAbstractViewInteractor *dtkAbstractViewFactory::interactor(const QString& type)
{
    foreach(dtkAbstractViewTypeHandler key, d->interactors.keys())
        if (key.first == type)
            return d->interactors[key]();

    return 0l;
}

bool dtkAbstractViewFactory::registerViewType(const QString& type, dtkAbstractViewCreator func)
{
    if(!d->creators.contains(type)) {
        d->creators.insert(type, func);
        return true;
    }

    return false;
}

bool dtkAbstractViewFactory::registerViewAnimatorType(const QString& type, const QStringList& handled, dtkAbstractViewAnimatorCreator func)
{
    if(!d->animators.contains(qMakePair(type, handled))) {
        d->animators.insert(qMakePair(type, handled), func);
        return true;
    }

    return false;
}

bool dtkAbstractViewFactory::registerViewNavigatorType(const QString& type, const QStringList& handled, dtkAbstractViewNavigatorCreator func)
{
    if(!d->navigators.contains(qMakePair(type, handled))) {
        d->navigators.insert(qMakePair(type, handled), func);
        return true;
    }

    return false;
}

bool dtkAbstractViewFactory::registerViewInteractorType(const QString& type, const QStringList& handled, dtkAbstractViewInteractorCreator func)
{
    if(!d->interactors.contains(qMakePair(type, handled))) {
        d->interactors.insert(qMakePair(type, handled), func);
        return true;
    }

    return false;
}

unsigned int dtkAbstractViewFactory::size(const QString& type) const
{
    return d->views[type].size();
}

dtkAbstractView *dtkAbstractViewFactory::get(const QString& type, int idx)
{
    return d->views[type].value(idx);
}

dtkAbstractView *dtkAbstractViewFactory::get(const QString& type, const QString& name)
{
    foreach(dtkAbstractView *view, d->views[type])
        if(view->name() == name)
            return view;

    return NULL;
}

dtkAbstractViewFactory::dtkAbstractViewFactory(void) : dtkAbstractFactory(), d(new dtkAbstractViewFactoryPrivate)
{

}

dtkAbstractViewFactory::~dtkAbstractViewFactory(void)
{
    delete d;

    d = NULL;
}

dtkAbstractViewFactory *dtkAbstractViewFactory::s_instance = NULL;
