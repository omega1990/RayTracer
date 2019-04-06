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

		template <typename T>
		void AddShape(T* aShape);

		void AddLight(const rt::LightSource& aLightSource)
		{
			myLightSources.push_back(aLightSource);
		}

		std::vector<rt::Shape*> myShapes = {};
		std::vector<rt::LightSource> myLightSources = {};
	};
}


template <typename T>
void
rt::World::AddShape(
	T* aShape)
{
	myShapes.push_back(std::move(aShape));
}
