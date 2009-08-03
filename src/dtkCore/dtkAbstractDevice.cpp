/* dtkAbstractDevice.cpp --- 
 * 
 * Author: Jean-Christophe Lombardo
 * Copyright (C) 2009 - Jean-Christophe Lombardo, Inria
 * Created: Mon Mar 23 08:51:30 2009
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:34:34 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDevice.h>
#include <dtkCore/dtkAbstractViewInteractor.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkAbstractViewInteractor.h>
#include <dtkCore/dtkAbstractViewNavigator.h>

typedef QHash<QString, dtkAbstractViewInteractor *> ViewInteractorMap;
typedef QHash<QString, dtkAbstractViewNavigator *> ViewNavigatorMap;

class dtkAbstractDevicePrivate
{
public:
    QString name;
    ViewInteractorMap interactors;
    ViewNavigatorMap  navigators;
};

dtkAbstractDevice::dtkAbstractDevice(QString name, dtkAbstractObject *parent) : dtkAbstractObject(parent), d(new dtkAbstractDevicePrivate)
{
    d->name = name;
}

dtkAbstractDevice::dtkAbstractDevice(const dtkAbstractDevice& data) : dtkAbstractObject(), d(new dtkAbstractDevicePrivate)
{
    d->interactors = data.d->interactors;
    d->name        = data.d->name;
}

dtkAbstractDevice::~dtkAbstractDevice(void)
{
    d->interactors.clear();

    delete d;

    d = NULL;
}


QString dtkAbstractDevice::description(void) const
{
    return "dtkAbstractDevice";
}

QString dtkAbstractDevice::name(void)
{
    return d->name;
}

dtkAbstractViewInteractor *dtkAbstractDevice::interactor(QString name)
{
    dtkAbstractViewInteractor *itc = 0;

    if (!d->interactors.contains(name)) {
        itc = dtkAbstractViewFactory::instance()->interactor(name);
        d->interactors.insert(name, itc);
    } else {
        itc = d->interactors.value(name);
    }

    if (itc) {
        connect(this, SIGNAL(buttonPressed(int)),  itc, SLOT(buttonPressed(int)));
        connect(this, SIGNAL(buttonReleased(int)), itc, SLOT(buttonReleased(int)));
    }

    return itc;
}

dtkAbstractViewNavigator *dtkAbstractDevice::navigator(QString name)
{
    dtkAbstractViewNavigator *navigator = 0;

    if (!d->navigators.contains(name)) {
        navigator = dtkAbstractViewFactory::instance()->navigator(name);
        d->navigators.insert(name, navigator);
    } else {
        navigator = d->navigators.value(name);
    }

    if (navigator) {
        connect(this, SIGNAL(buttonPressed(int)),  navigator, SLOT(buttonPressed(int)));
        connect(this, SIGNAL(buttonReleased(int)), navigator, SLOT(buttonReleased(int)));
    }

    return navigator;
}
