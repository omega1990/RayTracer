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
		const VectorF& GetPosition() const;
		const void SetPosition(const VectorF& aPosition);
		bool GetIsObject() const;

	protected:
		Shape(const VectorF& aPosition);
		Shape(const VectorF& aPosition, const Color& aColor, bool aIsObject = true);
		Shape(const Shape&& aShape);

		Color myColor{ 0, 0, 0, 255 };
		Material myMaterial{ 1.f, 1.f, 1.f, 1.f };
		VectorF myPosition;
		bool myIsObject;
	};
}