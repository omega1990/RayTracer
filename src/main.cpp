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
#include "../inc/Line.hpp"
#include "../inc/LightSource.h"
#include "../inc/DebugHandler.h"
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

	std::cout << "SDL initialized." << SDL_GetError() << std::endl;

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

void GenerateWorld()
{
	rt::World& world = rt::World::GetInstance();
	
	world.AddShape(new rt::Plane(rt::Vector<float>(0.0f, 1.0f, 0.0f), rt::Vector<float>(0.0f, -40.0f, 0.0f), rt::ColorName::DARK_GREY, materials::bronze));

	world.AddShape(new rt::Sphere(rt::Vector<float>(-90.f, 60.f, 55.f), 50.f, rt::COPPER, materials::bronze));
	world.AddShape(new rt::Sphere(rt::Vector<float>(0.f, 90.f, 55.f), 10.f, rt::CHROME, materials::chrome));

	//world.AddShape(new rt::Line(rt::Vector<float>(0.f, 90.f, 55.f), rt::Vector<float>(0.f, 1.0f, 0.f), 100.f, 25.f, rt::ColorName::RED, materials::chrome));

	world.AddLight(new rt::LightSource(rt::Vector<float>(-100.f, 170.f, 30.f), 2.f));
}

int main(int argc, char* argv[])
{
	rt::Camera camera;
	GenerateWorld();

	const rt::World& world = rt::World::GetInstance();

	// Temporary
	float x = 0.f;
	float y = 10.f;
	float z = 50.f;
	float radius = 300.f;
	float angle = 0.f;

	float angle1 = M_PI / 2.f;
	float angle2 = angle1 + M_PI;
	float radius1 = 20.f;

	rt::VectorF positionOne;
	rt::VectorF positionTwo;

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
		
		drawer.DrawWorld(camera);

		SDL_RenderPresent(renderer);
		
		world.myLightSources[0]->myPosition.SetX(x + std::cosf(angle)*radius);
		world.myLightSources[0]->myPosition.SetZ(z + std::sinf(angle)*radius);

		//positionOne = world->myShapes[1]->GetPosition();
		//positionOne.SetX(positionOne.GetX() + std::cosf(angle1) * radius1);
		//positionOne.SetZ(positionOne.GetZ() + std::sinf(angle1) * radius1);
		//world->myShapes[1]->SetPosition(positionOne);

		//positionTwo = world->myShapes[2]->GetPosition();
		//positionTwo.SetX(positionTwo.GetX() + std::cosf(angle2) * radius1);
		//positionTwo.SetZ(positionTwo.GetZ() + std::sinf(angle2) * radius1);
		//world->myShapes[2]->SetPosition(positionTwo);

		angle -= 0.05f;
		angle1 += 0.1f;
		angle2 = angle1 + 3.14f;

		//world.myLightSources[1].myPosition.SetX(z + std::cosf(angle1)*radius);
		//world.myLightSources[1].myPosition.SetZ(z + std::sinf(angle1)*radius);
	}

	/* Shutdown all subsystems */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}