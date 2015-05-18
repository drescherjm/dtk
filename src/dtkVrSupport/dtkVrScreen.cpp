/* dtkVrScreen.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 21:10:30 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 19:40:34 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 76
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkVrScreen.h"

class dtkVrScreenPrivate
{
public:
    dtkDeprecated::dtkVector3D<double> x;
    dtkDeprecated::dtkVector3D<double> y;

    dtkDeprecated::dtkVector3D<double> lowerLeft;
    dtkDeprecated::dtkVector3D<double> upperLeft;
    dtkDeprecated::dtkVector3D<double> lowerRight;
    dtkDeprecated::dtkVector3D<double> upperRight;

    double width;
    double height;
};

dtkVrScreen::dtkVrScreen(const dtkDeprecated::dtkVector3D<double>& lowerLeft, const dtkDeprecated::dtkVector3D<double>& lowerRight, const dtkDeprecated::dtkVector3D<double>& upperLeft) : d(new dtkVrScreenPrivate)
{
    d->lowerLeft = lowerLeft;
    d->upperLeft = upperLeft;
    d->lowerRight = lowerRight;

    this->initialize();
}

dtkVrScreen::dtkVrScreen(const dtkVrScreen& other)
{
    d->lowerLeft = other.d->lowerLeft;
    d->upperLeft = other.d->upperLeft;
    d->lowerRight = other.d->lowerRight;

    this->initialize();
}

dtkVrScreen::~dtkVrScreen(void)
{
    delete d;

    d = NULL;
}

void dtkVrScreen::initialize(void)
{
    d->x = d->lowerRight - d->lowerLeft;
    d->width = d->x.norm();
    d->y = d->upperLeft - d->lowerLeft;
    d->height = d->y.norm();

    d->upperRight = d->lowerRight + d->y*d->height;
}

void dtkVrScreen::uninitialize(void)
{

}

const dtkDeprecated::dtkVector3D<double>& dtkVrScreen::lowerLeft(void) const
{
    return d->lowerLeft;
}

const dtkDeprecated::dtkVector3D<double>& dtkVrScreen::upperLeft(void) const
{
    return d->upperLeft;
}

const dtkDeprecated::dtkVector3D<double>& dtkVrScreen::lowerRight(void) const
{
    return d->lowerRight;
}

const dtkDeprecated::dtkVector3D<double>& dtkVrScreen::upperRight(void) const
{
    return d->upperRight;
}

const dtkDeprecated::dtkVector3D<double>& dtkVrScreen::up(void) const
{
    return d->y;
}

const dtkDeprecated::dtkVector3D<double>& dtkVrScreen::right(void) const
{
    return d->x;
}

double dtkVrScreen::width(void) const
{
    return d->width;
}

double dtkVrScreen::height(void) const
{
    return d->height;
}

const dtkDeprecated::dtkVector3D<double> dtkVrScreen::screens[5][3] = {
    { dtkDeprecated::dtkVector3D<double>(-1.6, -0.8, -0.05), dtkDeprecated::dtkVector3D<double>(-1.6, 2.4, -0.05), dtkDeprecated::dtkVector3D<double>(-1.6, -0.8,  2.35)}, // left
    { dtkDeprecated::dtkVector3D<double>(-1.6,  2.4, -0.05), dtkDeprecated::dtkVector3D<double>( 1.6, 2.4, -0.05), dtkDeprecated::dtkVector3D<double>(-1.6,  2.4,  2.35)}, // front
    { dtkDeprecated::dtkVector3D<double>( 1.6,  2.4, -0.05), dtkDeprecated::dtkVector3D<double>( 1.6,-0.8, -0.05), dtkDeprecated::dtkVector3D<double>( 1.6,  2.4,  2.35)}, // right
    { dtkDeprecated::dtkVector3D<double>(-1.6,  0.0, -0.05), dtkDeprecated::dtkVector3D<double>( 1.6, 0.0, -0.05), dtkDeprecated::dtkVector3D<double>(-1.6,  2.4, -0.05)}, // bottom
    { dtkDeprecated::dtkVector3D<double>(-2.05, 1.5,  0.76), dtkDeprecated::dtkVector3D<double>( 2.05, 1.5, 0.76), dtkDeprecated::dtkVector3D<double>(-2.05, 1.5,  2.16)}  // wall
};
