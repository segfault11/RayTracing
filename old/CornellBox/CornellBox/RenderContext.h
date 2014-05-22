//
//  RenderContext.h
//  FirstRayTracer
//
//  Created by Arno in Wolde Lübke on 06.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//

#ifndef __FirstRayTracer__RenderContext__
#define __FirstRayTracer__RenderContext__

#include <iostream>
#include "Matrix4.h"
#include "Framebuffer.h"
#include <list>
#include "AObject.h"
#include "Camera.h"
#include "Ray.h"

template<typename REAL>
class RenderContext
{
public:
    RenderContext(
        const Camera<REAL>& camera,
        int width,
        int height,
        const CGK::Math::Color3<REAL>& backgroundColor
    );
    ~RenderContext();

    void AddObject(const AObject<REAL>& object);
    void SaveFrameBufferToPPM(const std::string& filename) const;
    void Render();
    
private:
    CGK::Math::Color3<REAL> trace(const Ray<REAL>& ray) const;

    Camera<REAL> camera;
    Framebuffer<REAL> framebuffer;
    std::list<const AObject<REAL>* > objects;
    CGK::Math::Color3<REAL> backgroundColor;
};

typedef RenderContext<float> RenderContextf;

#include "RenderContext.inl"

#endif /* defined(__FirstRayTracer__RenderContext__) */
