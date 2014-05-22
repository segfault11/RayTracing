//------------------------------------------------------------------------------
//
//  Vec3.inl
//  CreatingPrimaryRays
//
//  Created by Arno in Wolde Lübke on 03.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
template<typename REAL>
Vec3<REAL>::Vec3()
: X(0), Y(0), Z(0)
{

}
//------------------------------------------------------------------------------
template<typename REAL>
void Vec3<REAL>::MakeZero()
{
    this->X = REAL(0);
    this->Y = REAL(0);
    this->Z = REAL(0);
}
//------------------------------------------------------------------------------
template<typename REAL>
Vec3<REAL>::~Vec3()
{

}
//------------------------------------------------------------------------------
template <typename REAL>
Vec3<REAL> Vec3<REAL>::operator+(const Vec3<REAL>& v) const
{
    Vec3<REAL> r;

    r.X = this->X + v.X;
    r.Y = this->Y + v.Y;
    r.Z = this->Z + v.Z;

    return r;
}
//------------------------------------------------------------------------------
template <typename REAL>
Vec3<REAL> Vec3<REAL>::operator-(const Vec3<REAL>& v) const
{
    Vec3<REAL> r;

    r.X = this->X - v.X;
    r.Y = this->Y - v.Y;
    r.Z = this->Z - v.Z;

    return r;
}
//------------------------------------------------------------------------------
template <typename REAL>
Vec3<REAL> Vec3<REAL>::operator*(const REAL& a) const
{
    Vec3<REAL> r;
    
    r.X = this->X*a;
    r.Y = this->Y*a;
    r.Z = this->Z*a;
    
    return r;
}
//------------------------------------------------------------------------------
template<typename REAL>
REAL Vec3<REAL>::GetNorm() const
{
    return std::sqrt<REAL>(this->X*this->X + this->Y*this->Y + this->Z*this->Z);
}
//------------------------------------------------------------------------------











