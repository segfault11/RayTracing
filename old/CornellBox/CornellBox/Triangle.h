//
//  Triangle.h
//  RayTriangleIntersection
//
//  Created by Arno in Wolde Lübke on 13.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//

#ifndef __RayTriangleIntersection__Triangle__
#define __RayTriangleIntersection__Triangle__

#include <iostream>
#include "AObject.h"
#include "RayTriangleIntersection.h"

template<typename REAL>
class Triangle : public AObject<REAL>
{
public:
    Triangle(
        const CGK::Math::Vector3<REAL>& a,
        const CGK::Math::Vector3<REAL>& b,
        const CGK::Math::Vector3<REAL>& c,
        const CGK::Math::Matrix4<REAL>& transform,
        const CGK::Math::Color3<REAL>& color
    );
    
    ~Triangle();
    
    void TraceWithRay(const Ray<REAL>& ray) const;

private:
    CGK::Math::Vector3<REAL> a, b, c;
};

#include "Triangle.inl"

#endif /* defined(__RayTriangleIntersection__Triangle__) */
