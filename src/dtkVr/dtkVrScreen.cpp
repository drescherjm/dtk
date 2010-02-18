/* dtkVrScreen.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 21:10:30 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 23:21:00 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 72
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrScreen.h"

#include <dtkCore/dtkVec3.h>

class dtkVrScreenPrivate
{
public:
    dtkVec3 x;
    dtkVec3 y;

    dtkVec3 lowerLeft;
    dtkVec3 upperLeft;
    dtkVec3 lowerRight;
    dtkVec3 upperRight;

    double width;
    double height;
};

dtkVrScreen::dtkVrScreen(const dtkVec3& lowerLeft, const dtkVec3& lowerRight, const dtkVec3& upperLeft) : d(new dtkVrScreenPrivate)
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
    d->y = d->upperLeft - d->lowerLeft;

    d->x.normalize();
    d->y.normalize();

    d->width = d->x.length();
    d->height = d->y.length();

    d->upperRight = d->lowerRight + d->y*d->height;
}

void dtkVrScreen::uninitialize(void)
{

}

const dtkVec3& dtkVrScreen::lowerLeft(void) const
{
    return d->lowerLeft;
}

const dtkVec3& dtkVrScreen::upperLeft(void) const
{
    return d->upperLeft;
}

const dtkVec3& dtkVrScreen::lowerRight(void) const
{
    return d->lowerRight;
}

const dtkVec3& dtkVrScreen::upperRight(void) const
{
    return d->upperRight;
}

const dtkVec3& dtkVrScreen::up(void) const
{
    return d->y;
}

const dtkVec3& dtkVrScreen::right(void) const
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

const dtkVec3 dtkVrScreen::screens[5][3] = {
    { dtkVec3(-1.6, -0.8, -0.05), dtkVec3(-1.6, 2.4, -0.05), dtkVec3(-1.6, -0.8,  2.35)}, // left
    { dtkVec3(-1.6,  2.4, -0.05), dtkVec3( 1.6, 2.4, -0.05), dtkVec3(-1.6,  2.4,  2.35)}, // front
    { dtkVec3( 1.6,  2.4, -0.05), dtkVec3( 1.6,-0.8, -0.05), dtkVec3( 1.6,  2.4,  2.35)}, // right
    { dtkVec3(-1.6,  0.0, -0.05), dtkVec3( 1.6, 0.0, -0.05), dtkVec3(-1.6,  2.4, -0.05)}, // bottom
    { dtkVec3(-2.05, 1.5,  0.76), dtkVec3( 2.05, 1.5, 0.76), dtkVec3(-2.05, 1.5,  2.16)}  // wall
};
