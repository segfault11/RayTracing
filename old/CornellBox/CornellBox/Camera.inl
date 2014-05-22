//------------------------------------------------------------------------------
//
//  Camera.cpp
//  FirstRayTracer
//
//  Created by Arno in Wolde Lübke on 06.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
template<typename REAL>
Camera<REAL>::Camera(
    const CGK::Math::Matrix4<REAL>& cameraToWorld,
    const REAL& fovy,
    const REAL& nearPlane,
    const REAL& farPlane
)
:
    CameraToWorld(cameraToWorld),
    Fovy(fovy),
    NearPlane(nearPlane),
    FarPlane(farPlane)
{

}
//------------------------------------------------------------------------------
template<typename REAL>
Camera<REAL>::~Camera()
{

}
//------------------------------------------------------------------------------