#include "pathTracer.h"

scene* pathTracer::createRandomScene()
{
    scene* world = new scene();

    /*auto l0 = new lambertianMaterial(vec3(0.1f, 0.2f, 0.5f));
    auto l1 = new lambertianMaterial(vec3(0.8f, 0.8f, 0.0f));
    auto m0 = new metalMaterial(vec3(0.8f, 0.6f, 0.2f), 0.0f);
    auto d0 = new dielectricMaterial(1.5f);
    auto d1 = new dielectricMaterial(1.5f);

    auto s0 = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, l0);
    auto s1 = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f, l1);
    auto s2 = new sphere(vec3(1.0f, 0.0f, -1.0f), 0.5f, m0);
    auto s3 = new sphere(vec3(-1.0f, 0.0f, -1.0f), 0.5f, d0);
    //auto s4 = new sphere(vec3(-1.0f, 0.0f, -1.0f), -0.45f, d1);

    world.add(s0);
    world.add(s1);
    world.add(s2);
    world.add(s3);*/
    //world.add(s4);

    /*auto l0 = new lambertianMaterial(vec3(0.0f, 0.0f, 1.0f));
    auto l1 = new lambertianMaterial(vec3(1.0f, 0.0f, 0.0f));
    float R = cos(glm::quarter_pi<float>());
    auto s0 = new sphere(vec3(-R, 0.0f, -1.0f), R, l0);
    auto s1 = new sphere(vec3(+R, 0.0f, -1.0f), R, l1);
    world.add(s0);
    world.add(s1);*/

    world->addShape(new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5))));

    for (int a = -3; a < 3; a++)
    {
        for (int b = -3; b < 3; b++)
        {
            float choose_mat = random::next();

            vec3 center(a + 0.9 * random::next(), 0.2, b + 0.9 * random::next());

            if ((center - vec3(4, 0.2, 0)).length() > 0.5)
            {
                if (choose_mat < 0.7)
                {  // diffuse
                    auto color = vec3(
                        random::next() * random::next(),
                        random::next() * random::next(),
                        random::next() * random::next());

                    world->addShape(new sphere(center, 0.2f, new lambertian(color)));

                }
                else if (choose_mat < 0.85)
                { // metal
                    auto color = vec3(
                        0.5 * (1 + random::next()),
                        0.5 * (1 + random::next()),
                        0.5 * (1 + random::next()));

                    world->addShape(new sphere(center, 0.2f, new metal(color, 0.5f * random::next())));
                }
                else
                {
                    world->addShape(new sphere(center, 0.2, new dielectric(1.5f)));
                }
            }
        }
    }

    world->addShape(new sphere(vec3(-4, 1, 0), 1.0, new metal(vec3(0.5, 0.4, 0.7), 0.0)));
    world->addShape(new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5)));
    world->addShape(new sphere(vec3(4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1))));

    return world;
}

pathTracer::pathTracer(uint width, uint height, uint ssp) :
    _width(width),
    _height(height),
    _ssp(ssp)
{
    _scene = *pathTracer::createRandomScene();
}

pathTracer::~pathTracer()
{
}

vec3 pathTracer::li(const ray & r, int depth)
{
    intersection hit;
    bool anyHit = _scene.hit(r, 0.0001f, std::numeric_limits<float>().max(), hit);

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

void pathTracer::run()
{
    auto writer = new ppmWriter("raytracing.ppm", _width, _height);

    vec3 from(12.0f, 2.0f, 6.0f);
    vec3 at(0.0f, 0.5f, 0.0f);
    float focusDistance = length(from - at);
    float aperture = 0.5f;

    float fov = 20.0f * (glm::pi<float>() / 180.0f);
    camera cam(fov, float(_width) / float(_height), aperture, focusDistance);

    cam.lookAt(from, at, vec3(0.0f, 1.0f, 0.0f));

    auto total = _height;

    for (int j = _height - 1; j >= 0; --j)
    {
        for (int i = 0; i < _width; ++i)
        {
            auto color = vec3();
            for (int k = 0; k < _ssp; ++k)
            {
                float u = float(i + random::next()) / float(_width);
                float v = float(j + random::next()) / float(_height);
                const ray r = cam.castRay(vec2(u, v));
                color += li(r, 0);
            }
            color /= float(_ssp);
            writer->write(sqrt(color.x), sqrt(color.y), sqrt(color.z));
        }

        auto current = (float(_height - j) / float(_height)) * 100.0f;

        std::cout << std::to_string(int(current)) << "%" << std::endl;
    }

    delete (writer);

    std::cout << "ended" << std::endl;
}
