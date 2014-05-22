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
#include <CGK/Math/RayTriangleIntersection.h>

template<typename REAL>
class Triangle : public AObject<REAL>
{
public:
    Triangle(
        const CGKVector3<REAL>& a,
        const CGKVector3<REAL>& b,
        const CGKVector3<REAL>& c,
        const CGKMatrix4<REAL>& transform,
        const CGKColor3<REAL>& color
    );
    
    ~Triangle();
    
    bool IsIntersectedByRay(REAL& t, const Ray<REAL>& ray) const;
    
private:
    CGKVector3<REAL> a, b, c;
};

#include "Triangle.inl"

#endif /* defined(__RayTriangleIntersection__Triangle__) */
