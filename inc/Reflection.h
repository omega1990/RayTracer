#pragma once

#include "Color.hpp"
#include "LightSource.h"
#include "Vector.hpp"
#include "Material.h"
#include "Shape.hpp"

#include <vector>

class Reflection
{
public:
	Reflection();
	~Reflection();

	static void GetPixelReflection(
		const Material& aMaterial, const rt::Shape* aShape, const std::vector<rt::Shape*>& aShapes, const std::vector<rt::LightSource*>& aLightSources, const rt::VectorF& aPixelNormal, const rt::VectorF& aHitPosition, const rt::VectorF& aCameraPosition, rt::Color& aOutColor, int aRecursionStep = 0);
};