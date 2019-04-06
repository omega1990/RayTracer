#pragma once

#include "Color.hpp"
#include "Vector.hpp"
#include "Shape.hpp"
#include "Material.h"

namespace rt
{
	class Sphere : public Shape
	{
	public:

		Sphere(				const Vector<float>& aCenter,
							const float&		 aRadius,
							const rt::Color&	 aColor,
							const Material&		 aMaterial);

		bool IsIntersecting(const Vector<float>& aRayVector,
							const Vector<float>& aRayOrigin,
							float&				 aOutDistance,
							Vector<float>& aOutHitPosition,
							Vector<float>& aSurfaceNormal) const override;

	private:
		float myRadius = 5.0f;
	};
}
