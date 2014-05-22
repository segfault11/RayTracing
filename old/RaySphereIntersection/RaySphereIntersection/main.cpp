//------------------------------------------------------------------------------
//
//  main.cpp
//  CreatingPrimaryRays
//
//  Created by Arno in Wolde Lübke on 03.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
#include <iostream>
#include <cmath>
#include "Framebuffer.h"
#include <CGK/Math/RaySphereIntersection.h>
//------------------------------------------------------------------------------
int main(int argc, const char * argv[])
{
    Framebufferf f(640, 480);

    int w = f.GetWidth();
    int h = f.GetHeight();
    float asp = static_cast<float>(w)/h;
    float fov = 60.0;
    float angle = std::tan(fov*M_PI/180.0*0.5);

    CGKVector3f c(3.0, 2.0, -7.0);
    float r = 1.0;
    
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            float x = (i + 0.5)/w;
            float y = (j + 0.5)/h;
            float z = -1.0;
            
            x = 2.0*x - 1.0;
            y = 1.0 - 2.0*y;

//            f.Pixel(i, j) = CGKVector3f(
//                x > 0 ? 1 : 0,
//                y > 0 ? 1 : 0,
//                0.0
//            );
            
            x *= asp*angle;
            y *= angle;
            
            CGKVector3f dir(x, y, z);
            dir.Normalize();
            
            //std::cout << dir.GetMagnitude() << std::endl;
        
            float t;
                        
            if (CGKMathRaySphereIntersection<float>(t, CGKVector3f(0.0, 0.0, 0.0), dir, c, r))
            {
                f.Pixel(i, j) = CGKColor3f(1.0, 0.0, 0.0);
            }
            else
            {
                f.Pixel(i, j) = CGKColor3f(1.0, 1.0, 1.0);
            }

        }
    }

    f.ToPPM("Test.ppm");

    return 0;
}
//------------------------------------------------------------------------------

