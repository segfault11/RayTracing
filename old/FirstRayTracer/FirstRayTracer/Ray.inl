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
    Origin(CGKVector3<REAL>(0.0, 0.0, 0.0)),
    Direction(CGKVector3<REAL>(1.0, 0.0, 0.0))
{

}
//------------------------------------------------------------------------------
template<typename REAL>
Ray<REAL>::Ray(
    const CGKVector3<REAL>& origin,
    const CGKVector3<REAL>& direction
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
CGKVector3<REAL> Ray<REAL>::operator()(const REAL& t) const
{
    return this->Origin + this->Direction*t;
}
//------------------------------------------------------------------------------