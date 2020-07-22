#include "RayTracer.h"
#include "Sphere.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class App : public olc::PixelGameEngine
{
public:
	App()
	{
		sAppName = "Ray-Tracer";
	}

public:
	bool OnUserCreate() override
	{
		//populate scene here
		tracer = new RayTracer(ScreenWidth(), ScreenHeight());
		tracer->GetScene().camera = Camera({ 0, 0, 3 }, { 0, 0, 0 });
		tracer->GetScene().objects.push_back(std::make_shared<Sphere>(Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(2, 2, 2))));
		tracer->GetScene().objects.push_back(std::make_shared<Sphere>(Transform(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(1, 1, 2))));
		tracer->GetScene().objects.push_back(std::make_shared<Sphere>(Transform(glm::vec3(0, 2, 0), glm::vec3(0, 0, 0), glm::vec3(1, 2, 1))));
		tracer->GetScene().objects.push_back(std::make_shared<Sphere>(Transform(glm::vec3(2, 0, 0), glm::vec3(0, 0, 0), glm::vec3(2, 1, 1))));
		tracer->render();
		DrawSprite({0, 0}, &tracer->GetRender());
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		if (GetKey(olc::SPACE).bPressed)
		{
			static glm::vec3 pos = {0, 0, 3};
			static glm::vec3 rot = { 0, 0, 0 };
			if (GetKey(olc::W).bHeld)
				pos.z -= 1;
			if (GetKey(olc::S).bHeld)
				pos.z += 1;
			if (GetKey(olc::A).bHeld)
				pos.x -= 1;
			if (GetKey(olc::D).bHeld)
				pos.x += 1;
			if (GetKey(olc::LEFT).bHeld)
				rot.y += 1;
			if (GetKey(olc::RIGHT).bHeld)
				rot.y -= 1;
			if (GetKey(olc::UP).bHeld)
				rot.x += 1;
			if (GetKey(olc::DOWN).bHeld)
				rot.y -= 1;
			tracer->GetScene().camera = Camera(pos, rot);
			// If we have a scene file we can re-read it and re-render here
			tracer->render();
			DrawSprite({ 0, 0 }, &tracer->GetRender());
		}
		if (GetKey(olc::ESCAPE).bPressed)
			return false;
		return true;
	}
private:
	RayTracer* tracer;
};

int main()
{
	App app;
	if (app.Construct(480, 360, 1, 1))
		app.Start();
}