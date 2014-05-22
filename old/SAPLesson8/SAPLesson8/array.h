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

#ifndef ARRAY_H
#define ARRAY_H

namespace lrt {

// dimension
template<uint32_t D, class C>
class Array
{
public:
	Array(const Vec<size_t, D> &dim) : dimension(dim), arraySize(1)
	{
		for (uint32_t i = 0; i < D; ++i) arraySize *= dim[i]; 
		data = new C[arraySize];
	}
	virtual ~Array() { delete [] data; }
	void clear() { memset(this->data, 0x0, sizeof(C) * this->arraySize); }
	void set(const C &c) { for (uint32_t i = 0; i < arraySize; ++i) data[i] = c; }
	Vec<size_t, D> dimension;
	size_t arraySize;
	C *data;
};

template<class C>
C bilinearInterpolate1(
	const double &s, const double &t,
	const C &a, const C &b, const C &c, const C &d)
{
	C e = a * (1 - s) + b * s;
	C f = c * (1 - s) + d * s;
	return e * (1 - t) + f * t; 
}

// dimension
template<class C>
class Array2 : public Array<2, C> 
{
public:
	Array2(const Vec<size_t, 2> &dim) : Array<2, C>(dim) {}
	template<typename T> C interpolate(const T &s, const T &t) const
	{
		assert(s <= 1 && t <= 1); 
		double x = s * (this->dimension[0] - 1), y = t * (this->dimension[1] - 1);
		uint32_t xi = static_cast<uint32_t>(x), yi = static_cast<uint32_t>(y);
		double dx = x - xi, dy = y - yi;
		const C &a = (*this)[yi][xi];
		const C &b = (*this)[yi][std::min(xi + 1, this->dimension[0] - 1)];
		const C &c = (*this)[std::min(yi + 1, this->dimension[1] - 1)][xi];
		const C &d = (*this)[std::min(yi + 1, this->dimension[1] - 1)][std::min(xi + 1, this->dimension[0] - 1)];
		return bilinearInterpolate1<C>(dx, dy, a, b, c, d);
	}
	C* operator [] (size_t j) { return this->data + j * this->dimension[0]; }
	C* operator [] (size_t j) const { return this->data + j * this->dimension[0]; }
};

} // end namespace lrt

#endif
