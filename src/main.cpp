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
#include "../inc/LightSource.h"
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

rt::World
GenerateWorld()
{
	rt::World world;
	rt::Shape* plane1 = new rt::Plane(rt::Vector<float>(0.0f, 1.0f, 0.0f), rt::Vector<float>(0.0f, -40.0f, 0.0f), rt::ColorName::DARK_GREY, materials::bronze);
	rt::Shape* sphere1 = new rt::Sphere(rt::Vector<float>(90.f, 60.f, 55.f), 50.f, rt::CHROME, materials::chrome);
	rt::Shape* sphere2  = new rt::Sphere(rt::Vector<float>(-90.f, 60.f, 55.f), 50.f, rt::COPPER, materials::bronze);
	/*rt::Plane plane2(rt::Vector<float>(-1.0f, 0.0f, 0.0f), rt::Vector<float>(150.0f, 0.0f, 0.0f), rt::ColorName::GREY);
	rt::Plane plane3(rt::Vector<float>(1.0f, 0.0f, 0.0f), rt::Vector<float>(-150.0f, 0.0f, 0.0f), rt::ColorName::GREY);
	rt::Plane plane4(rt::Vector<float>(0.0f, -1.0f, 0.0f), rt::Vector<float>(0.0f, 300.0f, 0.0f), rt::ColorName::GREY);
	rt::Plane plane5(rt::Vector<float>(0.0f, 0.0f, 1.0f), rt::Vector<float>(0.0f, 0.0f, 470.0f), rt::ColorName::GREY);
*/
	world.AddShape(plane1);
	//world.AddShape(plane2);
	//world.AddShape(plane3);
	//world.AddShape(plane4);
	//world.AddShape(plane5);

	rt::LightSource light(rt::Vector<float>(-100.f, 170.f, 30.f), 2.f);

	//rt::LightSource light2(rt::Vector<float>(-100.f, 170.f, 30.f), 20.f);


	world.AddShape(sphere1);
	world.AddShape(sphere2);
	world.AddLight(light);
	//world.AddLight(light2);


	return std::move(world);
}

int main(int argc, char* argv[])
{
	rt::Camera camera;
	rt::World world = GenerateWorld();

	// Temporary
	float x = 0.f;
	float y = 10.f;
	float z = 50.f;
	float radius = 300.f;
	float angle = 0.f;

	float x1 = 0.f;
	float y1 = 10.f;
	float z1 = 50.f;
	float radius1 = 300.f;
	float angle1 = 90.f;



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
		
		drawer.DrawWorld(camera, world);

		SDL_RenderPresent(renderer);
		
		angle -= 0.1f;
		angle1 -= 0.1f;

		world.myLightSources[0].myPosition.SetX(x + std::cosf(angle)*radius);
		world.myLightSources[0].myPosition.SetZ(z + std::sinf(angle)*radius);

		//world.myLightSources[1].myPosition.SetX(z + std::cosf(angle1)*radius);
		//world.myLightSources[1].myPosition.SetZ(z + std::sinf(angle1)*radius);
	}

	/* Shutdown all subsystems */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}