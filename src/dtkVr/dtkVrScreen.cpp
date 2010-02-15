/* dtkVrScreen.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 21:10:30 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 12 21:43:36 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 70
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
    QVector3D x;
    QVector3D y;

    QVector3D lowerLeft;
    QVector3D upperLeft;
    QVector3D lowerRight;
    QVector3D upperRight;

    double width;
    double height;
};

dtkVrScreen::dtkVrScreen(const QVector3D& lowerLeft, const QVector3D& lowerRight, const QVector3D& upperLeft) : d(new dtkVrScreenPrivate)
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

const QVector3D& dtkVrScreen::lowerLeft(void) const
{
    return d->lowerLeft;
}

const QVector3D& dtkVrScreen::upperLeft(void) const
{
    return d->upperLeft;
}

const QVector3D& dtkVrScreen::lowerRight(void) const
{
    return d->lowerRight;
}

const QVector3D& dtkVrScreen::upperRight(void) const
{
    return d->upperRight;
}

const QVector3D& dtkVrScreen::up(void) const
{
    return d->y;
}

const QVector3D& dtkVrScreen::right(void) const
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

const QVector3D dtkVrScreen::screens[5][3] = {
    { QVector3D(-1.6, -0.8, -0.05), QVector3D(-1.6, 2.4, -0.05), QVector3D(-1.6, -0.8,  2.35)}, // left
    { QVector3D(-1.6,  2.4, -0.05), QVector3D( 1.6, 2.4, -0.05), QVector3D(-1.6,  2.4,  2.35)}, // front
    { QVector3D( 1.6,  2.4, -0.05), QVector3D( 1.6,-0.8, -0.05), QVector3D( 1.6,  2.4,  2.35)}, // right
    { QVector3D(-1.6,  0.0, -0.05), QVector3D( 1.6, 0.0, -0.05), QVector3D(-1.6,  2.4, -0.05)}, // bottom
    { QVector3D(-2.05, 1.5,  0.76), QVector3D( 2.05, 1.5, 0.76), QVector3D(-2.05, 1.5,  2.16)}  // wall
};
