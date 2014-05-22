#include "Renderer.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "Renderer.h"

typedef struct Renderer Renderer;

struct Renderer {
    FxsImage *image;
	ObjectPtr object;
};

RendererPtr RendererCreate(FxsImage* image, ObjectPtr object)
{
	RendererPtr r = malloc(sizeof(Renderer));	

	assert(image->numChannels == 3);

	r->image = image;
	r->object = object;

	return r;
}

void RendererDestroy(RendererPtr *renderer)
{

}

void RendererRender(RendererPtr renderer, const char* filename, float fovy)
{
	Ray r;
	int i, j;
	FxsVector3MakeZero(&r.origin);	
	float asp = ((float)renderer->image->width)/renderer->image->height;
	float tanfov = tanf(M_PI / 180.0f * fovy / 2.0);
	float t;
	ShadingRecord sr;
	unsigned char fg[3] = {255, 0, 0};
	unsigned char bg[3] = {255, 255, 255};

	for (i = 0; i < renderer->image->width; i++) {
	    for (j = 0; j < renderer->image->height; j++) {
	        r.direction.x = 2.0f * ((i + 0.5f)/renderer->image->width) - 1.0f;
	        r.direction.y = 2.0f * ((j + 0.5f)/renderer->image->height) - 1.0f;
			r.direction.x *= (tanfov * asp);
			r.direction.y *= tanfov;
            r.direction.z = -1.0f;
            FxsVector3Normalize(&r.direction);
            
			if (ObjectIsIntersectedByRay(renderer->object, &t, &sr, &r)) {
			    FxsImageSet(renderer->image, i, renderer->image->height - 1 - j, fg);
			} else {
			    FxsImageSet(renderer->image, i, renderer->image->height - 1 - j, bg);
			}
	    }
	}

	FxsImageSave(renderer->image, filename);
}
