//------------------------------------------------------------------------------
//
//  ObjObject.h
//  CornellBox
//
//  Created by Arno in Wolde Lübke on 20.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------

#ifndef __CornellBox__ObjObject__
#define __CornellBox__ObjObject__

#include <iostream>
#include <string>
#include "Object.h"
#include "RayTriangleIntersection.h"
#include <limits>
#include "AObject.h"

template<typename REAL>
class ObjObject : public AObject<REAL>
{
public:
    ObjObject(
        const std::string& filename,
        const CGK::Math::Matrix4<REAL>& objectToWorld
    );
    
    ~ObjObject();
    
    void TraceWithRay(const Ray<REAL>& ray) const;
    
private:
    CGK::Obj::File* objFile;
};

#include "ObjObject.inl"

#endif /* defined(__CornellBox__ObjObject__) */
