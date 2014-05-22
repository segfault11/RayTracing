/*
** @file Ray.h
** @brief Declaration of a ray structure.
*/
#ifndef RAY_H
#define RAY_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <Fxs/Math/Vector3.h>

typedef struct _Ray  {
	FxsVector3 origin;
	FxsVector3 direction;
} Ray;

#ifdef __cplusplus
}
#endif


#endif /* end of include guard: RAY_H */
