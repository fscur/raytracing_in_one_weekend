#include <iostream>
#include "../common/sampler.h"
#include "../common/random.h"
#include "../materials/material.h"
#include "../io/ppmWriter.h"
#include "../io/console.h"
#include "pathTracer.h"

#undef max

pathTracer::pathTracer(scene* scene) :
    _scene(scene),
    _camera(scene->getCamera()),
    MAX_FLOAT(std::numeric_limits<float>().max())
{
}

pathTracer::~pathTracer()
{
}

vec3 pathTracer::li(const ray& r, int depth)
{
    intersection hit;
    bool anyHit = _scene->hit(r, 0.0001f, MAX_FLOAT, hit);

    if (anyHit)
    {
        ray scattered;
        vec3 attenuation;

        if (depth < 3 && hit.material->scatter(r, hit, attenuation, scattered))
            return attenuation * li(scattered, depth + 1);
        else
            return vec3(0.0f);
    }
    else
    {
        vec3 dir = normalize(r.direction);
        float t = 0.5f * (dir.y + 1.0f);
        return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
}

void pathTracer::run(uint width, uint height, uint ssp, bitmap* ptr, void* dc)
{
    float issp = 1.0f / float(ssp);

    for (int y = height - 1; y >= 0; --y)
    {
        for (int x = 0; x < width; ++x)
        {
            vec3 color;
            for (int k = 0; k < ssp; ++k)
            {
                float u = float(x + random::next()) / float(width);
                float v = float(y + random::next()) / float(height);
                const ray r = _camera->castRay(vec2(u, v));
                color += li(r, 0);
            }
            color *= issp;
            ptr->setPixel(x, y, sqrt(color.x), sqrt(color.y), sqrt(color.z));
        }

        ptr->blit(dc);
    }
}