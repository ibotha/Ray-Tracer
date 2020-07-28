#include "RayTracer.h"
#include "glm/gtc/constants.hpp"
#include <iostream>
#include <windows.h>
#include <ppl.h>
#include "Camera.h"
#include "Ray.h"
#include "Random.h"

using namespace concurrency;
using namespace std;

RayTracer::RayTracer(int32_t w, int32_t h, int _max_depth, int _samplesPerPixel)
    :m_Render(w, h), max_depth(_max_depth), samplesPerPixel(_samplesPerPixel) {}

// Computes the product of two square matrices in parallel.
void RayTracer::render_parallel() {

    std::cout << "Starting Render in Parallel.\n";

    float FOV = m_Scene.camera.FOV;
    const float AR = m_Render.height / static_cast<float>(m_Render.width);
    const float	invHeight = 1.0f / static_cast<float>(m_Render.height);
    const float	invWidth = 1.0f / static_cast<float>(m_Render.width);
    const float	angle = glm::tan(FOV * 0.5f); // TODO: get FOV from camera
    const size_t width = static_cast<size_t>(m_Render.width);
    const float ARangle = angle * (1 / AR);

    std::atomic<int> widthSum = 0;
    const int widthSegment = width / 5;

    parallel_for(size_t(0), width, [&](size_t x) {

        auto count = widthSum++;
        if (count % widthSegment == 0) {
            std::cout << (float)(((float) count / (float) width) * 100) << "%\n";
        }

        float xSalt = 0, ySalt = 0;

        for (int y = 0; y < m_Render.height; y++) {

            glm::vec3 colour = { 0, 0, 0 };
            for (int i = 0; i < samplesPerPixel; i++) {

                if (i == 0) {
                    xSalt = 0;
                    ySalt = 0;
                }
                else {
                    xSalt = random_float();
                    ySalt = random_float();
                }

                Ray ray({ 0, 0, 0 }, {
                        (2 * (x + xSalt) * invWidth - 1) * ARangle,//(2.0f * ((float)x + 0.5f) * invwidth - 1.0f) * (float)m_Render.width * invheight * angle,
                        ((2 - 2 * (y + ySalt) * invHeight) - 1) * angle,//(1.0f - 2.0f * ((float)y + 0.5f) * invheight) * angle,
                        -1.0f
                    });
                ray.Normalize();
                ray = m_Scene.camera.transform.ToWorldSpace(ray);
                colour += Trace(ray);
            }
            float scale = 1.0f / samplesPerPixel;
            //colour = glm::sqrt(colour * scale);
            auto scaled_colour = colour * scale;
            colour = glm::log2(scaled_colour + 1.0f);
            m_Render.SetPixel(x, y, olc::Pixel(colour.r * 255, colour.g * 255, colour.b * 255));
        }
    });
}


void RayTracer::render() {
    std::cout << "Starting Render.\n";

    float FOV = m_Scene.camera.FOV;
    const float AR = m_Render.height / static_cast<float>(m_Render.width);
    const float	invHeight = 1.0f / static_cast<float>(m_Render.height);
    const float	invWidth = 1.0f / static_cast<float>(m_Render.width);
    const float	angle = glm::tan(FOV * 0.5f); // TODO: get FOV from camera
    const float ARangle = angle * (1 / AR);

    for (int x = 0; x < m_Render.width; x++) {
        
        if (x % 25 == 0)
            std::cout << ((float) x / m_Render.width) * 100 << "%\n";

        float xSalt = 0, ySalt = 0;
        
        for (int y = 0; y < m_Render.height; y++) {

            glm::vec3 colour = { 0, 0, 0 };
            for (int i = 0; i < samplesPerPixel; i++) {

                if (i == 0) {
                    xSalt = 0;
                    ySalt = 0;
                }
                else {
                    xSalt = random_float();
                    ySalt = random_float();
                }

                Ray ray({ 0, 0, 0 }, {
                        (2 * (x + xSalt) * invWidth - 1) * ARangle,//(2.0f * ((float)x + 0.5f) * invwidth - 1.0f) * (float)m_Render.width * invheight * angle,
                        ((2 - 2 * (y + ySalt) * invHeight) - 1) * angle,//(1.0f - 2.0f * ((float)y + 0.5f) * invheight) * angle,
                        -1.0f
                    });
                ray.Normalize();
                ray = m_Scene.camera.transform.ToWorldSpace(ray);
                colour += Trace(ray);
            }
            float scale = 1.0f / samplesPerPixel;
            auto scaled_colour = colour * scale;
            colour = glm::sqrt(scaled_colour);
            m_Render.SetPixel(x, y, olc::Pixel(colour.r * 255, colour.g * 255, colour.b * 255));
        }
    }

    std::cout << "Done Rendering.\n";
}

// Sends a ray out into the scene and returns the color after all lighting and other calculations
glm::vec3 RayTracer::Trace(const Ray& ray, int depth) {
    Intersection i = m_Scene.Intersect(ray, 0.001f, INFINITY);

    if (i.hit) {
        //return (i.normal + glm::vec3(1)) * 0.5f;
        Ray n;
        glm::vec3 attenuation;
        if (depth > max_depth || !i.object->mat->scatter(ray, i, attenuation, n))
            return glm::vec3(0, 0, 0);
        glm::vec3 col = attenuation * Trace(n, depth + 1);
        return col;
    }
    else {
        // render sky blend
        glm::vec3 top(0.5, 0.7, 1.0f);
        glm::vec3 bottom(1.0f, 1.0f, 1.0f);
        float factor = (ray.direction.y + 1.0f) * 0.5f;
        glm::vec3 current = (1.0f - factor) * bottom + factor * top;
        return current;
    }
}
