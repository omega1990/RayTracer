#pragma once

#include "Vector.hpp"

namespace rt
{

class LightSource
{
public:
	LightSource(const rt::Vector<float>& aPosition, float aIntensity);
	~LightSource();

	rt::Vector<float> myPosition;
	float myIntensity;
};

}

