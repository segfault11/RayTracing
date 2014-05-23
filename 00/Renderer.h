#ifndef RENDERER_H
#define RENDERER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <Fxs/Math/Matrix4.h>
#include <Fxs/Image/Image.h>
#include "Object.h"

typedef struct RenderContext RenderContext;

struct RenderContext {
	FxsImage *image;
	ObjectPtr object;    
	unsigned char bgColor[3];
	unsigned char defaultColor[3]; /* default color of nodes that have no 
						    	   ** diffuse color attached to it
								   */
	FxsMatrix4 cameraToWorld;
};


typedef struct Renderer* RendererPtr;

RendererPtr RendererCreate(RenderContext *rc);
void RendererDestroy(RendererPtr *renderer);
void RendererRender(RendererPtr renderer, const char* filename, float fovy);

#ifdef __cplusplus
}
#endif


#endif /* end of include guard: RENDERER_H */
