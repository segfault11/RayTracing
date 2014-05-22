//------------------------------------------------------------------------------
//
//  RenderContext.cpp
//  FirstRayTracer
//
//  Created by Arno in Wolde Lübke on 06.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
template<typename REAL>
RenderContext<REAL>::RenderContext(
    const Camera<REAL>& camera,
    int width,
    int height,
    const CGKColor3<REAL>& backgroundColor
)
: camera(camera), backgroundColor(backgroundColor), framebuffer(width, height)
{

}
//------------------------------------------------------------------------------
template<typename REAL>
RenderContext<REAL>::~RenderContext()
{

}
//------------------------------------------------------------------------------
template<typename REAL>
void RenderContext<REAL>::Render()
{
    int w = this->framebuffer.GetWidth();
    int h = this->framebuffer.GetHeight();
    float asp = static_cast<REAL>(w)/h;
    float tanfovy = std::tan(this->camera.Fovy/2.0);
    Ray<REAL> ray;
    
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            REAL x = (REAL(2.0)*((i + REAL(0.5))/w) - REAL(1.0))*
                    tanfovy*asp;
            REAL y = (REAL(1.0) - REAL(2.0)*((j + REAL(0.5))/h))*
                    tanfovy;
            REAL z = REAL(-1.0);
            
            CGKVector3<REAL> direction(x, y, z);
            direction.Normalize();
            
            this->framebuffer.Pixel(i, j) = trace(Ray<REAL>(
                    CGKVector3<REAL>(0.0, 0.0, 0.0),
                    direction
                ));
        }
    }
}
//------------------------------------------------------------------------------
template<typename REAL>
CGKColor3<REAL> RenderContext<REAL>::trace(const Ray<REAL>& ray) const
{
    REAL t = 0.0;
    REAL tClosest = this->camera.FarPlane;
    const AObject<REAL>* res = nullptr;

    for (const AObject<REAL>* obj : this->objects)
    {
        if (obj->IsIntersectedByRay(t, ray))
        {
            if (t < tClosest)
            {
                res = obj;
                tClosest = t;
            }
        }
    }
    
    if (nullptr == res)
    {
        return this->backgroundColor;
    }
    
    return res->GetColor();
}
//------------------------------------------------------------------------------
template<typename REAL>
void RenderContext<REAL>::SaveFrameBufferToPPM(
    const std::string& filename
) const
{
    this->framebuffer.ToPPM(filename);
}
//------------------------------------------------------------------------------
template<typename REAL>
void RenderContext<REAL>::AddObject(const AObject<REAL>& object)
{
    this->objects.push_back(&object);
}
//------------------------------------------------------------------------------