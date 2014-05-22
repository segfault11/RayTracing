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
#include "Vec3.h"
#include "Ray3.h"
#include "Framebuffer.h"
//------------------------------------------------------------------------------
int main(int argc, const char * argv[])
{
    Framebufferf f(640, 480);

    int w = f.GetWidth();
    int h = f.GetHeight();
    float asp = static_cast<float>(w)/h;
    float fov = 60.0;
    float angle = std::tan(fov*M_PI/180.0*0.5);

    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            float x = (i + 0.5)/w;
            float y = (j + 0.5)/h;
            float z = -1.0;
            
            x = 2.0*x - 1.0;
            y = 1.0 - 2.0*y;
            
            x *= asp*angle;
            y *= angle;
            
            float r = x < 0.0 ? 1.0 : 0.0;
            float g = 0.0;
            float b = y < 0.0 ? 1.0 : 0.0;
            
            f(i, j) = Vec3f(r, g, b);
        }
    }

    f.ToPPM("Test.ppm");

    return 0;
}
//------------------------------------------------------------------------------

