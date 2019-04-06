#pragma once

#include "Shape.hpp"
#include "SDL.h"
#include "LightSource.h"

#include <memory>


namespace rt
{
	class World
	{
	public:
		World() {};
		World(const World& world)
		{
			myShapes = world.myShapes;
			myLightSources = world.myLightSources;
		}
		World(World&& world)
		{
			myShapes = std::move(world.myShapes);
			myLightSources = std::move(world.myLightSources);
		}

		~World()
		{
			for (auto& shape : myShapes)
			{
				delete shape;
				shape = nullptr;
			}

			for (auto& light : myLightSources)
			{
				delete light;
				light = nullptr;
			}
		}

		template <typename T>
		void AddShape(T* aShape);

		void AddLight(rt::LightSource* aLightSource)
		{
			myLightSources.push_back(std::move(aLightSource));
		}

		std::vector<rt::Shape*> myShapes = {};
		std::vector<rt::LightSource*> myLightSources = {};
	};
}


template <typename T>
void rt::World::AddShape(T* aShape)
{
	myShapes.push_back(std::move(aShape));
}
