#include "ppmWriter.h"

ppmWriter::ppmWriter(std::string fileName, uint width, uint height) :
    _writer(new textWriter(fileName))
{
    auto header = "P3\n" + std::to_string(width) + " " + std::to_string(height) + "\n255\n";
    _writer->writeLine(header);
}

void ppmWriter::write(float r, float g, float b)
{
    write(
        byte(255.9999f * r),
        byte(255.9999f * g),
        byte(255.9999f * b));
}

void ppmWriter::write(byte r, byte g, byte b)
{
    _writer->writeLine(
        std::to_string(r) + " " +
        std::to_string(g) + " " +
        std::to_string(b));
}

ppmWriter::~ppmWriter()
{
    delete _writer;
}


