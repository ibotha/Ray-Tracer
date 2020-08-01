#include "RayTracer.h"
#include "Sphere.h"
#include "Disk.h"
#include "Triangle.h"
#include "TriangleGlm.h"
#include "SphereGlm.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class App : public olc::PixelGameEngine {
private:
    RayTracer* tracer;

public:
    App() {
        sAppName = "Ray-Tracer";
    }

public:
    bool OnUserCreate() override {
        std::cout << "Creating RayTracer\n";
        //populate scene here
        int samplesPerPixel = 16;
        int maxDepth = 32;
        tracer = new RayTracer(ScreenWidth(), ScreenHeight(), maxDepth, samplesPerPixel);
        Scene& scene = tracer->GetScene();

        CreateCamera(scene);
        PopulateSceneObjects(scene);
        
        //tracer->Render();
        /*tracer->RenderParallel();
        auto img = &tracer->GetRender();
        DrawSprite({ 0, 0 }, img);*/
        
        tracer->RenderDepth();
        auto depthImg = &tracer->GetDepth();
        DrawSprite({ 0, 0 }, depthImg);
        return true;
    }

    void CreateCamera(Scene& scene) {
        glm::vec3 CameraPos = { 0, 0, 5 };
        glm::vec3 CameraDir = { 0, 0, 0 };
        scene.camera = Camera(CameraPos, CameraDir);
    }

    void PopulateSceneObjects(Scene& scene) {
        scene.objects.push_back(std::make_shared<Sphere>(glm::vec3(0, 1, 0), 1));
        scene.objects.push_back(std::make_shared<SphereGlm>(glm::vec3(0, -1, 0), 1));
        //scene.objects.back()->mat = std::make_shared<Metal>(glm::vec3(0.9f, 0.9f, 0.9f), 0.0f);

        //scene.objects.push_back(std::make_shared<Sphere>(glm::vec3(2, -0.5, 0), 0.5));
        //scene.objects.back()->mat = std::make_shared<Dielectric>(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, 1.5f);

        scene.objects.push_back(std::make_shared<Disk>(glm::vec3(0, 0, -0.5), glm::vec3(-0.5, 0.5, 0.5), 2.0f));

        //scene.objects.push_back(std::make_shared<Plane>(glm::vec3(0, 0, -0.5), glm::vec3(0.5, 0.5, 0.5)));
        //scene.objects.push_back(std::make_shared<TriangleGlm>(glm::vec3(0, 0, -100), glm::vec3(0, 3, -0.1), glm::vec3(3, 0, -0.1)));

        // Large base sphere.
        //scene.objects.push_back(std::make_shared<Sphere>(glm::vec3(0, -1001, 0), 1000));

        //tracer->GetScene().objects.push_back(std::make_shared<Sphere>(Transform(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(1, 1, 2))));
        //tracer->GetScene().objects.push_back(std::make_shared<Sphere>(Transform(glm::vec3(0, 2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 2, 1))));
        //tracer->GetScene().objects.push_back(std::make_shared<Sphere>(Transform(glm::vec3(2, 0, 0), glm::vec3(0, 0, 0), glm::vec3(2, 1, 1))));
    }


    bool OnUserUpdate(float fElapsedTime) override {
        static int inc = 1;
        // called once per frame
        if (GetKey(olc::SPACE).bPressed) {
            static glm::vec3 pos = { 0, 0, 5 };
            static glm::vec3 rot = { 0, 0, 0 };
            if (GetKey(olc::I).bHeld)
                inc++;
            if (GetKey(olc::O).bHeld && inc > 1)
                inc--;
            if (GetKey(olc::W).bHeld)
                pos.z -= inc;
            if (GetKey(olc::S).bHeld)
                pos.z += inc;
            if (GetKey(olc::A).bHeld)
                pos.x -= inc;
            if (GetKey(olc::D).bHeld)
                pos.x += inc;
            if (GetKey(olc::LEFT).bHeld)
                rot.y += inc;
            if (GetKey(olc::RIGHT).bHeld)
                rot.y -= inc;
            if (GetKey(olc::UP).bHeld)
                rot.x += inc;
            if (GetKey(olc::DOWN).bHeld)
                rot.x -= inc;
            tracer->GetScene().camera = Camera(pos, rot);
            // If we have a scene file we can re-read it and re-render here
            //tracer->Render();
            
            //tracer->RenderParallel();
            //DrawSprite({ 0, 0 }, &tracer->GetRender());
            
            tracer->RenderDepth();
            DrawSprite({ 0, 0 }, &tracer->GetDepth());
        }
        if (GetKey(olc::ESCAPE).bPressed)
            return false;
        return true;
    }

};

int main() {
    App app;
    if (app.Construct(800, 600, 1, 1))
        app.Start();
}