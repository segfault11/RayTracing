//------------------------------------------------------------------------------
//
//  Triangle.cpp
//  RayTriangleIntersection
//
//  Created by Arno in Wolde Lübke on 13.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
template<typename REAL>
Triangle<REAL>::Triangle(
        const CGKVector3<REAL>& a,
        const CGKVector3<REAL>& b,
        const CGKVector3<REAL>& c,
        const CGKMatrix4<REAL>& transform,
        const CGKColor3<REAL>& color
)
: AObject<REAL>(transform, color), a(a), b(b), c(c)
{

}
//--;---------------------------------------------------------------------------
template<typename REAL>
Triangle<REAL>::~Triangle()
{

}
//------------------------------------------------------------------------------
template<typename REAL>
bool Triangle<REAL>::IsIntersectedByRay(REAL& t, const Ray<REAL>& ray) const
{
    CGKVector3<REAL> rayOrigin = this->worldToObject*ray.Origin;
    CGKVector3<REAL> rayDirection = this->worldToObject*ray.Direction;    
    rayDirection.Normalize();

    return CGKMathRayTriangleIntersection(
        t,
        rayOrigin,
        ray.Direction,
        this->a,
        this->b,
        this->c
    );
}
//------------------------------------------------------------------------------
