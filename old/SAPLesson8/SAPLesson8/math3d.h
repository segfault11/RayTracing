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

#ifndef MATH3D_H
#define MATH3D_H

template<typename T>
inline T radians(const T &angle) { return angle * T(M_PI) / T(180); }

template<typename T>
bool solveQuadratic(const T &a, const T &b, const T &c, T &x0, T &x1)
{
	T discr = b * b - 4 * a * c;
	if (discr <= 0) return false;
	//else if (discr == 0) x0 = x1 = - 0.5 * b / a;
	//else {
		T q = (b < 0) ? 
			-0.5 * (b - sqrt(discr)) :
			-0.5 * (b + sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	//}
	if (x0 > x1) std::swap(x0, x1);
	return true;
}

template<typename T>
inline T clamp(const T &a, const T &min, const T &max)
{
	if (a < min) return min;
	else if (a > max) return max; 
	else return a;
}

#endif
