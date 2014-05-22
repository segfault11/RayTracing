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
#include "Matrix4.h"
#include "Vector3.h"
#include "Ray.h"

template<typename REAL>
class AObject
{
public:
    AObject(const CGK::Math::Matrix4<REAL>& objectToWorld, const CGK::Math::Color3<REAL>& color);
    ~AObject();
    
    virtual void TraceWithRay(const Ray<REAL>& ray) const = 0;
    
    bool IsHit() const {return this->isHit;}
    REAL GetDistance() const {return this->distance;}
    const CGK::Math::Color3<REAL>& GetColor() const {return this->color;}

    const CGK::Math::Matrix4<REAL>& GetObjectToWorld() const {return objectToWorld;}
    const CGK::Math::Matrix4<REAL>& GetWorldToObject() const {return worldToObject;}


protected:
    CGK::Math::Matrix4<REAL> objectToWorld;
    CGK::Math::Matrix4<REAL> worldToObject;

    mutable bool isHit;
    mutable REAL distance;
    mutable CGK::Math::Color3<REAL> color;
};

#include "AObject.inl"

#endif /* defined(__FirstRayTracer__IObject__) */
