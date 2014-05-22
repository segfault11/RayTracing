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
    const CGKMatrix4<REAL>& objectToWorld,
    const CGKColor3<REAL>& color
)
: objectToWorld(objectToWorld), color(color)
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