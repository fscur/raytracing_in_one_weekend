#pragma once

#include "textWriter.h"
#include "../common/types.h"

class ppmWriter
{
public:
    ppmWriter(std::string fileName, uint width, uint height);
    void write(float r, float g, float b);
    void write(byte r, byte g, byte b);
    ~ppmWriter();

private:
    textWriter* _writer;
};


