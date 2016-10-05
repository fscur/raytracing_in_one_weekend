#include <iostream>
#include "bitmap.h"

bitmap::bitmap(uint width, uint height) :
    width(width),
    height(height)
{
    _hdc = CreateCompatibleDC(NULL);
    _bmi.bmiHeader.biSize = sizeof(_bmi.bmiHeader);
    _bmi.bmiHeader.biWidth = width;
    _bmi.bmiHeader.biHeight = height;
    _bmi.bmiHeader.biPlanes = 1;
    _bmi.bmiHeader.biBitCount = 32;
    _bmi.bmiHeader.biCompression = BI_RGB;
    
    data = new byte[width * height * 4];

    _bmp = CreateDIBSection(_hdc, &_bmi, DIB_RGB_COLORS, (void**)&data, NULL, 0);
    _oldBmp = (HBITMAP)SelectObject(_hdc, _bmp);
}

void bitmap::blit(void* dc)
{
    SetDIBitsToDevice((HDC)_hdc, 0, 0, width, height, 0, 0, 0, height, &data[0], &_bmi, DIB_RGB_COLORS); // set the new dibs to the dc
    if (!BitBlt((HDC)dc, 0, 0, width, height, (HDC)_hdc, 0, 0, SRCCOPY))
    {
        std::cout << "BitBlt Error: " << HRESULT_FROM_WIN32(GetLastError()) << std::endl;
        system("pause");
    }
}

void bitmap::setPixel(uint x, uint y, float r, float g, float b)
{
    data[(y * width * 4) + (x * 4) + 0] = byte(255.9999f * b);
    data[(y * width * 4) + (x * 4) + 1] = byte(255.9999f * g);
    data[(y * width * 4) + (x * 4) + 2] = byte(255.9999f * r);
    data[(y * width * 4) + (x * 4) + 3] = 255;
}

void bitmap::setPixel(uint x, uint y, byte r, byte g, byte b)
{
    data[(y * width * 4) + (x * 4) + 0] = b;
    data[(y * width * 4) + (x * 4) + 1] = g;
    data[(y * width * 4) + (x * 4) + 2] = r;
    data[(y * width * 4) + (x * 4) + 3] = 255;
}

bitmap::~bitmap()
{
    SelectObject(_hdc, _oldBmp);
    DeleteObject(_bmp);
    DeleteDC(_hdc);
}