#include <iostream>
#include "screen.h"

screen::screen(std::string name, uint width, uint height) :
    window(name, width, height)
{
}

screen::~screen()
{
}

void screen::onInit()
{
    _pathTracer = new pathTracer(200u, 100u, 100u);
    _onKeyUpToken = input::keyUp->assign(std::bind(&screen::onKeyUp, this, std::placeholders::_1));
}

void screen::onUpdate()
{
}

void screen::onRender()
{
}

void screen::onTick()
{
}

void screen::onKeyUp(keyboardEventArgs* args)
{
    if (args->key == PHIK_SPACE)
    {
        console::writeLine("started");
        _pathTracerTask = std::thread([&] {_pathTracer->run(); });
    }
}

void screen::onClosing()
{
}
