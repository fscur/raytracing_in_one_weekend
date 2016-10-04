#pragma once
#include <glm/glm.hpp>
#include "../math/ray.h"
#include "../common/intersection.h"

class shape
{
public:
    virtual bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const = 0;
};