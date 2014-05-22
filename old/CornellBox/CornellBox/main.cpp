//------------------------------------------------------------------------------
//
//  main.cpp
//  FirstRayTracer
//
//  Created by Arno in Wolde Lübke on 04.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
#include <iostream>
#include "Ray.h"
#include "RenderContext.h"
#include "Sphere.h"
#include "Triangle.h"
#include "ObjObject.h"
#include "Vector3.h"
//------------------------------------------------------------------------------
int main(int argc, const char * argv[])
{
    CGK::Math::Matrix4f ctw;
    ctw.MakeIdentity();
    
    CGK::Math::Matrix4f t;
    t.MakeTranslation(0.0, 0.0, -3.0);
    CGK::Math::Matrix4f o2w;
    o2w.MakeIdentity();
    o2w.MakeScale(1.0, 1.0, 1.0);
    
    o2w = t*o2w;
    //o2w.MakeTranslation(0.0, 0.0, -1.0);
    
    ObjObject<float> obj("CornellBox2.obj", o2w);
    
    Triangle<float> tr(
        CGK::Math::Vector3f(-1.0, 0.0, 0.0),
        CGK::Math::Vector3f(0.0, 1.0, 0.0),
        CGK::Math::Vector3f(1.0, 0.0, 0.0),
        o2w,
        CGK::Math::Color3f(1.0, 0.0, 0.0)
    );
    
    Cameraf cam(ctw, 60.0*M_PI/180.0, 0.1, 100.0);
    RenderContextf rc(cam, 600, 800, CGK::Math::Color3f(1.0, 1.0, 1.0));
    rc.AddObject(obj);
    rc.Render();
    rc.SaveFrameBufferToPPM("test.ppm");

    return 0;
}
//------------------------------------------------------------------------------

