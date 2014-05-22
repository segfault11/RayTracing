/*
	LRT
	Copyright (C) 2012  www.scratchapixel.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VECMATH_H
#define VECMATH_H

#include <iostream>
#include <limits>
#include <stdint.h>
#include <string.h>
#include <cmath>

namespace lrt {

static const float kFloatMaximumValue = std::numeric_limits<float>::max();
static const float kInfinity = std::numeric_limits<float>::infinity();

template<typename T, uint32_t D>
class Vec
{
public:
	T vectors[D];
	typedef T SCALAR;
public:
	Vec() { memset(vectors, 0x0, sizeof(T) * D); }
	Vec(T xx) { for (uint32_t i = 0; i < D; ++i) vectors[i] = xx; }
	Vec(T *xx) { memset(vectors, xx, sizeof(T) * D); }
	Vec<T, D> operator * (const Vec<T, D> &v) const { Vec<T, D> w; for (uint32_t i = 0; i < D; ++i) w[i] = (*this)[i] * v[i]; return w; } 
	Vec<T, D> operator * (const T &s) const { Vec<T, D> w; for (uint32_t i = 0; i < D; ++i) w[i] = (*this)[i] * s; return w; }
	Vec<T, D> operator / (const T &s) const { Vec<T, D> w; for (uint32_t i = 0; i < D; ++i) w[i] = (*this)[i] / s; return w; }
	Vec<T, D> operator + (const Vec<T, D> &v) const { Vec<T, D> w; for (uint32_t i = 0; i < D; ++i) w[i] = (*this)[i] + v[i]; return w; } 
	Vec<T, D> operator - (const Vec<T, D> &v) const { Vec<T, D> w; for (uint32_t i = 0; i < D; ++i) w[i] = (*this)[i] - v[i]; return w; } 
	Vec<T, D> operator - () const { Vec<T, D> w; for (uint32_t i = 0; i < D; ++i) w[i] = -(*this)[i]; return w; } 
	Vec<T, D>& operator += (const Vec<T, D> &v) { for (uint32_t i = 0; i < D; ++i) (*this)[i] += v[i]; return *this; } 
	Vec<T, D>& operator *= (const T &s) { for (uint32_t i = 0; i < D; ++i) (*this)[i] *= s; return *this; } 
	T& operator [] (uint32_t i) { return vectors[i]; }
	T operator [] (uint32_t i) const { return vectors[i]; }
	T length2() const { T l2 = T(0); for (uint32_t i = 0; i < D; ++i) l2 += (*this)[i] * (*this)[i]; return l2; }
	T length() const { return sqrt( length2() ); }
	friend std::ostream & operator << (std::ostream &os, const Vec<T, D> &v)
	{ for (uint32_t i = 0; i < D; ++i) os << v[i] << " "; return os; }
	friend Vec<T, D> operator * (const T &s, const Vec<T, D> &v) { Vec<T, D> w; for (uint32_t i = 0; i < D; ++i) w[i] = v[i] * s; return w; }
	friend Vec<T, D> operator / (const T &s, const Vec<T, D> &v) { Vec<T, D> w; for (uint32_t i = 0; i < D; ++i) w[i] = s / v[i]; return w; } 
};

template<typename T, uint32_t D>
inline T distanceSquared(const Vec<T, D> &a, const Vec<T, D> &b) 
{ return (b - a).length2(); }

template<typename T, uint32_t D>
inline T dot(const Vec<T, D> &a, const Vec<T, D> &b) 
{ T s = T(0); for (uint32_t i = 0; i < D; ++i) s += a[i] * b[i]; return s; }

template<typename T, uint32_t D>
struct CompareVec
{
	CompareVec(uint32_t a) { axis = a; }
	uint32_t axis;
	bool operator() (const Vec<T, D> *a, const Vec<T, D> *b) const 
	{ return a->vectors[axis] < b->vectors[axis]; } 
};

template<typename T, uint32_t D>
inline void normalize(Vec<T, D> &v)
{ 
	T len = 0;
	for (uint32_t i = 0; i < D; ++i) len += v[i] * v[i];
	if (len > 0) {
		T invLen = T(1) / sqrt(len);
		for (uint32_t i = 0; i < D; ++i) v[i] *= invLen;
	}
}

template<typename T>
class Vec2 : public Vec<T, 2>
{
public:
	// http://stackoverflow.com/questions/8059629/c-template-class-inheritance-and-operators-use
	// The operator from class Vec will return an object of type Vec and not an object of type Vec2
	// The only solution around this is to allow a constructor that takes an instance of class Vec
	// and copy its content.
	Vec2() : Vec<T, 2>() {}
	Vec2(const Vec<T, 2> &v) { (*this)[0] = v[0], (*this)[1] = v[1]; }
	Vec2(T xx, T yy) { this->vectors[0] = xx, this->vectors[1] = yy; }
};

template<typename T>
class Vec3 : public Vec<T, 3>
{
public:
	// http://stackoverflow.com/questions/8059629/c-template-class-inheritance-and-operators-use
	// The operator from class Vec will return an object of type Vec and not an object of type Vec2
	// The only solution around this is to allow a constructor that takes an instance of class Vec
	// and copy its content.
	Vec3() { memset(this->vectors, 0x0, sizeof(T) * 3); }
	Vec3(const T &s) : Vec<T, 3>(s) {}
	Vec3(const Vec<T, 3> &v) { (*this)[0] = v[0], (*this)[1] = v[1]; (*this)[2] = v[2]; }
	Vec3(T xx, T yy, T zz) { (*this)[0] = xx, (*this)[1] = yy; (*this)[2] = zz; }
	//Vec3<T> cross(const Vec3<T> &v) const
	//{ 
	//	return Vec3<T>(
	//		(*this)[1] * v[2] - (*this)[2] * v[1],
	//		(*this)[2] * v[0] - (*this)[0] * v[2],
	//		(*this)[0] * v[1] - (*this)[1] * v[0]);
	//}
	Vec3<T>& normalize() { T len2 = this->length2(); if (len2 > 0) (*this) *= 1 / sqrt(len2); return *this; }
};

template<typename T>
Vec3<T> cross(const Vec3<T> &va, const Vec3<T> &vb)
{
	return Vec3<T>(
		va[1] * vb[2] - va[2] * vb[1],
		va[2] * vb[0] - va[0] * vb[2],
		va[0] * vb[1] - va[1] * vb[0]);
}

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec2<double> Vec2d;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

} // end of namespace lrt

#endif
