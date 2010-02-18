/* dtkVrScreen.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 18:56:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 23:20:29 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 26
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

class dtkVec3;
class dtkVrScreenPrivate;

class dtkVrScreen
{
public:
     dtkVrScreen(const dtkVec3& lowerLeft, const dtkVec3& lowerRight, const dtkVec3& upperLeft);
     dtkVrScreen(const dtkVrScreen& other);
    ~dtkVrScreen(void);

    void   initialize(void);
    void uninitialize(void);

    const dtkVec3& lowerLeft(void) const;
    const dtkVec3& upperLeft(void) const;
    const dtkVec3& lowerRight(void) const;
    const dtkVec3& upperRight(void) const;

    const dtkVec3& up(void) const;
    const dtkVec3& right(void) const;

    double width(void) const;
    double height(void) const;

    static const dtkVec3 screens[5][3];

private:
    dtkVrScreenPrivate *d;
};

#endif
