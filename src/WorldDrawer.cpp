
#include "../inc/WorldDrawer.hpp"
#include "../inc/ScopedPerfTracker.h"
#include "../inc/Shading.h"
#include "../inc/Reflection.h"


rt::WorldDrawer::WorldDrawer(
	SDL_Window*		aWindow, 
	SDL_Renderer*	aRenderer, 
	SDL_Texture*	aTexture)
	: myWindow(aWindow)
	, myRenderer(aRenderer)
	, myTexture(aTexture)
{
}

void
rt::WorldDrawer::DrawPixel(
	const rt::Color& aColor,
	const int&		 aX,
	const int&		 aY)
{
	std::lock_guard<std::mutex> lk(myMutex);

	SDL_SetRenderDrawColor(myRenderer, aColor.Red, aColor.Green, aColor.Blue, aColor.Alpha);
	SDL_RenderDrawPoint(myRenderer, aX, aY);
}

void 
rt::WorldDrawer::DrawWorldParallel(
	const rt::Camera&	aCamera,
	uint32				aStart,
	uint32				aEnd)
{
	const rt::Canvas& canvas = aCamera.GetCanvas();
	const rt::World& world = rt::World::GetInstance();

	std::vector<rt::DrawPixel> drawCanvas;

	float closestDistance = 0.f;
	float distance = 0.f;
	float light = 0.f;
	bool hit = false;
	rt::Color color;

	int height = canvas.GetHeight() - (aStart / canvas.GetWidth()) - 1;
	int width = aStart % canvas.GetWidth();

	rt::VectorF rayHitPosition;
	rt::VectorF hitSurfaceNormal;
	Phong phongShading;

	for (uint32 i = aStart; i < aEnd; i++)
	{
		rt::CanvasPixel pixel = canvas.CanvasPixels[i];

		closestDistance = INT_MAX;

		rt::Shape* shapeToDraw = nullptr;

		for (auto&& shape : world.myShapes)
		{
			if (shape->IsIntersecting(rt::Vector<float>(pixel.X, pixel.Y, pixel.Z), aCamera.GetPosition(), distance, rayHitPosition, hitSurfaceNormal))
			{
				if (distance <= closestDistance)
				{
					closestDistance = distance;
					shapeToDraw = shape;
				}				
			}
		}

		if (shapeToDraw)
		{
			color = shapeToDraw->GetColor();

			if (shapeToDraw->GetIsObject())
			{
				phongShading.GetPixelShade(shapeToDraw->GetMaterial(), shapeToDraw, world.myShapes, world.myLightSources, hitSurfaceNormal, rayHitPosition, aCamera.GetPosition(), color);
				Reflection::GetPixelReflection(shapeToDraw->GetMaterial(), shapeToDraw, world.myShapes, world.myLightSources, hitSurfaceNormal, rayHitPosition, aCamera.GetPosition(), color);
			}

			DrawPixel(color, width, height);
		}
		else
		{
			DrawPixel(rt::Color::myPalette[rt::SKY], width, height);
		}

		width++;
		if (width == canvas.GetWidth())
		{
			width = 0;
			height--;
		}
	}
}

void
rt::WorldDrawer::DrawWorld(
	const rt::Camera& aCamera)
{
	ScopedPerfTracker tracker("name");
	const rt::Canvas& canvas = aCamera.GetCanvas();

	myDrawCanvas = {};

	uint8 numberOfThreads = 2;
	const int slice = canvas.CanvasPixels.size() / numberOfThreads;

	// use X threads
	std::vector<std::thread> threads;

	for (uint8 i = 0; i < numberOfThreads; i++)
	{
		threads.push_back(std::thread(std::bind(&rt::WorldDrawer::DrawWorldParallel, this, aCamera, slice * i, (slice * (i + 1)) - 1)));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
}
