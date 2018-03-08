#include <iostream>

#include "SDL.h" 

#include "../inc/Vector.hpp"
#include "../inc/Plane.hpp"
#include "../inc/Sphere.hpp"
#include "../inc/Camera.hpp"
#include "../inc/World.hpp"
#include "../inc/main.hpp"

SDL_Window* window;
SDL_Renderer* renderer;

int 
SDLInit(
	bool &retflag)
{
	retflag = true;
	if ((SDL_Init(SDL_INIT_VIDEO) == -1))
	{
		std::cout << "Could not initialize SDL:" << SDL_GetError() << std::endl;
		return -1;
	}

	std::cout << "SDL initalized." << SDL_GetError() << std::endl;

	if (SDL_CreateWindowAndRenderer(
		static_cast<int>(DEFAULT_CANVAS_HEIGHT),
		static_cast<int>(DEFAULT_CANVAS_WIDTH),
		0,
		&window,
		&renderer) == -1)
	{
		std::cout << "Could not create window and renderer" << SDL_GetError() << std::endl;
		return -1;
	}

	retflag = false;
	return {};
}

int 
CreateRenderer(
	bool &retflag)
{
	retflag = true;
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == nullptr)
	{
		std::cout << "Failed to create renderer : " << SDL_GetError();
		return 1;
	}

	retflag = false;
	return {};
}

void 
DrawPixel(
	const rt::Color& aColor, 
	const int& aX, 
	const int& aY)
{
	SDL_SetRenderDrawColor(renderer, aColor.Red, aColor.Green, aColor.Blue, aColor.Alpha);
	SDL_RenderDrawPoint(renderer, aX, aY);
}

int main(int argc, char* argv[])
{
	rt::Camera camera;
	rt::World world;
	rt::Plane plane1(rt::ColorName::GREY);
	rt::Sphere sphere1(rt::Vector<float>(0.0f, 20.0f, -150.0f), 10.0f, rt::SPHERE);
	rt::Plane plane2(rt::Vector<float>(-5.0f, 0.0f, 0.0f), rt::Vector<float>(150.0f, 0.0f, 0.0f), rt::ColorName::GREY);
	rt::Plane plane3(rt::Vector<float>(5.0f, 0.0f, 0.0f), rt::Vector<float>(-150.0f, 0.0f, 0.0f), rt::ColorName::GREY);
	rt::Plane plane4(rt::Vector<float>(0.0f, -1.0f, 0.0f), rt::Vector<float>(0.0f, 300.0f, 0.0f), rt::ColorName::GREY);
	rt::Plane plane5(rt::Vector<float>(0.0f, 0.0f, 1.0f), rt::Vector<float>(0.0f, 0.0f, 470.0f), rt::ColorName::GREY);
	world.myShapes.push_back(&plane1);
	world.myShapes.push_back(&plane2);
	world.myShapes.push_back(&plane3);
	world.myShapes.push_back(&plane4);
	world.myShapes.push_back(&plane5);
	world.myShapes.push_back(&sphere1);


	bool retflag;
	int retval = SDLInit(retflag);
	if (retflag) return retval;

	bool loop = true;
	while (loop)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = false;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					camera.MoveUp(0.05f);
					break;
				case SDLK_DOWN:
					camera.MoveDown(0.05f);
					break;
				default:
					break;
				}
			}
		}

		const rt::Canvas& canvas = camera.GetCanvas();
		double distance = 0;

		int width = 0;
		int height = static_cast<int>(canvas.GetHeight()) - 1;

		auto cameraPosition = camera.GetPosition();

		// I need camera axes in terms of world coordinates
		rt::Vector<float> yCameraAxis = camera.GetDirection().Cross(camera.GetTilt());
		float x, y, z;

		for (const auto& pixel : canvas.CanvasPixels)
		{
			// Before using the canvas pixels, its coordinates need to be translated
			// to the world's coordinates 
			x = camera.GetTilt().GetX() * pixel.X + yCameraAxis.GetX() * pixel.Y + camera.GetDirection().GetX() * pixel.Z;
			y = camera.GetTilt().GetY() * pixel.X + yCameraAxis.GetY() * pixel.Y + camera.GetDirection().GetY() * pixel.Z;
			z = camera.GetTilt().GetZ() * pixel.X + yCameraAxis.GetZ() * pixel.Y + camera.GetDirection().GetZ() * pixel.Z;

			double closestDistance = DBL_MAX;
			double light;

			bool hit = false;
			for (auto& shape : world.myShapes)
			{
				if (shape->IsIntersecting(rt::Vector<float>(x, y, z), camera.GetPosition(), distance, light))
				{
					if (distance > closestDistance)
					{
						continue;
					}

					closestDistance = distance;

					auto color = shape->GetColor() * light + (distance / 8) ;
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
	
		// TODO: Clearing
		SDL_RenderPresent(renderer);

		// Add a 16msec delay to make our game run at ~60 fps
		SDL_Delay(16);
	}

	/* Shutdown all subsystems */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}