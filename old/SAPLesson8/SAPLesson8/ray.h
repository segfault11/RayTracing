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

#ifndef RAY_H
#define RAY_H

#include "vecmath.h"

namespace lrt {

template<typename T>
class IsectInfo
{
public:
	IsectInfo() {}
	Vec3<T> P, N;
	Vec3<T> dPdu, dPdv;
	T s, t;
	Vec3<T> worldToLocal(const Vec3<T> &v) { 
		Vec3<T> sn(dPdu); 
		sn.normalize(); 
		Vec3<T> tn = N.cross(sn); 
		return Vec3<T>(dot(v, sn), dot(v, tn), dot(v, N));
	}
};

enum RayType
{
	kUnknownRay = 0,
	kCameraRay,
	kShadowRay,
};

template<typename T>
class Ray
{
public:
	Vec3<T> orig, dir;		/// ray orig and dir
	mutable T tmin, tmax;	/// ray min and max distances
	unsigned triangleId;	/// used with triangle mesh (id of the intersected triangle)
	Vec3<T> invdir; 		/// precomputed for ray-box intersection
	int sign[3];			/// precomputed for ray-box intersection
	RayType type;			/// ray type
	Ray(Vec3<T> orig, Vec3<T> dir, T near = T(0), T far = std::numeric_limits<T>::max(), RayType rt = kUnknownRay) : 
		orig(orig), dir(dir), tmin(near), tmax(far), type(rt)
	{
		invdir = T(1) / dir;
		sign[0] = (invdir[0] < 0);
		sign[1] = (invdir[1] < 0);
		sign[2] = (invdir[2] < 0);
	}
	Vec3<T> operator () (const T &t) const
	{ return orig + dir * t; }
};

}

#endif
