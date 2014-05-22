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

#ifndef MATRIX_H
#define MATRIX_H

#include "vecmath.h"

namespace lrt {

template<typename T>
class Matrix44
{
public:
	Matrix44()
	{
		m[0][0] = T(1.0);
		m[0][1] = T(0.0);
		m[0][2] = T(0.0);
		m[0][3] = T(0.0);
		m[1][0] = T(0.0);
		m[1][1] = T(1.0);
		m[1][2] = T(0.0);
		m[1][3] = T(0.0);
		m[2][0] = T(0.0);
		m[2][1] = T(0.0);
		m[2][2] = T(1.0);
		m[2][3] = T(0.0);
		m[3][0] = T(0.0);
		m[3][1] = T(0.0);
		m[3][2] = T(0.0);
		m[3][3] = T(1.0);
	}
	Matrix44(
		const T &c00, const T &c01, const T &c02, const T &c03,
		const T &c10, const T &c11, const T &c12, const T &c13,
		const T &c20, const T &c21, const T &c22, const T &c23,
		const T &c30, const T &c31, const T &c32, const T &c33)
	{
		m[0][0] = c00;
		m[0][1] = c01;
		m[0][2] = c02;
		m[0][3] = c03;
		m[1][0] = c10;
		m[1][1] = c11;
		m[1][2] = c12;
		m[1][3] = c13;
		m[2][0] = c20;
		m[2][1] = c21;
		m[2][2] = c22;
		m[2][3] = c23;
		m[3][0] = c30;
		m[3][1] = c31;
		m[3][2] = c32;
		m[3][3] = c33;
	}
	Matrix44(const T *coeffs) { memcpy(&m[0][0], coeffs, sizeof(T) * 16); }
	const T* operator [] (size_t i) const { return &m[i][0]; }
	T* operator [] (size_t i) { return &m[i][0]; }
	T m[4][4];
	static const Matrix44<T> Identity;
	// transform a point in homogeneous form (see OpenExr lib)
	template<typename S>
	void multVecMatrix(const Vec3<S> &src, Vec3<S> &dst) const
	{
		S x = src[0] * m[0][0] + src[1] * m[1][0] + src[2] * m[2][0] + m[3][0];
		S y = src[0] * m[0][1] + src[1] * m[1][1] + src[2] * m[2][1] + m[3][1];
		S z = src[0] * m[0][2] + src[1] * m[1][2] + src[2] * m[2][2] + m[3][2];
		S w = src[0] * m[0][3] + src[1] * m[1][3] + src[2] * m[2][3] + m[3][3];
		dst[0] = x / w;
		dst[1] = y / w;
		dst[2] = z / w;
	}
	// we are just interested in rotations. Use the 3x3 sub-matrix
	template<typename S>
	void multDirMatrix(const Vec3<S> &src, Vec3<S> &dst) const
	{
		dst[0] = src[0] * m[0][0] + src[1] * m[1][0] + src[2] * m[2][0];
		dst[1] = src[0] * m[0][1] + src[1] * m[1][1] + src[2] * m[2][1];
		dst[2] = src[0] * m[0][2] + src[1] * m[1][2] + src[2] * m[2][2];
	}
	friend std::ostream & operator << (std::ostream &os, const Matrix44<T> &m)
	{
		os << "[";
		os.precision(7);
		const T *c = &m[0][0];
		for (size_t i = 0; i < 16; ++i) {
			os << *(c++) << ((i==15) ? "]" : " ");
		}
		return os;
	}
	Matrix44 operator * (const Matrix44 &right) const
	{
		Matrix44 r;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				r.m[i][j] = 
					m[i][0] * right.m[0][j] +
					m[i][1] * right.m[1][j] +
					m[i][2] * right.m[2][j] +
					m[i][3] * right.m[3][j];
		return r;
	}
	Matrix44 inverse() const;
	Matrix44 transpose() const
	{
		Matrix44 t;
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				t[i][j] = m[j][i];
			}
		}
		return t;
	}
	static Matrix44<T> scale(const T &sx, const T &sy, const T &sz)
	{
		return Matrix44<T>(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
	}
	const Matrix44<T> & setTranslation(const Vec3<T> &t)
	{
		m[0][0] = 1;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;

		m[1][0] = 0;
		m[1][1] = 1;
		m[1][2] = 0;
		m[1][3] = 0;

		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = 1;
		m[2][3] = 0;

		m[3][0] = t[0];
		m[3][1] = t[1];
		m[3][2] = t[2];
		m[3][3] = 1;

		return *this;
	}
};

template<typename T>
const Matrix44<T> Matrix44<T>::Identity;

template<typename T>
Matrix44<T> Matrix44<T>::inverse() const
{
	int i, j, k;
	Matrix44<T> s;
	Matrix44<T> t (*this);

	// Forward elimination
	for (i = 0; i < 3 ; i++) {
		int pivot = i;

		T pivotsize = t[i][i];

		if (pivotsize < 0)
			pivotsize = -pivotsize;

		for (j = i + 1; j < 4; j++) {
			T tmp = t[j][i];

			if (tmp < 0)
				tmp = -tmp;

			if (tmp > pivotsize) {
				pivot = j;
				pivotsize = tmp;
			}
		}

		if (pivotsize == 0) {
			//if (singExc)
			//	throw ::Imath::SingMatrixExc ("Cannot invert singular matrix.");

			return Matrix44();
		}

		if (pivot != i) {
			for (j = 0; j < 4; j++) {
				T tmp;

				tmp = t[i][j];
				t[i][j] = t[pivot][j];
				t[pivot][j] = tmp;

				tmp = s[i][j];
				s[i][j] = s[pivot][j];
				s[pivot][j] = tmp;
			}
		}

		for (j = i + 1; j < 4; j++) {
			T f = t[j][i] / t[i][i];

			for (k = 0; k < 4; k++) {
				t[j][k] -= f * t[i][k];
				s[j][k] -= f * s[i][k];
			}
		}
	}

	// Backward substitution
	for (i = 3; i >= 0; --i) {
		T f;

		if ((f = t[i][i]) == 0) {
			//if (singExc)
			//	throw ::Imath::SingMatrixExc ("Cannot invert singular matrix.");

			return Matrix44();
		}

		for (j = 0; j < 4; j++) {
			t[i][j] /= f;
			s[i][j] /= f;
		}

		for (j = 0; j < i; j++) {
			f = t[j][i];

			for (k = 0; k < 4; k++) {
				t[j][k] -= f * t[i][k];
				s[j][k] -= f * s[i][k];
			}
		}
	}

	return s;
}

typedef Matrix44<float> Matrix44f;

} // end namespace lrt

#endif
