#pragma once
#include <stdlib.h>
#include <iostream>
#include <limits>

#include "../common/types.h"
#include "../io/ppmWriter.h"
#include "../scene/scene.h"
#include "../scene/camera.h"
#include "../common/sampler.h"
#include "../common/random.h"
#include "../shapes/sphere.h"
#include "../materials/lambertian.h"
#include "../materials/metal.h"
#include "../materials/dielectric.h"
#include "../math/ray.h"

class pathTracer
{
public:
    static scene* createRandomScene();

public:
    pathTracer(uint width, uint height, uint ssp);
    ~pathTracer();

    vec3 li(const ray& r, int depth);
    void run();

private:
    uint _width;
    uint _height;
    uint _ssp;
    scene _scene;
};