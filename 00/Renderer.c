#include "Renderer.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Renderer.h"

#define VEC3FROMVEC4(V3, V4) V3.x = V4.x; V3.y = V4.y; V3.z = V4.z;

typedef struct Renderer Renderer;

struct Renderer {
	RenderContext *renderContext;
};

RendererPtr RendererCreate(RenderContext *rc)
{
	RendererPtr r = malloc(sizeof(Renderer));	

	assert(rc->image->numChannels == 3);
	
	r->renderContext = rc;

	return r;
}

void RendererDestroy(RendererPtr *renderer)
{

}

void RendererRender(RendererPtr renderer, const char* filename, float fovy)
{
	Ray r;
    FxsVector4 vtmp;
	int i, j;
	FxsImage *img = renderer->renderContext->image;
	ObjectPtr obj = renderer->renderContext->object;
	float asp = ((float)img->width)/img->height;
	float tanfov = tanf(M_PI / 180.0f * fovy / 2.0);
	float t;
	ShadingRecord sr;

	for (i = 0; i < img->width; i++) {
	    for (j = 0; j < img->height; j++) {
            FxsVector3MakeZero(&r.origin);
	        r.direction.x = 2.0f * ((i + 0.5f)/img->width) - 1.0f;
	        r.direction.y = 2.0f * ((j + 0.5f)/img->height) - 1.0f;
			r.direction.x *= (tanfov * asp);
			r.direction.y *= tanfov;
            r.direction.z = -1.0f;
           	 
            FxsMatrix4MultiplyVector3(&vtmp, &renderer->renderContext->cameraToWorld, &r.origin);
            VEC3FROMVEC4(r.origin, vtmp);
            FxsMatrix4MultiplyVector3(&vtmp, &renderer->renderContext->cameraToWorld, &r.direction);
            VEC3FROMVEC4(r.direction, vtmp);
            FxsVector3Substract(&r.direction, &r.direction, &r.origin);
            FxsVector3Normalize(&r.direction);
            
			sr.color[0] = renderer->renderContext->defaultColor[0];
			sr.color[1] = renderer->renderContext->defaultColor[1];
			sr.color[2] = renderer->renderContext->defaultColor[2];

			if (ObjectIsIntersectedByRay(obj, &t, &sr, &r)) {
			    FxsImageSet(img, i, img->height - 1 - j, sr.color);
			} else {
			    FxsImageSet(img, i, img->height - 1 - j, renderer->renderContext->bgColor);
			}
	    }
	}

	FxsImageSave(img, filename);
}
