#include "Object.h"
#include <Fxs/Obj/ObjFile2.h>
#include <stdlib.h>
#include <float.h>
#include <Fxs/Math/Intersections.h>

typedef struct Object Object;

struct Object {
    FxsObjFile2 *file;
};

ObjectPtr ObjectCreate(const char *filename)
{
    Object *o = calloc(1, sizeof(Object));

    o->file = FxsObjFile2Create(filename);
    
    if (!o->file) {
        free(o);
        return NULL;
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

int ObjectIsIntersectedByRay(
	ObjectPtr object,
    float *t,
	ShadingRecord *sr, 
	const Ray *ray
)
{
    float tClosest = FLT_MAX;
    int i = 0;
    const FxsObjFile2Face *f;
    const FxsVector3 *v0, *v1, *v2;
    float t0, u, v;
    int fid = -1;
    
    for (i = 0; i < object->file->numFaces; i++) {
        f = &object->file->faces[i];
        v0 = &object->file->positions[f->p0];
        v1 = &object->file->positions[f->p1];
        v2 = &object->file->positions[f->p2];
        
        if (FxsRayDoesIntersectTriangle(&ray->origin, &ray->direction,
            &t0, &u, &v, v0, v1, v2)) {
            
            if (t0 < tClosest) {
                fid = i;
                tClosest = t0;
            }
            
        }
    }
    
    if (fid != -1) {
        *t = tClosest;
        return 1;
    } else {
        return 0;
    }
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