#pragma once

#include "Color.hpp"
#include "Vector.hpp"
#include "Shape.hpp"

namespace rt
{
	class Sphere : public Shape
	{
	public:

		Sphere(				const Vector<float>& aCenter,
							const float&		 aRadius,
							const rt::Color&	 aColor);

		bool IsIntersecting(const Vector<float>& aRayVector,
							const Vector<float>& aRayOrigin,
							double&				 aOutDistance) override;

	private:
		Vector<float> myCenter{ 0.0f, 0.0f, 0.0f };
		float myRadius = 5.0f;
	};
}
