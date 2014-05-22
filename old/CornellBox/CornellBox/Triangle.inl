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
        const CGK::Math::Vector3<REAL>& a,
        const CGK::Math::Vector3<REAL>& b,
        const CGK::Math::Vector3<REAL>& c,
        const CGK::Math::Matrix4<REAL>& transform,
        const CGK::Math::Color3<REAL>& color
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
void Triangle<REAL>::TraceWithRay(const Ray<REAL>& ray) const
{
    this->isHit = CGK::Math::RayTriangleIntersection(
            this->distance,
            ray.Origin,
            ray.Direction,
            this->a,
            this->b,
            this->c
        );
}
//------------------------------------------------------------------------------
