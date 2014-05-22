//------------------------------------------------------------------------------
//
//  Ray.h
//  FirstRayTracer
//
//  Created by Arno in Wolde Lübke on 06.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
#ifndef __FirstRayTracer__Ray__
#define __FirstRayTracer__Ray__

#include <iostream>
#include <CGK/Math/Vector3.h>

template <typename REAL>
class Ray
{
public:
    Ray();
    Ray(const CGKVector3<REAL>& origin, const CGKVector3<REAL>& direction);
    ~Ray();
    
    CGKVector3<REAL> operator()(const REAL& t) const;
    CGKVector3<REAL> Origin;
    CGKVector3<REAL> Direction;
};

#include "Ray.inl"

#endif /* defined(__FirstRayTracer__Ray__) */
