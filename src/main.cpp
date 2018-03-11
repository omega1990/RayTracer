#include <iostream>
#include <float.h>
#include <memory>
#include <thread>

#include "SDL.h" 

#include "../inc/Vector.hpp"
#include "../inc/Plane.hpp"
#include "../inc/Sphere.hpp"
#include "../inc/Camera.hpp"
#include "../inc/World.hpp"
#include "../inc/WorldDrawer.hpp"
#include "../inc/main.hpp"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* screenTexture;

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
		DEFAULT_CANVAS_HEIGHT,
		DEFAULT_CANVAS_WIDTH,
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

std::shared_ptr<rt::World> 
GenerateWorld()
{
	rt::World world;
	rt::Plane plane1(rt::ColorName::GREY);
	rt::Sphere sphere1(rt::Vector<float>(0.0f, 10.0f, 50.0f), 70.0f, rt::SPHERE);
	rt::Plane plane2(rt::Vector<float>(-1.0f, 0.0f, 0.0f), rt::Vector<float>(150.0f, 0.0f, 0.0f), rt::ColorName::GREY);
	rt::Plane plane3(rt::Vector<float>(1.0f, 0.0f, 0.0f), rt::Vector<float>(-150.0f, 0.0f, 0.0f), rt::ColorName::GREY);
	rt::Plane plane4(rt::Vector<float>(0.0f, -1.0f, 0.0f), rt::Vector<float>(0.0f, 300.0f, 0.0f), rt::ColorName::GREY);
	rt::Plane plane5(rt::Vector<float>(0.0f, 0.0f, 1.0f), rt::Vector<float>(0.0f, 0.0f, 470.0f), rt::ColorName::GREY);

	world.AddShape(plane1);
	world.AddShape(plane2);
	world.AddShape(plane3);
	world.AddShape(plane4);
	world.AddShape(plane5);
	world.AddShape(sphere1);

	return std::make_shared<rt::World>(world);
}

int main(int argc, char* argv[])
{
	rt::Camera camera;
	std::shared_ptr<rt::World> world = GenerateWorld();


	// Rendering 
	bool retflag;
	int retval = SDLInit(retflag);
	if (retflag) return retval;

	screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, camera.GetCanvas().GetWidth(), camera.GetCanvas().GetHeight());
	rt::WorldDrawer drawer(window, renderer, screenTexture);

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
				case SDLK_LEFT:
					camera.MoveLeft(0.05f);
					break;
				case SDLK_RIGHT:
					camera.MoveRight(0.05f);
					break;
				default:
					break;
				}
			}
		}
		
		drawer.DrawWorld(camera, *world);

		SDL_RenderPresent(renderer);

		// Add a 16msec delay to make our game run at ~60 fps
		// SDL_Delay(16);
	}

	/* Shutdown all subsystems */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}