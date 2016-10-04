#pragma once
#include <thread>

#include "app/window.h"
#include "app/input.h"

#include "drawing/bitmap.h"

#include "pathTracing/pathTracer.h"

class screen :
    public window
{
public:
    screen(std::string name, uint witdh, uint height);
    ~screen(void);

    void onInit() override;
    void onClosing() override;
    void onUpdate() override;
    void onRender() override;
    void onTick() override;

    void onKeyUp(keyboardEventArgs* args);

private:
    eventToken _onKeyUpToken;
    bitmap* _image;
    pathTracer* _pathTracer;
    std::thread _pathTracerTask;
};