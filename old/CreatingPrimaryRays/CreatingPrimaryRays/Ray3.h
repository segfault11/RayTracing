//
//  Ray3.h
//  CreatingPrimaryRays
//
//  Created by Arno in Wolde Lübke on 03.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//

#ifndef __CreatingPrimaryRays__Ray3__
#define __CreatingPrimaryRays__Ray3__

#include <iostream>
#include "Vec3.h"

template <typename REAL>
class Ray3
{
public:
    Ray3();
    Ray3(const Vec3<REAL>& origin, const Vec3<REAL>& direction);
    ~Ray3();
    
    Vec3<REAL> operator()(const REAL& t) const;
    
    Vec3<REAL> Origin;
    Vec3<REAL> Direction;
};

#include "Ray3.inl"

typedef Ray3<float> Ray3f;
typedef Ray3<double> Ray3d;

#endif /* defined(__CreatingPrimaryRays__Ray3__) */
