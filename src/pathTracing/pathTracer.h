#pragma once
#include "../common/types.h"
#include "../drawing/bitmap.h"
#include "../math/ray.h"
#include "../scene/scene.h"
#include "../scene/camera.h"

class pathTracer
{
public:
    pathTracer(scene* scene);
    ~pathTracer();

    void run(uint width, uint height, uint ssp, bitmap* canvas, void* dc);

private:
    vec3 li(const ray& r, int depth);

private:
    const float MAX_FLOAT;
    scene* _scene;
    camera* _camera;
};