#include "Object.h"
#include <string.h>
#include <stdio.h>
#include <Fxs/Obj/ObjFile2.h>
#include <Fxs/Obj/ObjMtlFile.h>
#include <stdlib.h>
#include <float.h>
#include <Fxs/Math/Intersections.h>

typedef struct Object Object;

struct Object {
    FxsObjFile2 *file;
	FxsObjMtlFilePtr mtlFile;
};

ObjectPtr ObjectCreate(const char *filename)
{
    Object *o = calloc(1, sizeof(Object));

    o->file = FxsObjFile2Create(filename);
    
    if (!o->file) {
        free(o);
        return NULL;
    }
    
	if (!strlen(o->file->mtlFilename)) {
	    return o;
	}

	o->mtlFile = FxsObjMtlFileCreateWithFile(o->file->mtlFilename);

	if (!o->mtlFile) {
		FxsObjFile2Destroy(&o->file);
	    free(o);
	}
	
    return o;
}


//void NodeIsIntersectedByRay(
//    const FxsObjFile2 *file,
//    int id,
//    int *isIntersected,
//    float *t,
//	ShadingRecord *sr, 
//	const Ray *ray
//    
//)
//{
//    const FxsObjFile2Face *f;
//    const FxsVector3 *v0, *v1, *v2;
//    int i;
//    float tl, u, v;
// 
//    for (i = 0; file->nodes[id].numFaces; i++) {
//        f = &file->faces[file->nodes[id].faceId + i];
//        v0 = &file->positions[f->p0];
//        v1 = &file->positions[f->p1];
//        v2 = &file->positions[f->p2];
//
//        FxsRayDoesIntersectTriangle(&ray->origin, &ray->direction,
//            &tl, &u, &v, v0, v1, v2);
//    }
//    
//
//}

/*
** Checks if a nodes faces are intersected by a ray. Fills out the shading 
** record according to the intersection if they were. Node the faces of 
** a node are not considered intersected if there already was an intersection 
** closer to the faces of the node.
*/ 
int FacesAreIntersectedByRay(
	const FxsObjFile2 *obj, 
	int faceId, 
	unsigned int numFaces, 
	float *t, 
	int  *hitFaceId,
	const Ray *ray
)
{
	int i = 0;
	const FxsObjFile2Face *face;
    const FxsVector3 *v0, *v1, *v2;
    float t0, u, v;
	int rv = 0;


	for (i = 0; i < numFaces; i++) {
	    face = &obj->faces[faceId + i];
		v0 = &obj->positions[face->p0];
		v1 = &obj->positions[face->p1];
		v2 = &obj->positions[face->p2];

        if (!FxsRayDoesIntersectTriangle(&ray->origin, 
			&ray->direction, &t0, &u, &v, v0, v1, v2)) {
			continue;
		}

        if (t0 < *t) {
            *t = t0;
			*hitFaceId = faceId + i;
			rv = 1; 
			/* Note: we report intersection only if this was the closest 
			** intersection so far 
			*/
        }
	}

	return rv;
}

int NodeIsIntersectedByRay(
	const FxsObjFile2 *obj, 
	int nodeId, 
	float *t, 
	int *hitNodeId, 
	int *hitFaceId,
	const Ray *ray
)
{
	int i = 0, rv = 0;

	if (FacesAreIntersectedByRay(obj, obj->nodes[nodeId].faceId, 
		obj->nodes[nodeId].numFaces, t, hitFaceId, ray)) {
	   	*hitNodeId = nodeId;  
		rv |= 1;
	}

	for (i = 0; i < obj->nodes[nodeId].numChilds; i++) {
		rv |= NodeIsIntersectedByRay(obj, obj->nodes[nodeId].childId + i, t,
				hitNodeId, hitFaceId, ray);
	}

	return rv;
}

int ObjectIsIntersectedByRay(
	ObjectPtr object,
    float *t,
	ShadingRecord *sr, 
	const Ray *ray
)
{
	int hitFaceId;
	int hitNodeId;
    int rv = 0;
    FxsObjMaterialPtr mat;

	*t = FLT_MAX;

	rv = NodeIsIntersectedByRay(object->file, 0, t, &hitNodeId, &hitFaceId, ray); 

	if (!rv) {
	    return rv;
	}

	if (strlen(object->file->nodes[hitNodeId].materialName)) {
		 
		mat = FxsObjMtlFileGetMaterialWithName(object->mtlFile, 
				object->file->nodes[hitNodeId].materialName);

		if (!mat) {
		    return rv;
		}

		if (FxsObjMaterialHasAttribute(mat, "Kd")) {
			sr->color[0] = FxsObjMaterialGetAttributeElementAsFloat(mat, "Kd", 0) * 255; 
			sr->color[1] = FxsObjMaterialGetAttributeElementAsFloat(mat, "Kd", 1) * 255; 
			sr->color[2] = FxsObjMaterialGetAttributeElementAsFloat(mat, "Kd", 2) * 255; 
		}

	}

	return rv;
}

void ObjectDestroy(ObjectPtr *object)
{
    if (!object || !(*object)) {
        return;
    }

    FxsObjFile2Destroy(&(*object)->file);
    free(*object);
    *object = NULL;
}
