/* dtkQuat.cpp --- 
 * 
 * Author: Jean-Christophe Lombardo
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 11:32:57 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  2 17:56:45 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkQuat.h"

#ifdef WIN32
#define _USE_MATH_DEFINES
#endif

#define M_PI		3.14159265358979323846


#include <math.h>

double dtkQuat::Deg2Rad(double v)
{
    return v*M_PI/180.0;
}

double dtkQuat::Rad2Deg(double v)
{
    return v*180.0/M_PI;
}

dtkQuat::dtkQuat(double q0, double q1, double q2, double q3)
{
    mVal[0] = q0;
    mVal[1] = q1;
    mVal[2] = q2;
    mVal[3] = q3;
}

dtkQuat::dtkQuat(const dtkQuat &q)
{
    for(unsigned int i=0; i<4; ++i) mVal[i] = q.mVal[i];
}

dtkQuat::~dtkQuat()
{
}

void dtkQuat::hpr(double &h, double &p, double &r) const
{
    double q0 = mVal[3];
    double q1 = mVal[0];
    double q2 = mVal[1];
    double q3 = mVal[2];
    r = Rad2Deg(atan2(2*(q0*q1 + q2*q3), 1 - 2*(q1*q1 + q2*q2)));
    p = Rad2Deg(asin(2*(q0*q2-q3*q1)));
    h = Rad2Deg(atan2(2*(q0*q3 + q1*q2), 1 - 2*(q2*q2 + q3*q3)));
}

dtkQuat dtkQuat::fromHPR(double h, double p, double r)
{
    double  cosH, sinH, cosP, sinP, cosR, sinR;
    double  half_r, half_p, half_h;

    half_h = Deg2Rad(h / 2.0);
    half_p = Deg2Rad(p / 2.0);
    half_r = Deg2Rad(r / 2.0);

    cosH = cos(half_h);
    sinH = sin(half_h);

    cosP = cos(half_p);
    sinP = sin(half_p);

    cosR = cos(half_r);
    sinR = sin(half_r);

    return dtkQuat(
        sinR * cosP * cosH - cosR * sinP * sinH,
        cosR * sinP * cosH + sinR * cosP * sinH,
        cosR * cosP * sinH - sinR * sinP * cosH,
        cosR * cosP * cosH + sinR * sinP * sinH
        );
}

void dtkQuat::axeAngle(dtkVec3 &axis, double &angle) const
{
    angle = 2*Rad2Deg(acos(mVal[3]));
    axis.set(mVal[0], mVal[1], mVal[2]);
    axis.normalize();
}

dtkQuat dtkQuat::fromAxeAngle(dtkVec3 axe, double angle)
{
    double cosA = cos(Deg2Rad(angle)/2.0);
    double sinA = sin(Deg2Rad(angle)/2.0);
    axe.normalize();
    axe *= sinA;
    return dtkQuat(axe[0], axe[1], axe[2], cosA);
}
