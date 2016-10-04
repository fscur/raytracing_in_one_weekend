#include "scene.h"

scene::scene()
{
}

bool scene::hit(const ray& ray, float tMin, float tMax, intersection& hit) const
{
    intersection tempRecord;
    bool hitAnything = false;
    double closestHit = tMax;
    auto listCount = _shapes.size();

    for (int i = 0; i < listCount; ++i)
    {
        if (_shapes[i]->hit(ray, tMin, closestHit, tempRecord))
        {
            hitAnything = true;
            closestHit = tempRecord.t;
            hit = tempRecord;
        }
    }

    return hitAnything;
}

void scene::addShape(shape* shape)
{
    _shapes.push_back(shape);
}
