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

#include "ray.h"
#include "utils.h"
#include "array.h"
#include "matrix.h"
#include "math3d.h"
#include "image.h"

#include <vector>
#include <cstdlib>

using namespace lrt;

struct Spectrum
{
public:
	Spectrum() {}
	void convertToRgb(Vec3f &rgb) { rgb = xyz; }
	Vec3f xyz;
};

class Object
{
public:
	Object(const Matrix44f &o2w) : objectToWorld(o2w)
	{
		worldToObject = objectToWorld.inverse();
		std::cerr << objectToWorld << "\n" << worldToObject << std::endl;
		color = Vec3f(drand48(), drand48(), drand48());
	}
	virtual ~Object() {}
	virtual bool intersect(const Ray<float> &r, float &t) const = 0;
	Matrix44f objectToWorld, worldToObject;
	Vec3f color;
};

class Sphere : public Object
{
public:
	Sphere(const Matrix44f &o2w = Matrix44f::Identity, float r = 1) : 
		Object(o2w), radius(r), radius2(r * r) 
	{}
	bool intersect(const Ray<float> &r, float &t) const
	{
		Vec3f rorig, rdir;
		this->worldToObject.multVecMatrix(r.orig, rorig);
		this->worldToObject.multDirMatrix(r.dir, rdir);
        rdir.normalize();
		float a = dot(rdir, rdir);
		float b = 2 * dot(rdir, rorig);
		float c = dot(rorig, rorig) - radius2;
		float t0, t1;
		if (!solveQuadratic(a, b, c, t0, t1) || t1 < 0) return false;
		if (t1 < t0) std::swap(t0, t1);
		t = (t0 < 0) ? t1 : t0; 
		return true;
	}
	float radius, radius2;
};

class Camera
{
public:
	Camera() { set(); }
	void set(
		const Matrix44f &c2w = Matrix44f::Identity, 
		const float &f = 90, 
		const float &ncp = 0.1, 
		const float &fcp = 1000)
	{
		nearClippingPlane = ncp;
		farClippingPlane = fcp;
		fov = f;
		cameraToWorld = c2w;
		worldToCamera = cameraToWorld.inverse();
		angle = atan(degtorad(fov * 0.5));
	}
	float nearClippingPlane, farClippingPlane;
	float fov;
	float angle;
	Matrix44f cameraToWorld, worldToCamera;
};

class RenderContext
{
public:
	RenderContext()
	{
		imageWidth = 640;
		imageHeight = 480;
		imageAspectRatio = imageWidth / (float)imageHeight;
		backgroundColor = Vec3f(0.498, 0.616, 0.780);
	}
	~RenderContext()
	{
		while (!objects.empty()) {
			Object *obj = objects.back();
			objects.pop_back();
			delete obj;
		}
	}
	Camera camera;
	size_t imageWidth, imageHeight;
	float imageAspectRatio;
	Array2<Vec3f> *image;
	std::vector<Object *> objects;
	Vec3f backgroundColor;
};

template<typename T>
void trace(const Ray<T> ray, const RenderContext *rc, Spectrum &s)
{
	float tClosest = ray.tmax;
	Vec3f objectColor;
	Object *hitObject = NULL;
	for (size_t i = 0; i < rc->objects.size(); ++i) {
		float t;
		if (rc->objects[i]->intersect(ray, t)) {
			if (t < tClosest && t > ray.tmin) { 
				tClosest = t; 
				hitObject = rc->objects[i];
				objectColor = rc->objects[i]->color;
			}
		}
	}
	// an other choice is: if (hitObject != NULL)
	s.xyz = (tClosest < ray.tmax) ? objectColor : rc->backgroundColor;
}

void render(const RenderContext *rc)
{
	Array2<Vec3f> *image = new Array2<Vec3f>(Vec2<size_t>(rc->imageWidth, rc->imageHeight));
	Vec3f *pixel = image[0][0];
	Vec3f rayOrigin;
	rc->camera.cameraToWorld.multVecMatrix(Vec3f(0), rayOrigin);
	for (uint32_t j = 0; j < rc->imageHeight; ++j) {
		for (uint32_t i = 0; i < rc->imageWidth; ++i) {
			float x = (2 * ((i + 0.5) / rc->imageWidth) - 1) * rc->imageAspectRatio * rc->camera.angle;
			float y = (1 - 2 *((j + 0.5) / rc->imageHeight)) * rc->camera.angle;
			//Vec3f rayDirection;
			//rc->camera.cameraToWorld.multDirMatrix(Vec3f(x, y, -1), rayDirection);
			Vec3f cameraPos;
			rc->camera.cameraToWorld.multVecMatrix(Vec3f(x, y, -1), cameraPos);
			Vec3f rayDirection = cameraPos - rayOrigin;
			normalize(rayDirection); 
			Ray<float> ray(rayOrigin, rayDirection, rc->camera.nearClippingPlane, rc->camera.farClippingPlane);
			Spectrum rayColor;
			trace<float>(ray, rc, rayColor);
			rayColor.convertToRgb(*pixel);
			++pixel;
		}
	}
	savePPM(image, "./untitled.ppm");
	delete image;
}

int main(int argc, char **argv)
{
	srand48(168);
	RenderContext *rc = new RenderContext;
	Matrix44f o2w; 
	o2w.setTranslation(Vec3f(2, 2, -5));
	rc->objects.push_back(new Sphere(o2w));
	o2w.setTranslation(Vec3f(1, 1, -6));
	o2w[0][0] = 1.2;
	o2w[1][1] = 1.2;
	o2w[2][2] = 1.2;
	rc->objects.push_back(new Sphere(o2w));
	Matrix44f c2w;
	c2w.setTranslation(Vec3f(0, 0, 5));
	rc->camera.set(c2w, 30);
	render(rc);
	delete rc;
	return 0;
}
