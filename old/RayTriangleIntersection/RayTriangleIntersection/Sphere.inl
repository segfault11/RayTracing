//------------------------------------------------------------------------------
//
//  Sphere.cpp
//  FirstRayTracer
//
//  Created by Arno in Wolde Lübke on 10.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
template<typename REAL>
Sphere<REAL>::Sphere(
    const CGKVector3<REAL>& center,
    const REAL& radius,
    const CGKMatrix4<REAL>& transform,
    const CGKColor3<REAL>& color
)
: AObject<REAL>(transform, color), center(center), radius(radius)
{

}
//------------------------------------------------------------------------------
template<typename REAL>
Sphere<REAL>::~Sphere()
{

}
//------------------------------------------------------------------------------
template<typename REAL>
bool Sphere<REAL>::IsIntersectedByRay(REAL& t, const Ray<REAL>& ray) const
{
    CGKVector3<REAL> rayOrigin = this->worldToObject*ray.Origin;
    CGKVector3<REAL> rayDirection = this->worldToObject*ray.Direction;    
    rayDirection.Normalize();

    return CGKMathRaySphereIntersection(
        t,
        ray.Origin,
        ray.Direction,
        this->center,
        this->radius
    );
}
//------------------------------------------------------------------------------