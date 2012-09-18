/* dtkAbstractViewFactory.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:54:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: lun. sept. 10 17:12:51 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 150
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkAbstractView.h"
#include "dtkAbstractViewFactory.h"
#include "dtkAbstractViewAnimator.h"
#include "dtkAbstractViewNavigator.h"
#include "dtkAbstractViewInteractor.h"
#include "dtkSmartPointer.h"

class dtkAbstractViewFactoryPrivate
{
public:
    typedef QHash<               QString,      dtkAbstractViewFactory::dtkAbstractViewCreator>           dtkAbstractViewCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractViewFactory::dtkAbstractViewAnimatorCreator>   dtkAbstractViewAnimatorCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractViewFactory::dtkAbstractViewNavigatorCreator>  dtkAbstractViewNavigatorCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractViewFactory::dtkAbstractViewInteractorCreator> dtkAbstractViewInteractorCreatorHash;
    typedef QHash<QString,                     QString>                                                  dtkAbstractViewInterfacesHash;

public:
    QHash<QString, unsigned int> viewCount;
    QHash<QString, dtkAbstractView *> views;

public:
    dtkAbstractViewCreatorHash           creators;
    dtkAbstractViewAnimatorCreatorHash   animators;
    dtkAbstractViewNavigatorCreatorHash  navigators;
    dtkAbstractViewInteractorCreatorHash interactors;
    dtkAbstractViewInterfacesHash       interfaces;
};

DTKCORE_EXPORT dtkAbstractViewFactory *dtkAbstractViewFactory::instance(void)
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

    view->setObjectName(QString("%1%2").arg(view->metaObject()->className()).arg(d->viewCount[type]));

    d->viewCount[type]++;
    d->views[view->objectName()] = view;

    emit created(view, type);

    return view;
}

QStringList dtkAbstractViewFactory::implementations(const QString& interface)
{
    QStringList implementations;

    if(d->interfaces.keys().contains(interface))
        implementations << d->interfaces.values(interface);
    else
        qDebug() << "There is no available implementation of " << interface ;

    return implementations;
}

QStringList dtkAbstractViewFactory::interfaces(void)
{
    return d->interfaces.keys();
}

dtkSmartPointer<dtkAbstractView> dtkAbstractViewFactory::createSmartPointer(const QString& type)
{
    dtkSmartPointer<dtkAbstractView> view = this->create(type);
    return view;
}

dtkAbstractViewAnimator *dtkAbstractViewFactory::animator(const QString& type)
{
    foreach(dtkAbstractViewTypeHandler key, d->animators.keys())
        if (key.first == type)
            return d->animators[key]();

    return 0l;
}

dtkSmartPointer<dtkAbstractViewAnimator> dtkAbstractViewFactory::animatorSmartPointer(const QString& type)
{
    dtkSmartPointer<dtkAbstractViewAnimator> animator = this->animator(type);
    return animator;
}

dtkAbstractViewNavigator *dtkAbstractViewFactory::navigator(const QString& type)
{
    foreach(dtkAbstractViewTypeHandler key, d->navigators.keys())
        if (key.first == type)
            return d->navigators[key]();

    return 0l;
}

dtkSmartPointer<dtkAbstractViewNavigator> dtkAbstractViewFactory::navigatorSmartPointer(const QString& type)
{
    dtkSmartPointer<dtkAbstractViewNavigator> navigator = this->navigator(type);
    return navigator;
}

dtkAbstractViewInteractor *dtkAbstractViewFactory::interactor(const QString& type)
{
    foreach(dtkAbstractViewTypeHandler key, d->interactors.keys())
        if (key.first == type)
            return d->interactors[key]();

    return 0l;
}

dtkSmartPointer<dtkAbstractViewInteractor> dtkAbstractViewFactory::interactorSmartPointer(const QString& type)
{
    dtkSmartPointer<dtkAbstractViewInteractor> interactor = this->interactor(type);
    return interactor;
}

bool dtkAbstractViewFactory::registerViewType(const QString& type, dtkAbstractViewCreator func)
{
    qDebug()<<"dtkAbstractViewFactory::registerViewType ";
    if(!d->creators.contains(type)) {
        d->creators.insert(type, func);
        return true;
    }

    qDebug()<<"dtkAbstractViewFactory::registerViewType 2 ";

    return false;
}

bool dtkAbstractViewFactory::registerViewType(const QString& type, dtkAbstractViewCreator func, const QString& interface)
{
    if(!d->creators.contains(type)) {
        d->creators.insert(type, func);
        d->interfaces.insertMulti(interface, type);
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
    return d->viewCount[type];
}

QStringList dtkAbstractViewFactory::viewNames(void) const
{
    return d->views.keys();
}

QList<dtkAbstractView *> dtkAbstractViewFactory::views(void)
{
    return d->views.values();
}

dtkAbstractView *dtkAbstractViewFactory::view(const QString& name)
{
    return d->views.value(name);
}

QList<QString> dtkAbstractViewFactory::creators(void) const
{
    return d->creators.keys();
}

QList<dtkAbstractViewFactory::dtkAbstractViewTypeHandler> dtkAbstractViewFactory::animators(void) const
{
    return d->animators.keys();
}

QList<dtkAbstractViewFactory::dtkAbstractViewTypeHandler> dtkAbstractViewFactory::interactors(void) const
{
    return d->interactors.keys();
}

QList<dtkAbstractViewFactory::dtkAbstractViewTypeHandler> dtkAbstractViewFactory::navigators(void) const
{
    return d->navigators.keys();
}

void dtkAbstractViewFactory::clear(void)
{
    foreach(dtkAbstractView *view, d->views.values()) {
        view->deleteLater();
        view = NULL;
    }
    
    d->views.clear();
    d->viewCount.clear();
}

dtkAbstractViewFactory::dtkAbstractViewFactory(void) : dtkAbstractFactory(), d(new dtkAbstractViewFactoryPrivate)
{

}

dtkAbstractViewFactory::~dtkAbstractViewFactory(void)
{
    delete d;

    d = NULL;
}

DTKCORE_EXPORT dtkAbstractViewFactory *dtkAbstractViewFactory::s_instance = NULL;
