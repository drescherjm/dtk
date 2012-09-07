/* dtkAbstractView.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:01:09 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Thu May  3 10:39:55 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 325
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkAbstractData.h"
#include "dtkAbstractView.h"
#include "dtkAbstractView_p.h"
#include "dtkAbstractViewAnimator.h"
#include "dtkAbstractViewNavigator.h"
#include "dtkAbstractViewInteractor.h"

#include <dtkMath/dtkVector3D.h>
#include <dtkMath/dtkQuaternion.h>

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkAbstractView implementation
// /////////////////////////////////////////////////////////////////

dtkAbstractView::dtkAbstractView(dtkAbstractView *parent) : dtkAbstractObject(*new dtkAbstractViewPrivate, parent)
{
    DTK_D(dtkAbstractView);

    d->stereo = false;
}

dtkAbstractView::dtkAbstractView(const dtkAbstractView& other) : dtkAbstractObject(*new dtkAbstractViewPrivate(*other.d_func()), other)
{

}

dtkAbstractView& dtkAbstractView::operator=(const dtkAbstractView& other)
{
    dtkAbstractObject::operator=(other);

    DTK_D(dtkAbstractView);

    d->animators   = other.d_func()->animators;
    d->navigators  = other.d_func()->navigators;
    d->interactors = other.d_func()->interactors;

    return (*this);
}

dtkAbstractView::~dtkAbstractView(void)
{

}

void dtkAbstractView::initialize(void)
{

}

void dtkAbstractView::uninitialize(void)
{

}

void dtkAbstractView::link(dtkAbstractView *other)
{
    DTK_UNUSED(other);
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::unlink(dtkAbstractView *other)
{
    DTK_UNUSED(other);
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::select(dtkAbstractData *data)
{
    DTK_UNUSED(data);
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::unselect(dtkAbstractData *data)
{
    DTK_UNUSED(data);
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::setStereo(bool on)
{
    DTK_D(dtkAbstractView);

    d->stereo = on;
}

void dtkAbstractView::setView(void *)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::setData(dtkAbstractData *data)
{
    DTK_DEFAULT_IMPLEMENTATION;

    DTK_D(dtkAbstractView);

    foreach(dtkAbstractViewAnimator *animator, d->animators)
        if (animator->enabled())
            animator->setData(data);

    foreach(dtkAbstractViewInteractor *interactor, d->interactors)
      if (interactor->enabled())
	interactor->setData(data);
}

void dtkAbstractView::setData(dtkAbstractData *data, int channel)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(data);
    DTK_UNUSED(channel);
}

void dtkAbstractView::setBackgroundColor(int red, int green, int blue)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(red);
    DTK_UNUSED(green);
    DTK_UNUSED(blue);
}

void dtkAbstractView::setBackgroundColor(double red, double green, double blue)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(red);
    DTK_UNUSED(green);
    DTK_UNUSED(blue);
}

void *dtkAbstractView::view(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

void *dtkAbstractView::data(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

void *dtkAbstractView::data(int channel)
{
    DTK_UNUSED(channel);
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

bool dtkAbstractView::stereo(void)
{
    DTK_D(dtkAbstractView);

    return d->stereo;
}

void dtkAbstractView::clear(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::reset(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::update(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

QWidget *dtkAbstractView::widget(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

void dtkAbstractView::close(void)
{
    emit closed();
}

void dtkAbstractView::showFullScreen(void)
{
    if(QWidget *widget = this->widget())
        widget->showFullScreen();
}

void dtkAbstractView::showMinimized(void)
{
    if(QWidget *widget = this->widget())
        widget->showMinimized();
}

void dtkAbstractView::showMaximized(void)
{
    if(QWidget *widget = this->widget())
        widget->showMaximized();
}

void dtkAbstractView::showNormal(void)
{
    if(QWidget *widget = this->widget())
        widget->showNormal();
}

void dtkAbstractView::show(void)
{
    if(QWidget *widget = this->widget())
        widget->show();
}

void dtkAbstractView::resize(int width, int height)
{
    if(QWidget *widget = this->widget())
        widget->resize(width, height);
}

void dtkAbstractView::addAnimator(dtkAbstractViewAnimator *animator)
{
    if(animator->identifier().isEmpty()) {
        dtkDebug() << "No identifier specified for animator. Not add to" << this->identifier();
        return;
    }

    DTK_D(dtkAbstractView);

    d->animators.insert(animator->identifier(), animator);
}

void dtkAbstractView::addNavigator(dtkAbstractViewNavigator *navigator)
{
    if(navigator->identifier().isEmpty()) {
        dtkDebug() << "No identifier specified for navigator. Not add to" << this->identifier();
        return;
    }

    DTK_D(dtkAbstractView);

    d->navigators.insert(navigator->identifier(), navigator);
}

void dtkAbstractView::addInteractor(dtkAbstractViewInteractor *interactor)
{
    if(interactor->identifier().isEmpty()) {
        dtkDebug() << "No identifier specified for interactor. Not add to" << this->identifier();
        return;
    }

    if(interactor) {        
        DTK_D(dtkAbstractView);

        d->interactors.insert(interactor->identifier(), interactor);
    }
}

void dtkAbstractView::enableAnimator(const QString& animator)
{
    DTK_D(dtkAbstractView);

    if (d->animators.contains(animator)) {
        d->animators.value(animator)->setView(this);
        d->animators.value(animator)->enable();
    } else
        dtkDebug() << identifier() << " has no such animator: " << animator;
}

void dtkAbstractView::disableAnimator(const QString& animator)
{
    DTK_D(dtkAbstractView);

    if (d->animators.contains(animator))
        d->animators.value(animator)->disable();
}

void dtkAbstractView::enableNavigator(const QString& navigator)
{
    DTK_D(dtkAbstractView);

    if (d->navigators.contains(navigator)) {
//      d->navigators.value(navigator)->setView(this);
        d->navigators.value(navigator)->enable();
    } else
        dtkDebug() << identifier() << " has no such navigator: " << navigator;
}

void dtkAbstractView::disableNavigator(const QString& navigator)
{
    DTK_D(dtkAbstractView);

    if (d->navigators.contains(navigator))
        d->navigators.value(navigator)->disable();
}

void dtkAbstractView::enableInteractor(const QString& interactor)
{
    DTK_D(dtkAbstractView);

    if (d->interactors.contains(interactor)) {
        d->interactors.value(interactor)->setView(this);
        d->interactors.value(interactor)->enable();
    } else
        dtkDebug() << identifier() << " has no such interactor: " << interactor;
}

void dtkAbstractView::disableInteractor(const QString& interactor)
{
    DTK_D(dtkAbstractView);

    if (d->interactors.contains(interactor))
        d->interactors.value(interactor)->disable();
}

dtkAbstractViewAnimator *dtkAbstractView::animator(const QString& type)
{
    DTK_D(dtkAbstractView);

    if (d->animators.contains(type))
        return d->animators.value(type);

    return NULL;
}

dtkAbstractViewNavigator *dtkAbstractView::navigator(const QString& type)
{
    DTK_D(dtkAbstractView);

    if (d->navigators.contains(type))
        return d->navigators.value(type);

    return NULL;
}

dtkAbstractViewInteractor *dtkAbstractView::interactor(const QString& type)
{
    DTK_D(dtkAbstractView);

    if (d->interactors.contains(type))
        return d->interactors.value(type);

    return NULL;
}

QList<dtkAbstractViewAnimator *> dtkAbstractView::animators(void) const
{
    DTK_D(const dtkAbstractView);

    QList<dtkAbstractViewAnimator *> ret;
#if QT_VERSION > 0x0406FF
    ret.reserve(d->animators.size());
#endif
    foreach( dtkSmartPointer<dtkAbstractViewAnimator> value, d->animators )
        ret.push_back(value.data());
    return ret;
}

QList<dtkAbstractViewNavigator *> dtkAbstractView::navigators(void) const
{
    DTK_D(const dtkAbstractView);

    QList<dtkAbstractViewNavigator *> ret;
#if QT_VERSION > 0x0406FF
    ret.reserve(d->navigators.size());
#endif
    foreach( dtkSmartPointer<dtkAbstractViewNavigator> value, d->navigators )
        ret.push_back(value.data());
    return ret;
}

QList<dtkAbstractViewInteractor *> dtkAbstractView::interactors(void) const
{
    DTK_D(const dtkAbstractView);

    QList<dtkAbstractViewInteractor *> ret;
#if QT_VERSION > 0x0406FF
    ret.reserve(d->interactors.size());
#endif
    foreach( dtkSmartPointer<dtkAbstractViewInteractor> value, d->interactors )
        ret.push_back(value.data());
    return ret;
}

void dtkAbstractView::setHeadPosition(dtkVector3D<double> position)
{
    DTK_UNUSED(position);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::setHeadOrientation(dtkQuaternion<double> orientation)
{
    DTK_UNUSED(orientation);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::setUpperLeft(dtkVector3D<double> position)
{
    DTK_UNUSED(position);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::setLowerLeft(dtkVector3D<double> position)
{
    DTK_UNUSED(position);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::setLowerRight(dtkVector3D<double> position)
{
    DTK_UNUSED(position);

    DTK_DEFAULT_IMPLEMENTATION;
}

// /////////////////////////////////////////////////////////////////
// Debug stream operators
// /////////////////////////////////////////////////////////////////

QDebug operator<<(QDebug debug, const dtkAbstractView& viewer)
{
    debug.nospace() << viewer.identifier();

    return debug.space();
}

QDebug operator<<(QDebug debug, dtkAbstractView *viewer)
{
    debug.nospace() << viewer->identifier();

    return debug.space();
}
