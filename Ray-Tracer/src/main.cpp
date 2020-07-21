#include "RayTracer.h"

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
		Scene scene;
		//populate scene here
		tracer = new RayTracer(scene, ScreenWidth(), ScreenHeight());
		tracer->render();
		DrawSprite({0, 0}, &tracer->GetRender());
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		if (GetKey(olc::SPACE).bHeld)
		{
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