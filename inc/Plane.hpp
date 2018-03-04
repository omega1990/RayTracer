#pragma once

#include "Vector.hpp"
#include "Shape.hpp"

namespace rt
{
	class Plane : public Shape
	{
	public:
		Plane();

		Plane(				const Vector<float>& aNorm, 
							const Vector<float>& aPoint, 
							const Color& aColor);

		Plane(				const Color & aColor);

		bool IsIntersecting(const Vector<float>& aRayVector,
							const Vector<float>& aRayOrigin,
							double&				 aOutDistance,
							double&				 aLight) override;
	private:
		Vector<float> myNormalVector{ 0.0f, 1.0f, 0.0f };
		Vector<float> myPoint{ 0.0f, 0.0f, 0.0f };
	};

}