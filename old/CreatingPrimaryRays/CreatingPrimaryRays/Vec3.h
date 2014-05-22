//------------------------------------------------------------------------------
//
//  Vec3.h
//  CreatingPrimaryRays
//
//  Created by Arno in Wolde Lübke on 03.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef __CreatingPrimaryRays__Vec3__
#define __CreatingPrimaryRays__Vec3__

#include <iostream>

template<typename REAL>
class Vec3
{
public:
    Vec3();
    Vec3(const REAL& x, const REAL& y, const REAL& z);
    ~Vec3();
    
    void MakeZero();
    Vec3 operator+(const Vec3<REAL>& v) const;
    Vec3 operator-(const Vec3<REAL>& v) const;
    
    Vec3 operator*(const REAL& a) const;

    REAL GetNorm() const;
    

    REAL X, Y, Z;
};

#include "Vec3.inl"

typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

#endif /* defined(__CreatingPrimaryRays__Vec3__) */
