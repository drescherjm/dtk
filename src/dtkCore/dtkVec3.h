/* dtkVec3.h --- 
 * 
 * Author: Jean-Christophe Lombardo
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 11:28:59 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 12:26:49 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVEC3_H
#define DTKVEC3_H

#include <math.h>
#include <iostream>

class dtkVec3
{
public:
    dtkVec3(double x=0.0, double y=0.0, double z=0.0)
    {
        mVal[0] = x;
        mVal[1] = y;
        mVal[2] = z;
    }

    dtkVec3(const dtkVec3 &v)
    {
        for (unsigned int i=0; i<3; ++i) mVal[i] = v.mVal[i];
    }

    ~dtkVec3() {}

    inline double x() const { return mVal[0]; }
    inline double y() const { return mVal[1]; }
    inline double z() const { return mVal[2]; }

    inline void set(double x, double y, double z)
    {
        mVal[0] = x;
        mVal[1] = y;
        mVal[2] = z;
    }
    inline void setX(double v) { mVal[0] = v; }
    inline void setY(double v) { mVal[1] = v; }
    inline void setZ(double v) { mVal[2] = v; }

    inline double& operator[](int i) { return mVal[i]; }
    inline double operator[](int i) const { return mVal[i]; }

    inline const double* values() const { return mVal; }
    unsigned int nbValues() const {return 3;}
    inline double* values() { return mVal; }

    inline double length(void) const { return sqrt(*this * *this); }
    inline double normalize(void) { double l = length(); *this /= l; return l; }

    inline bool operator==(const dtkVec3 &v) const {
        return (mVal[0]==v[0]) && (mVal[1]==v[1]) &&(mVal[2]==v[2]);
    }

    inline bool operator!=(const dtkVec3 &v) const {
        return (mVal[0]!=v[0]) || (mVal[1]!=v[1]) ||(mVal[2]!=v[2]);
    }

    inline dtkVec3 operator*(double v) const { return dtkVec3(mVal[0]*v, mVal[1]*v, mVal[2]*v); }
    inline dtkVec3 operator/(double v) const { return dtkVec3(mVal[0]/v, mVal[1]/v, mVal[2]/v); }

    inline dtkVec3 &operator*=(double v)
    {
        for (unsigned int i=0; i<3; ++i) mVal[i] *= v;
        return *this;
    }

    inline dtkVec3 &operator/=(double v)
    {
        for (unsigned int i=0; i<3; ++i) mVal[i] /= v;
        return *this;
    }

    inline double operator*(const dtkVec3 &v) const
    {
        return ((mVal[0]*v.mVal[0]) + (mVal[1]*v.mVal[1]) + (mVal[2]*v.mVal[2])); 
    }

    inline const dtkVec3 operator-(void) const
    {
        return dtkVec3(-mVal[0], -mVal[1], -mVal[2]); 
    }

    inline const dtkVec3 operator-(const dtkVec3 &v) const
    {
        return dtkVec3(mVal[0] - v.mVal[0], mVal[1] - v.mVal[1], mVal[2] - v.mVal[2]); 
    }

    inline const dtkVec3 operator+(const dtkVec3 &v) const
    {
        return dtkVec3(mVal[0] + v.mVal[0], mVal[1] + v.mVal[1], mVal[2] + v.mVal[2]); 
    }

private:
    double mVal[3];
};

inline std::ostream &operator<<(std::ostream &out, const dtkVec3 &v)
{
    out<<v[0]<<" "<<v[1]<<" "<<v[2];
    return out;
}

inline std::istream &operator>>(std::istream &in, dtkVec3 &v)
{
    in>>v[0]>>v[1]>>v[2];
    return in;
}

#endif
