#include <iostream>
#include "screen.h"

screen::screen(std::string name, uint width, uint height) :
    window(name, width, height),
    _processing(false)
{
}

screen::~screen()
{
    delete _scene;
    delete _camera;
    delete _pathTracer;
}

void screen::onInit()
{
    initInput();
    initCamera();
    initScene();
    initPathTracer();
}

void screen::initInput()
{
    _onKeyUpToken = input::keyUp->assign(std::bind(&screen::onKeyUp, this, std::placeholders::_1));
}

void screen::initCamera()
{
    vec3 from(12.0f, 2.0f, 6.0f);
    vec3 at(0.0f, 0.5f, 0.0f);
    float focusDistance = length(from - at);
    float aperture = 0.5f;
    float fov = 20.0f * (glm::pi<float>() / 180.0f);

    _camera = new camera(fov, float(_width) / float(_height), aperture, focusDistance);
    _camera->lookAt(from, at, vec3(0.0f, 1.0f, 0.0f));
}

void screen::initScene()
{
    _scene = scene::createRandomScene(_camera);
}

void screen::initPathTracer()
{
    _canvasWidth = _width;
    _canvasHeight = _height;
    _canvasSsp = 256u;
    _pathTracer = new pathTracer(_scene);
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
    if (!_processing && args->key == PHIK_SPACE)
    {
        _processing = true;
        _pathTracerTask = std::thread([&] 
        {
            bitmap* image = new bitmap(_canvasWidth, _canvasHeight);
            _pathTracer->run(_canvasWidth, _canvasHeight, _canvasSsp, image, getDC());
            delete (image);
        });
        _processing = false;
    }
}

void screen::onClosing()
{
}