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


/*
** Interpolates a vec3 quantity for a point within a triangle. 
** NOTE: when interpolating normals, they might have to be interpolated afterwards.
** @see http://www.flipcode.com/archives/Interpolating_Normals_For_Ray-Tracing.shtml
*/ 
void TriangleInterpolateVector3(
	const FxsVector3 *tp0,
	const FxsVector3 *tp1, 
	const FxsVector3 *tp2,
	const FxsVector3 *ta0,
	const FxsVector3 *ta1,
	const FxsVector3 *ta2,
	FxsVector3 *taout,
	const FxsVector3 *p
)
{
	float d0, d1, d2;	
	const FxsVector3 *pa, *pb, *pc;
	const FxsVector3 *aa, *ab, *ac;
	FxsVector3 nplane, ntmp, dca, dcb;
	float dplane;
	FxsVector3 dirray;
	float t;
	FxsVector3 q, aq, qa, qp;
	float bclen, bqlen, qplen, qalen;
	float alpha, beta;

	d0 = FxsVector3Distance(tp0, p);
	d1 = FxsVector3Distance(tp1, p);
	d2 = FxsVector3Distance(tp2, p);

	if (d0 > d1 && d0 > d2) {
		pa = tp0;
		pb = tp1;
		pc = tp2;
		aa = ta0;
		ab = ta1;
		ac = ta2;
	} else if (d1 > d0 && d1 > d2) {
		pa = tp1;
		pb = tp0;
		pc = tp2;
		aa = ta1;
		ab = ta0;
		ac = ta2;
	} else {
		pa = tp2;
		pb = tp0;
		pc = tp1;
		aa = ta2;
		ab = ta0;
		ac = ta1;
	}
	
	/* compute the plane (dplane, nplane) */
	FxsVector3Substract(&dca, pa, pc); 
	FxsVector3Substract(&dcb, pb, pc); 
	FxsVector3Cross(&ntmp, &dca, &dcb);
	FxsVector3Cross(&nplane, &dcb, &ntmp);
	FxsVector3Normalize(&nplane);
	FxsVector3Dot(&dplane, pc, &nplane);

	/* compute the ray from p in direction p - pa and its intersection with the planea*/
	FxsVector3Substract(&dirray, p, pa);
	FxsVector3Normalize(&dirray);
	FxsRayDoesIntersectPlane(p, &dirray, &t, dplane, &nplane);

	q.x = p->x + dirray.x * t;
	q.y = p->y + dirray.y * t;
	q.z = p->z + dirray.z * t;

    /* interpolate along bc*/
	bqlen = FxsVector3Distance(&q, pb);
	FxsVector3Length(&dcb, &bclen);

	alpha = bqlen/bclen;

	aq.x = ab->x + alpha * (ac->x - ab->x);
	aq.y = ab->y + alpha * (ac->y - ab->y);
	aq.z = ab->z + alpha * (ac->z - ab->z);

	FxsVector3Substract(&qa, &q, pa);
	FxsVector3Substract(&qp, &q, p);
	FxsVector3Length(&qa, &qalen);
	FxsVector3Length(&qp, &qplen);

	beta = qplen / qalen;

	taout->x = aq.x + beta * (aa->x - aq.x);
	taout->y = aq.y + beta * (aa->y - aq.y);
	taout->z = aq.z + beta * (aa->z - aq.z);
}

/*
** Computes the normal at the point of intersection between a ray and a face
** @see http://www.flipcode.com/archives/Interpolating_Normals_For_Ray-Tracing.shtml
*/ 
static void FaceGetInterpolatedNormal(
	FxsObjFile2 *file, 
	int faceId, 
	FxsVector3 *normal,
	const Ray *ray,
	float t
)
{
	FxsObjFile2Face *f = &file->faces[faceId];
	FxsVector3 p;
	p.x = ray->origin.x + t * ray->direction.x;
	p.y = ray->origin.y + t * ray->direction.y;
	p.z = ray->origin.z + t * ray->direction.z;

	TriangleInterpolateVector3(
		&file->positions[f->p0],
		&file->positions[f->p1],
		&file->positions[f->p2],
		&file->normals[f->n0],
		&file->normals[f->n1],
		&file->normals[f->n2],
		normal,
		&p
	);

	FxsVector3Normalize(normal); /* TODO: dunno if this is neccessary */
}
	
/*
** Tests if the object is hit by the ray. If it is hit, the functions fills out
** the shading record and returns 1, otherwise it returns 0.
*/ 
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

	/* fill out shading record */
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

	if (object->file->faces[hitFaceId].type & FXS_OBJ2_FACE_NORMALS) {
		FaceGetInterpolatedNormal(object->file, hitFaceId, &sr->normal, ray, *t);
	} else {
		FxsVector3Make(&sr->normal, 1.0, 0.0, 0.0);
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
