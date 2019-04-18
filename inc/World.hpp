#pragma once

#include "Singleton.h"
#include "Shape.hpp"
#include "SDL.h"
#include "LightSource.h"

#include <memory>


namespace rt
{

class World : public Singleton<World>
{
	friend class Singleton<World>;

public:
	template <typename T>
	void AddShape(T* aShape);

	void AddLight(rt::LightSource* aLightSource);

	std::vector<rt::Shape*> myShapes = {};
	std::vector<rt::LightSource*> myLightSources = {};

private:
	World(){};
	~World();

public:
	World(const World&) = delete;
	void operator=(const World&) = delete;
};

}

template <typename T>
void rt::World::AddShape(T* aShape)
{
	myShapes.push_back(std::move(aShape));
}
