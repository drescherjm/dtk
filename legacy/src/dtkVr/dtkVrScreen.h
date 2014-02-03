/* dtkVrScreen.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 18:56:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 19:37:47 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 32
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRSCREEN_H
#define DTKVRSCREEN_H

#include "dtkVrExport.h"

#include <dtkMath/dtkVector3D.h>

#include <QtGui>

class dtkVrScreenPrivate;

class  DTKVR_EXPORT dtkVrScreen
{
public:
     dtkVrScreen(const dtkVector3D<double>& lowerLeft, const dtkVector3D<double>& lowerRight, const dtkVector3D<double>& upperLeft);
     dtkVrScreen(const dtkVrScreen& other);
    ~dtkVrScreen(void);

    void   initialize(void);
    void uninitialize(void);

    const dtkVector3D<double>& lowerLeft(void) const;
    const dtkVector3D<double>& upperLeft(void) const;
    const dtkVector3D<double>& lowerRight(void) const;
    const dtkVector3D<double>& upperRight(void) const;

    const dtkVector3D<double>& up(void) const;
    const dtkVector3D<double>& right(void) const;

    double width(void) const;
    double height(void) const;

    static const dtkVector3D<double> screens[5][3];

private:
    dtkVrScreenPrivate *d;
};

#endif
