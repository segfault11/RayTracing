//------------------------------------------------------------------------------
//
//  Camera.h
//  FirstRayTracer
//
//  Created by Arno in Wolde Lübke on 06.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
#ifndef __FirstRayTracer__Camera__
#define __FirstRayTracer__Camera__

#include <iostream>
#include <CGK/Math/Matrix4.h>

template<typename REAL>
class Camera
{
public:
    Camera(
        const CGKMatrix4<REAL>& cameraToworld,
        const REAL& fovy,
        const REAL& nearPlane,
        const REAL& farPlane
    );
    ~Camera();
    
    CGKMatrix4<REAL> CameraToWorld;
    REAL Fovy;
    REAL NearPlane;
    REAL FarPlane;
};

typedef Camera<float> Cameraf;

#include "Camera.inl"


#endif /* defined(__FirstRayTracer__Camera__) */
