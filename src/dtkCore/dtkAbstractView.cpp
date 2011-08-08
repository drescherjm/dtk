/* dtkAbstractView.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:01:09 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May  9 14:41:38 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 272
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewAnimator.h>
#include <dtkCore/dtkAbstractViewNavigator.h>
#include <dtkCore/dtkAbstractViewInteractor.h>
#include <dtkCore/dtkLog.h>
#include <dtkCore/dtkSmartPointer.h>

class dtkAbstractViewPrivate
{
public:
    bool stereo;

    QMap<QString, dtkSmartPointer<dtkAbstractViewAnimator> >   animators;
    QMap<QString, dtkSmartPointer<dtkAbstractViewNavigator> >  navigators;
    QMap<QString, dtkSmartPointer<dtkAbstractViewInteractor> > interactors;
};

dtkAbstractView::dtkAbstractView(dtkAbstractView *parent) : dtkAbstractObject(parent), d(new dtkAbstractViewPrivate)
{

}

dtkAbstractView::dtkAbstractView(const dtkAbstractView& view) : dtkAbstractObject(), d(new dtkAbstractViewPrivate)
{
    d->animators   = view.d->animators;
    d->navigators  = view.d->navigators;
    d->interactors = view.d->interactors;
}

dtkAbstractView::~dtkAbstractView(void)
{
    delete d;
    
    d = NULL;
}

void dtkAbstractView::link(dtkAbstractView *other)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::unlink(dtkAbstractView *other)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::select(dtkAbstractData *data)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::unselect(dtkAbstractData *data)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::setStereo(bool on)
{
    d->stereo = on;
}

void dtkAbstractView::setView(void *)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::setData(dtkAbstractData *data)
{
    DTK_DEFAULT_IMPLEMENTATION;

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
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

bool dtkAbstractView::stereo(void)
{
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
    d->animators.insert(animator->description(), animator);
}

void dtkAbstractView::addNavigator(dtkAbstractViewNavigator *navigator)
{
    d->navigators.insert(navigator->description(), navigator);
}

void dtkAbstractView::addInteractor(dtkAbstractViewInteractor *interactor)
{
    if(interactor)
        d->interactors.insert(interactor->description(), interactor);
}

void dtkAbstractView::enableAnimator(const QString& animator)
{
    if (d->animators.contains(animator)) {
        d->animators.value(animator)->setView(this);
        d->animators.value(animator)->enable();
    } else
        dtkDebug() << description() << " has no such animator: " << animator;
}

void dtkAbstractView::disableAnimator(const QString& animator)
{
    if (d->animators.contains(animator))
        d->animators.value(animator)->disable();
}

void dtkAbstractView::enableNavigator(const QString& navigator)
{
    if (d->navigators.contains(navigator)) {
//      d->navigators.value(navigator)->setView(this);
        d->navigators.value(navigator)->enable();
    } else
        dtkDebug() << description() << " has no such navigator: " << navigator;
}

void dtkAbstractView::disableNavigator(const QString& navigator)
{
    if (d->navigators.contains(navigator))
        d->navigators.value(navigator)->disable();
}

void dtkAbstractView::enableInteractor(const QString& interactor)
{
    if (d->interactors.contains(interactor)) {
        d->interactors.value(interactor)->setView(this);
        d->interactors.value(interactor)->enable();
    } else
        dtkDebug() << description() << " has no such interactor: " << interactor;
}

void dtkAbstractView::disableInteractor(const QString& interactor)
{
    if (d->interactors.contains(interactor))
        d->interactors.value(interactor)->disable();
}

dtkAbstractViewAnimator *dtkAbstractView::animator(const QString& type)
{
    if (d->animators.contains(type))
        return d->animators.value(type);

    return NULL;
}

dtkAbstractViewNavigator *dtkAbstractView::navigator(const QString& type)
{
    if (d->navigators.contains(type))
        return d->navigators.value(type);

    return NULL;
}

dtkAbstractViewInteractor *dtkAbstractView::interactor(const QString& type)
{
    if (d->interactors.contains(type))
        return d->interactors.value(type);

    return NULL;
}

QList<dtkAbstractViewAnimator *> dtkAbstractView::animators(void) const
{
    QList<dtkAbstractViewAnimator *> ret;
    ret.reserve(d->animators.size());
    foreach( dtkSmartPointer<dtkAbstractViewAnimator> value, d->animators )
        ret.push_back(value.data());
    return ret;
}

QList<dtkAbstractViewNavigator *> dtkAbstractView::navigators(void) const
{
    QList<dtkAbstractViewNavigator *> ret;
    ret.reserve(d->navigators.size());
    foreach( dtkSmartPointer<dtkAbstractViewNavigator> value, d->navigators )
        ret.push_back(value.data());
    return ret;
}

QList<dtkAbstractViewInteractor *> dtkAbstractView::interactors(void) const
{
    QList<dtkAbstractViewInteractor *> ret;
    ret.reserve(d->interactors.size());
    foreach( dtkSmartPointer<dtkAbstractViewInteractor> value, d->interactors )
        ret.push_back(value.data());
    return ret;
}

// /////////////////////////////////////////////////////////////////
// vr compatibility api
// /////////////////////////////////////////////////////////////////

void dtkAbstractView::initialize(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::uninitialize(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::enableInteraction(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::disableInteraction(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::bounds(float& xmin, float& xmax, float& ymin, float& ymax, float &zmin, float& zmax)
{
    DTK_UNUSED(xmin);
    DTK_UNUSED(xmax);
    DTK_UNUSED(ymin);
    DTK_UNUSED(ymax);
    DTK_UNUSED(zmin);
    DTK_UNUSED(zmax);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::cameraUp(double *coordinates)
{
    DTK_UNUSED(coordinates);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::cameraPosition(double *coordinates)
{
    DTK_UNUSED(coordinates);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::cameraFocalPoint(double *coordinates)
{
    DTK_UNUSED(coordinates);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::setCameraPosition(double x, double y, double z)
{
    DTK_UNUSED(x);
    DTK_UNUSED(y);
    DTK_UNUSED(z);

    DTK_DEFAULT_IMPLEMENTATION;
}

void dtkAbstractView::setCameraClippingRange(double near, double far)
{
    DTK_UNUSED(near);
    DTK_UNUSED(far);

    DTK_DEFAULT_IMPLEMENTATION;
}

QString dtkAbstractView::cameraProjectionMode(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return "None";
}

double dtkAbstractView::cameraViewAngle(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 0.0;
}

double dtkAbstractView::cameraZoom(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return 1.0;
}

// /////////////////////////////////////////////////////////////////
// Debug stream operators
// /////////////////////////////////////////////////////////////////

QDebug operator<<(QDebug debug, const dtkAbstractView& viewer)
{
    debug.nospace() << viewer.description();

    return debug.space();
}

QDebug operator<<(QDebug debug, dtkAbstractView *viewer)
{
    debug.nospace() << viewer->description();

    return debug.space();
}
