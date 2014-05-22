/*
** @file Object.h
** @brief Declaration of the geometry to be rendered
**
** Declares an object structure to be used for rendering. The object structure
** can check if its geometry interesected by a ray. If a ray intersects the 
** object, the object fills out a shading record that represents the interesected 
** surface point. The shading record contains the intersection point, the 
** normal and the color for the point.
**
** The geometry for the point is a triangle mesh, that is stored in an .obj file.
** If the .obj file is accompanied by a .mtl file, which assigns materials to
** the .obj file's geometry, the diffuse color is used to represent the surface
** color. The geometry is simply stored as a list, no acceleration data 
** structure is used.
*/
#ifndef OBJECT_H
#define OBJECT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <Fxs/Math/Vector3.h>
#include "Ray.h"

/*
** The shading record, which contains data on how to shade a surface point. 
*/ 
typedef struct {
	FxsVector3 point;
	FxsVector3 normal;
	FxsVector3 color;
} ShadingRecord;

typedef struct Object* ObjectPtr;

/*
** Creates an object from an .obj file. Returns NULL if s.th. goes wrong.
*/ 
ObjectPtr ObjectCreate(const char *filename);

/*
** Checks if the object is intersected by a ray. Returns 0 if not. Returns 1
** and fills out "sr" otherwise.
*/ 
int ObjectIsIntersectedByRay(
	ObjectPtr object,
    float *t,
	ShadingRecord *sr, 
	const Ray *ray
);

/*
** Destroys the object.
*/ 
void ObjectDestroy(ObjectPtr *object);


#ifdef __cplusplus
}
#endif

#endif /* end of include guard: OBJECT_H */
