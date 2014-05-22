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
//------------------------------------------------------------------------------
int main(int argc, const char * argv[])
{
    CGKMatrix4f ctw;
    ctw.MakeIdentity();
    ctw.MakeTranslation(0.0, 0.0, -2.0);
    
    CGKMatrix4f o2w;
    o2w.MakeScale(0.5, 1.0, 1.0);

    Sphere<float> s(
        CGKVector3<float>(3.0, 2.0, -7.0),
        1.0,
        o2w,
        CGKColor3f(1.0, 0.0, 0.0)
    );
    
    Sphere<float> s2(
        CGKVector3f(-4.0, 0.0, -3.45),
        2.0,
        ctw,
        CGKColor3f(0.0, 0.0, 1.0)
    );
    
    Triangle<float> tr(
        CGKVector3f(-1.0, 0.0, -1.0),
        CGKVector3f(0.0, 1.0, -1.0),
        CGKVector3f(1.0, 0.0, -1.0),
        ctw,
        CGKColor3f(1.0, 0.0, 0.0)
    );
    
    Cameraf cam(ctw, 60.0*M_PI/180.0, 0.1, 100.0);
    RenderContextf rc(cam, 640, 480, CGKColor3f(1.0, 1.0, 1.0));
//    rc.AddObject(s);
//    rc.AddObject(s2);
    rc.AddObject(tr);
    rc.Render();
    rc.SaveFrameBufferToPPM("test.ppm");
    std::cout << "Hello, World!\n";
    return 0;
}
//------------------------------------------------------------------------------

