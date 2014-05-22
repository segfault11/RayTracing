//------------------------------------------------------------------------------
//
//  Framebuffer.inl
//  CreatingPrimaryRays
//
//  Created by Arno in Wolde Lübke on 03.01.14.
//  Copyright (c) 2014 Arno in Wolde Lübke. All rights reserved.
//
//------------------------------------------------------------------------------
template<typename REAL>
Framebuffer<REAL>::Framebuffer(int width, int height)
: width(width), height(height)
{
    this->buffer = new CGK::Math::Color3<REAL>[width*height];
    std::memset(this->buffer, 0, sizeof(CGK::Math::Color3<REAL>)*width*height);
}
//------------------------------------------------------------------------------
template<typename REAL>
Framebuffer<REAL>::~Framebuffer()
{
    delete[] this->buffer;
}
//------------------------------------------------------------------------------
template<typename REAL>
CGK::Math::Color3<REAL>& Framebuffer<REAL>::Pixel(int i, int j)
{
    assert(!(i < 0 || i >= width || j < 0 || j >= height));
    
    int idx = j*this->width + i;
    
    return this->buffer[idx];
}
//------------------------------------------------------------------------------
template<typename REAL>
void Framebuffer<REAL>::ToPPM(const std::string& filename) const
{
    std::ofstream file;
    
    file.open(filename, std::ios::out | std::ios::binary);
    
    file << "P6" << std::endl;
    file << width << " " << height << std::endl;
    file << "255" << std::endl;
    
    
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int idx = j*this->width + i;
            unsigned char r, g, b;
            
            r = this->buffer[idx][0]*REAL(255);
            g = this->buffer[idx][1]*REAL(255);
            b = this->buffer[idx][2]*REAL(255);
            
            file << r << g  << b;
        }
    }
    
    file.close();
}
//------------------------------------------------------------------------------
template<typename REAL>
void Framebuffer<REAL>::SetClearColor(const CGK::Math::Color3<REAL>& color)
{
    this->clearColor = color;
}
//------------------------------------------------------------------------------
template<typename REAL>
void Framebuffer<REAL>::Clear()
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            int idx = j*this->width + i;
            this->buffer[idx] = clearColor;
        }
    }
}
//------------------------------------------------------------------------------




