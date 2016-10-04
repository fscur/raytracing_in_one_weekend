#pragma once
#include <vector>
#include "../math/ray.h"
#include "../common/intersection.h"
#include "../shapes/shape.h"

class scene
{
public:
    scene();
    void addShape(shape* shape);
    bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const;

private:
    std::vector<shape*> _shapes;
};


