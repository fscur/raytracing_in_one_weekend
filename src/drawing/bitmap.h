#pragma once
#include "../common/types.h"

#ifdef WIN32
#include <Windows.h>
#endif WIN32

class bitmap
{
public:
    bitmap(uint width, uint height);
    void setPixel(uint x, uint y, byte r, byte g, byte b);
    void blit(void* dc);
    ~bitmap();

private:
#ifdef WIN32
    HDC _hdc;
    HBITMAP _bmp;
    BITMAPINFO _bmi;
#endif

public:
    uint width;
    uint height;
    unsigned char* data;
};