//------------------------------------------------------------------------------
//
//  ObjObject.cpp
//  CornellBox
//
//  Created by Arno in Wolde Lübke on 20.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
template<typename REAL>
ObjObject<REAL>::ObjObject(
	const std::string& filename,
	const CGK::Math::Matrix4<REAL>& objectToWorld
)
: AObject<REAL>(objectToWorld, CGK::Math::Color3<REAL>(1.0, 0.0, 0.0)), objFile(nullptr)
{
    this->objFile = CGK::Obj::File::Load(filename);
}
//------------------------------------------------------------------------------
template<typename REAL>
ObjObject<REAL>::~ObjObject()
{
    CGK::Obj::File::Release(&this->objFile);
}
//------------------------------------------------------------------------------
template<typename REAL>
void ObjObject<REAL>::TraceWithRay(const Ray<REAL>& ray) const
{
//    std::cout << __FUNCTION__ << std::endl;

    REAL tClosest = std::numeric_limits<REAL>::max();
    REAL t;
    unsigned int matIdx;
    
//    std::cout << objFile->Objects.size() << std::endl;
    
    for (const CGK::Obj::Object& obj : objFile->Objects)
    {
        for (const CGK::Obj::Group& grp : obj.Groups)
        {
            for (const CGK::Obj::Face& face : grp.Faces)
            {
                const CGK::Math::Tuple3ui& pi = face.PositionIndices;
                const CGK::Math::Vector3<REAL> a = this->objFile->Positions[pi[0]];
                const CGK::Math::Vector3<REAL> b = this->objFile->Positions[pi[1]];
                const CGK::Math::Vector3<REAL> c = this->objFile->Positions[pi[2]];
                
                bool isIntersecting = CGK::Math::RayTriangleIntersection(
                        t,
                        ray.Origin,
                        ray.Direction,
                        a, b, c
                    );
                
                if (isIntersecting)
                {
                    if (t < tClosest)
                    {
                        tClosest = t;
                        matIdx = face.MaterialIndex;
                    }
                }
            }
        }
    }
    
    if (tClosest < std::numeric_limits<REAL>::max())
    {
        this->isHit = true;
        this->distance = tClosest;
        this->color = this->objFile->Materials[matIdx].Diffuse;
        return;
    }
    
    this->isHit = false;
}
//------------------------------------------------------------------------------
