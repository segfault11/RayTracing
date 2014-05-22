//------------------------------------------------------------------------------
//
//  Ray.inl
//  FirstRayTracer
//
//  Created by Arno in Wolde Lübke on 06.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
#include "Ray.h"
//------------------------------------------------------------------------------
template<typename REAL>
Ray<REAL>::Ray()
:
    Origin(CGK::Math::Vector3<REAL>(0.0, 0.0, 0.0)),
    Direction(CGK::Math::Vector3<REAL>(1.0, 0.0, 0.0))
{

}
//------------------------------------------------------------------------------
template<typename REAL>
Ray<REAL>::Ray(
    const CGK::Math::Vector3<REAL>& origin,
    const CGK::Math::Vector3<REAL>& direction
)
: Origin(origin), Direction(direction)
{

}
//------------------------------------------------------------------------------
template<typename REAL>
Ray<REAL>::~Ray()
{
}
//------------------------------------------------------------------------------
template<typename REAL>
CGK::Math::Vector3<REAL> Ray<REAL>::operator()(const REAL& t) const
{
    return this->Origin + this->Direction*t;
}
//------------------------------------------------------------------------------