#pragma once
#include "../common/types.h"
#include "console.h"
#include "mouseEventArgs.h"
#include "keyboardEventArgs.h"

#ifdef WIN32
#include <Windows.h>
#endif

class window
{
public:
    window(std::string name, uint width, uint height);
    virtual ~window();

    void init();
    void clear();
    void render();
    void input();
    void update();
    void tick();
    void close();

    virtual void onInit() = 0;
    virtual void onUpdate() = 0;
    virtual void onRender() = 0;
    virtual void onClosing() = 0;

    virtual void onTick();

private:
    void adjustWindowToScreenBounds();

public:
    bool closed;

protected:
    std::string _name;
    uint _width;
    uint _height;

#ifdef WIN32
public:
    HDC getDC() const { return _deviceContext; }

private:
    static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static int convertToKey(WPARAM wParam);

    void createWindow(std::string name, uint width, uint height);
    PIXELFORMATDESCRIPTOR getPixelFormatDescriptor();
    void getDpi();

private:
    HWND _windowHandle;
    HINSTANCE _applicationInstance;
    HDC _deviceContext;
    HGLRC _renderingContext;
    DWORD _windowExStyle = 0;
    DWORD _windowStyle = WS_OVERLAPPEDWINDOW;
#endif

};