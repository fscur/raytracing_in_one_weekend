#include "window.h"

window::window(std::string name, uint width, uint height) :
    _name(name),
    _width(width),
    _height(height),
    closed(false) {}

window::~window()
{
}

void window::clear()
{
}

void window::render()
{
    onRender();
}

void window::update()
{
    onUpdate();
}

void window::tick()
{
    onTick();
}

void window::onTick() {}