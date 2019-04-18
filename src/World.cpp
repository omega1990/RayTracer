#include "../inc/World.hpp"

rt::World::~World()
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

void rt::World::AddLight(rt::LightSource* aLightSource)
{
	myLightSources.push_back(std::move(aLightSource));
}