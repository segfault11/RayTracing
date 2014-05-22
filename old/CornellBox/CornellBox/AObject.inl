//------------------------------------------------------------------------------
//
//  AObject.inl
//  FirstRayTracer
//
//  Created by Arno in Wolde Lübke on 04.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
template<typename REAL>
AObject<REAL>::AObject(
    const CGK::Math::Matrix4<REAL>& objectToWorld,
    const CGK::Math::Color3<REAL>& color
)
: objectToWorld(objectToWorld), color(color), distance(-1.0), isHit(false)
{
    this->worldToObject = objectToWorld;
    this->worldToObject.Invert();
}
//------------------------------------------------------------------------------
template<typename REAL>
AObject<REAL>::~AObject()
{

}
//------------------------------------------------------------------------------