#pragma once

#include "Color.hpp"
#include "Vector.hpp"

namespace rt
{
	class Shape
	{
	public:
		const Color& GetColor() const;

		virtual bool IsIntersecting(
			const Vector<float>& aRayVector,
			const Vector<float>& aRayOrigin,
			double&				 aOutDistance);

	protected:
		Shape();
		Shape(const Color& aColor);
		Color myColor{ 0, 0, 0, 255 };
	};
}