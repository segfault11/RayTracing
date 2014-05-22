//------------------------------------------------------------------------------
//
//  Sphere.h
//  FirstRayTracer
//
//  Created by Arno in Wolde Lübke on 10.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
#ifndef __FirstRayTracer__Sphere__
#define __FirstRayTracer__Sphere__

#include <iostream>
#include "AObject.h"
#include <CGK/Math/RaySphereIntersection.h>

template<typename REAL>
class Sphere : public AObject<REAL>
{
public:
    Sphere(
        const CGKVector3<REAL>& center,
        const REAL& radius,
        const CGKMatrix4<REAL>& transform,
        const CGKColor3<REAL>& color
    );
    
    ~Sphere();
    
    bool IsIntersectedByRay(REAL& t, const Ray<REAL>& ray) const;
    
private:
    CGKVector3<REAL> center;
    REAL radius;
};

#include "Sphere.inl"

#endif /* defined(__FirstRayTracer__Sphere__) */
