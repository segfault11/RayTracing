#ifndef RENDERER_H
#define RENDERER_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <Fxs/Image/Image.h>
#include "Object.h"

typedef struct Renderer* RendererPtr;

RendererPtr RendererCreate(FxsImage* image, ObjectPtr object);
void RendererDestroy(RendererPtr *renderer);
void RendererRender(RendererPtr renderer, const char* filename, float fovy);

#ifdef __cplusplus
}
#endif


#endif /* end of include guard: RENDERER_H */
