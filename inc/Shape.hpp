#pragma once

#include "Color.hpp"
#include "Vector.hpp"
#include "LightSource.h"
#include "Material.h"

namespace rt
{
	class Shape
	{
	public:
		const Color& GetColor() const;

		virtual bool IsIntersecting(
			const Vector<float>& aRayVector,
			const Vector<float>& aRayOrigin,
			float&				 aOutDistance,
			Vector<float>& aOutHitPosition,
			Vector<float>& aOutSurfaceNormal) const;

		const Material& GetMaterial() const;

	protected:
		Shape();
		Shape(const Shape&& aShape);

		Shape(const Color& aColor);
		Color myColor{ 0, 0, 0, 255 };
		Material myMaterial{ 1.f, 1.f, 1.f, 1.f };
	};
}