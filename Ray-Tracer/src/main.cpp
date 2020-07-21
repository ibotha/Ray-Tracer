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
		RayTracer tracer(scene);
		tracer.render();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand() % 255));
		return true;
	}
};

int main()
{
	App app;
	if (app.Construct(256, 240, 4, 4))
		app.Start();
}