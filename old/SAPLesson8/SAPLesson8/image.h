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

#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <cmath>
#include "utils.h"

#include <cassert>
#include <vector>

#include "vecmath.h"
#include "array.h"

// utility functions
namespace lrt {

template<typename T>
void savePPM(Array2<Vec3<T> > *arrayImg, const char *filename)
{
	std::ofstream ofs;
	ofs.open(filename);
	ofs << "P6\n" << arrayImg->dimension[0] << " " << arrayImg->dimension[1] << "\n255\n";
	for (uint32_t j = 0; j < arrayImg->dimension[1]; ++j) {
		for (uint32_t i = 0; i < arrayImg->dimension[0]; ++i) {
			Vec<unsigned char, 3> pixelChar;
			pixelChar[0] = (unsigned char)(std::min((*arrayImg)[j][i][0] * 255 + T(0.5), T(255)));
			pixelChar[1] = (unsigned char)(std::min((*arrayImg)[j][i][1] * 255 + T(0.5), T(255)));
			pixelChar[2] = (unsigned char)(std::min((*arrayImg)[j][i][2] * 255 + T(0.5), T(255)));
			ofs.write((char*)&pixelChar[0], 3);
		}
	}
	ofs.close();
}

} // end of lrt

#endif
