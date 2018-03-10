#pragma once

#include <memory>

#include "Shape.hpp"

namespace rt
{
	class World
	{
	public:
		template <typename T>
		void AddShape(const T& aShape);

		std::vector<std::shared_ptr<Shape>> myShapes = {};
	};
}


template <typename T>
void
rt::World::AddShape(
	const T& aShape)
{
	myShapes.push_back(std::make_shared<T>(aShape));
}
