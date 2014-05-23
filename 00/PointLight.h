#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <Fxs/Math/Vector3.h>

/*
** Definition of a simple point light that has a position
** and emits light of a certain color.
*/ 
typedef struct PointLight PointLight;

struct PointLight {
	FxsVector3 position;
	FxsVector3 color;
};

#ifdef __cplusplus
}
#endif

#endif /* end of include guard: POINTLIGHT_H */
