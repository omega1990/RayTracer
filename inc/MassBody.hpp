#pragma once

#include "Color.hpp"
#include "Vector.hpp"
#include "LightSource.h"
#include "Material.h"

namespace rt
{
class MassBody
{
public:
	MassBody(float aGravityForce, float aGravitySphereRadius, const VectorF& aGravityCenter);

private:
	float myGravityForce;
	float myGravitySphereRadius;
	rt::VectorF myGravityCenter;

};
}