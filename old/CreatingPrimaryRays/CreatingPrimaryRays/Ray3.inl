//------------------------------------------------------------------------------
//
//  Ray3.inl
//  CreatingPrimaryRays
//
//  Created by Arno in Wolde Lübke on 03.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
template<typename REAL>
Vec3<REAL>::Vec3(const REAL& x, const REAL& y, const REAL& z)
: X(x), Y(y), Z(z)
{
    
}
//------------------------------------------------------------------------------
template<typename REAL>
Ray3<REAL>::Ray3()
{
    this->Origin.MakeZero();
    this->Direction.MakeZero();
}
//------------------------------------------------------------------------------
template<typename REAL>
Ray3<REAL>::Ray3(const Vec3<REAL>& origin, const Vec3<REAL>& direction)
: Origin(origin), Direction(direction)
{

}
//------------------------------------------------------------------------------
template<typename REAL>
Ray3<REAL>::~Ray3()
{

}
//------------------------------------------------------------------------------
template<typename REAL>
Vec3<REAL> Ray3<REAL>::operator()(const REAL& t) const
{
    return this->Origin + this->Direction*t;
}
//------------------------------------------------------------------------------