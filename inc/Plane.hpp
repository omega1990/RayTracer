#pragma once

#include "Vector.hpp"
#include "Shape.hpp"
#include "Material.h"

namespace rt
{
	class Plane : public Shape
	{
	public:
		Plane();

		Plane(				const Vector<float>& aNorm, 
							const Vector<float>& aPoint, 
							const Color& aColor,
							const Material& aMaterial);

		Plane(				const Color & aColor,
							const Material& aMaterial);

		bool IsIntersecting(const Vector<float>& aRayVector,
							const Vector<float>& aRayOrigin,
							float&				 aOutDistance,
							Vector<float>& aOutHitPosition,
							Vector<float>& aOutSurfaceNormal) const override;
	private:
		Vector<float> myNormalVector{ 0.0f, 1.0f, 0.0f };
		Vector<float> myPoint{ 0.0f, 0.0f, 0.0f };
	};

}