#pragma once

#include "Color.hpp"
#include "Vector.hpp"
#include "Shape.hpp"
#include "Material.h"
#include "DebugEntity.h"

namespace rt
{
class Line : public Shape, public DebugEntity
{
public:

	Line(				const VectorF&		 aStartPoint,
						const VectorF&		 aDirection,
						const float			 aMagnitude,
						const float 		 aThickness,
						const rt::Color&	 aColor,
						const Material&		 aMaterial);

	~Line() override {};

	bool IsIntersecting(const VectorF&		 aRayVector,
						const VectorF&		 aRayOrigin,
						float&				 aOutDistance,
						VectorF&			 aOutHitPosition,
						VectorF&			 aSurfaceNormal) const override;

private:
	float myThickness = 5.0f;
	float myMagnitude;
	VectorF myStartPoint;
	VectorF myDirectionN;
	VectorF myHeightVector;
	VectorF myWidthVector;
};
}
