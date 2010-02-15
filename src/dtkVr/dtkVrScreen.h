/* dtkVrScreen.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 18:56:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 12 21:37:23 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRSCREEN_H
#define DTKVRSCREEN_H

#include <QtGui>

class dtkVrScreenPrivate;

class dtkVrScreen
{
public:
     dtkVrScreen(const QVector3D& lowerLeft, const QVector3D& lowerRight, const QVector3D& upperLeft);
     dtkVrScreen(const dtkVrScreen& other);
    ~dtkVrScreen(void);

    void   initialize(void);
    void uninitialize(void);

    const QVector3D& lowerLeft(void) const;
    const QVector3D& upperLeft(void) const;
    const QVector3D& lowerRight(void) const;
    const QVector3D& upperRight(void) const;

    const QVector3D& up(void) const;
    const QVector3D& right(void) const;

    double width(void) const;
    double height(void) const;

    static const QVector3D screens[5][3];

private:
    dtkVrScreenPrivate *d;
};

#endif
