#include "../inc/WorldDrawer.hpp"


rt::WorldDrawer::WorldDrawer(
	SDL_Window*		aWindow, 
	SDL_Renderer*	aRenderer)
	: myWindow(aWindow)
	, myRenderer(aRenderer)
{
}

void
rt::WorldDrawer::DrawPixel(
	const rt::Color& aColor,
	const int&		 aX,
	const int&		 aY)
{
	std::scoped_lock<std::mutex> lock(myMutex);

	SDL_SetRenderDrawColor(myRenderer, aColor.Red, aColor.Green, aColor.Blue, aColor.Alpha);
	SDL_RenderDrawPoint(myRenderer, aX, aY);
}

void
rt::WorldDrawer::DrawWorldParallel(
	const rt::Camera&	aCamera,
	const rt::World&	aWorld,
	const uint32&		aStart,
	const uint32&		aEnd)
{
	const rt::Canvas& canvas = aCamera.GetCanvas();

	double		closestDistance = 0;
	double		distance = 0;
	double		light = 0;
	bool		hit = false;
	rt::Color	color;

	int height = canvas.GetHeight() - (aStart / canvas.GetWidth()) - 1;
	int width = aStart % canvas.GetWidth();


	for (uint32 i = aStart; i < aEnd; i++)
	{
		rt::CanvasPixel pixel = canvas.CanvasPixels[i];

		closestDistance = DBL_MAX;

		hit = false;
		for (auto& shape : aWorld.myShapes)
		{
			if (shape->IsIntersecting(rt::Vector<float>(pixel.X, pixel.Y, pixel.Z), aCamera.GetPosition(), distance, light))
			{
				if (distance > closestDistance)
				{
					continue;
				}

				closestDistance = distance;

				color = shape->GetColor() * light + (distance / 8);
				DrawPixel(color, width, height);

				hit = true;
			}
		}

		if (!hit)
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
	const rt::Camera& aCamera,
	const rt::World& aWorld)
{
	auto a = SDL_GetTicks();

	const rt::Canvas& canvas = aCamera.GetCanvas();

	uint8 numberOfThreads = 4;
	int slice = canvas.CanvasPixels.size() / numberOfThreads;

	// use X threads
	std::vector<std::thread> threads;
	for (uint8 i = 0; i < numberOfThreads; i++)
	{
		threads.push_back(std::thread(std::bind(&rt::WorldDrawer::DrawWorldParallel, this, aCamera, aWorld, slice * i, (slice * (i + 1)) - 1)));
	}

	for (auto& thread : threads)
	{
		thread.join();
	}

	//DrawWorldParallel(aCamera, aWorld, 0, canvas.CanvasPixels.size());

	auto b = SDL_GetTicks();
	std::cout << b - a << std::endl;
}
