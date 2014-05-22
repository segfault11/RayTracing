//------------------------------------------------------------------------------
//
//  AObject.h
//  FirstRayTracer
//
//  Created by Arno in Wolde Lübke on 04.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
#ifndef __FirstRayTracer__AObject__
#define __FirstRayTracer__AObject__

#include <iostream>
#include <CGK/Math/Matrix4.h>
#include <CGK/Math/Vector3.h>
#include "Ray.h"

template<typename REAL>
class AObject
{
public:
    AObject(const CGKMatrix4<REAL>& objectToWorld, const CGKColor3<REAL>& color);
    ~AObject();
    
    virtual bool IsIntersectedByRay(
        REAL& t,
        const Ray<REAL>& ray
    ) const = 0;
    
    const CGKColor3<REAL>& GetColor() const {return this->color;}

protected:
    CGKMatrix4<REAL> objectToWorld;
    CGKMatrix4<REAL> worldToObject;
    CGKVector3<REAL> color;
};

#include "AObject.inl"

#endif /* defined(__FirstRayTracer__IObject__) */
