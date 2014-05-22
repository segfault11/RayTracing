//
//  Framebuffer.h
//  CreatingPrimaryRays
//
//  Created by Arno in Wolde Lübke on 03.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//

#ifndef __CreatingPrimaryRays__Framebuffer__
#define __CreatingPrimaryRays__Framebuffer__

#include <iostream>
#include "Vec3.h"
#include <string>
#include <memory>
#include <cstdlib>
#include <fstream>
#include <cassert>

template<typename REAL>
class Framebuffer
{
public:
    Framebuffer(int width, int height);
    ~Framebuffer();
    
    Vec3<REAL>& operator()(int i, int j);
    
    void SetClearColor(const Vec3<REAL>& color);
    void Clear();
    
    int GetWidth() const {return width;}
    int GetHeight() const {return height;}
    
    void ToPPM(const std::string& filename) const;
    
private:
    Vec3<REAL>* buffer;
    Vec3<REAL> clearColor;
    int width, height;
};

#include "Framebuffer.inl"


typedef Framebuffer<double> Framebufferd;
typedef Framebuffer<float> Framebufferf;

#endif /* defined(__CreatingPrimaryRays__Framebuffer__) */
