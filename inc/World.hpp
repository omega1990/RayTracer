#pragma once

#include "Shape.hpp"

namespace rt
{
	class World
	{
	public:
		std::vector<Shape*> myShapes = {};
	};
}