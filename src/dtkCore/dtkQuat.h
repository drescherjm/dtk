/* dtkQuat.h --- 
 * 
 * Author: Jean-Christophe Lombardo
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 11:30:32 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 25 11:21:44 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 26
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKQUAT_H
#define DTKQUAT_H

#include "dtkCoreExport.h"
#include "dtkVec3.h"

class DTKCORE_EXPORT dtkQuat
{
public:
     dtkQuat(double q0=0.0, double q1=0.0, double q2=0.0, double q3=1.0);
     dtkQuat(const dtkQuat &q);
    ~dtkQuat(void);

    inline double  operator[](int i) const { return mVal[i]; }
    inline double &operator[](int i) { return mVal[i]; }

    inline bool operator==(const dtkQuat &q) const
    {
        return (mVal[0]==q[0]) && (mVal[1]==q[1]) && (mVal[2]==q[2]) && (mVal[3]==q[3]);
    }

    inline bool operator!=(const dtkQuat &q) const
    {
        return (mVal[0]!=q[0]) || (mVal[1]!=q[1]) ||(mVal[2]!=q[2]) || (mVal[3]!=q[3]);
    }

    inline dtkQuat operator+(const dtkQuat &q) const
    {
        return dtkQuat (mVal[0]+q.mVal[0], mVal[1]+q.mVal[1], mVal[2]+q.mVal[2], mVal[3]+q.mVal[3]);
    }

    inline dtkQuat operator*(double v) const
    {
        return dtkQuat (mVal[0]*v, mVal[1]*v, mVal[2]*v, mVal[3]*v);
    }

    inline dtkQuat operator*(const dtkQuat &q) const
    {
        return dtkQuat(
              mVal[0]*q[3] + mVal[1]*q[2] - mVal[2]*q[1] + mVal[3]*q[0],
            - mVal[0]*q[2] + mVal[1]*q[3] + mVal[2]*q[0] + mVal[3]*q[1],
              mVal[0]*q[1] - mVal[1]*q[0] + mVal[2]*q[3] + mVal[3]*q[2],
            - mVal[0]*q[0] - mVal[1]*q[1] - mVal[2]*q[2] + mVal[3]*q[3]
            );
    }

    inline dtkQuat conj(void) const
    {
        return dtkQuat(-mVal[0], -mVal[1], -mVal[2],  mVal[3]);
    }

    inline double length2(void) const
    {
        return (mVal[0]*mVal[0] + mVal[1]*mVal[1] + mVal[2]*mVal[2] + mVal[3]*mVal[3]);
    }

    inline double length(void) const
    {
        return sqrt(length2());
    }

    inline dtkQuat inv(void) const
    {
        return conj()*(1.0/((*this)*conj()).length2());
    }

    inline dtkVec3 rotate(const dtkVec3 &v) const
    {
        // dtkQuat q((*this)*dtkQuat(v.x(), v.y(), v.z(), 0)*((*this).inv()));
        dtkQuat q(((*this).inv())*dtkQuat(v.x(), v.y(), v.z(), 0)*((*this)));

        return dtkVec3(q[0], q[1], q[2]);
    }

    inline dtkQuat exp(double v) const
    {
        dtkVec3 axe;
        double angle;
        axeAngle(axe, angle);
        return fromAxeAngle(axe, v*angle);
    }

    void hpr(double &h, double &p, double &r) const;

    void axeAngle(dtkVec3 &axe, double &angle) const;

    inline const double *values(void) const
    {
        return mVal;
    }

    inline double *values(void)
    {
        return mVal;
    }
    
    inline unsigned int nbValues(void) const {
        return 4;
    }

    static dtkQuat fromHPR(double h, double p, double r);

    static dtkQuat fromAxeAngle(dtkVec3 axe, double angle);

    static dtkQuat slerp(const dtkQuat q0, const dtkQuat q1, double alpha)
    {
        return (q0*(q0.inv()*q1).exp(alpha));
    }

    static double Deg2Rad(double v);
    static double Rad2Deg(double v);

private:
    double mVal[4];
};

inline std::ostream &operator<<(std::ostream &out, const dtkQuat &q)
{
    out<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3];
    return out;
}

inline std::istream &operator>>(std::istream &in, dtkQuat &q)
{
    in>>q[0]>>q[1]>>q[2]>>q[3];
    return in;
}

inline QDebug operator<<(QDebug debug, const dtkQuat& data)
{
    debug.nospace() << data[0] << " " << data[1] << " " << data[2] << " " << data[3];

    return debug.space();
}

inline QDebug operator<<(QDebug debug, dtkQuat *data)
{
    debug.nospace() << data[0] << " " << data[1] << " " << data[2] << " " << data[3];

    return debug.space();
}

#endif
