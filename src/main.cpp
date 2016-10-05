#include "app/application.h"
#include "screen.h"

extern "C"
{
    __declspec(dllexport) unsigned long NvOptimusEnablement = 1;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main(int argc, char* args[])
{
    application app;

    auto mainScreen = new screen("hit space to start [800 x 450 x 256 spp]", 800, 450);
    app.run(mainScreen);
    delete mainScreen;

    return 0;
}