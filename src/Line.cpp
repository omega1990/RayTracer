#include <cmath>

#include "../inc/Line.hpp"
#include "../inc/Color.hpp"

#define internal static

rt::Line::Line(
	const rt::VectorF&	 aStartPoint,
	const rt::VectorF&	 aDirection,
	const float			 aMagnitude,
	const float 		 aThickness, 
	const rt::Color&	 aColor,
	const Material&		 aMaterial)
	: myThickness(aThickness)
	, myStartPoint(aStartPoint)
	, myDirectionN(aDirection.Normalize())
	, myMagnitude(aMagnitude)
	, Shape(aStartPoint, aColor, false)
{
	myMaterial = aMaterial;

	myHeightVector = myDirectionN * myMagnitude;
}

bool 
rt::Line::IsIntersecting(
	const VectorF& aRayVector, 
	const VectorF& aRayOrigin, 
	float& aOutDistance,
	VectorF& aOutHitPosition,
	VectorF& aOutSurfaceNormal) const
{
	const VectorF rayN = (myStartPoint - aRayOrigin).Normalize();
	const VectorF spreadVector = rayN.Cross(myDirectionN).Normalize();
	const VectorF surfaceNormal = aRayVector.Normalize() * (-1);

	// Plane intersection
	const float denominator = aRayVector.Normalize() * surfaceNormal;
	if (denominator > 0)
		return false;

	const float hitDistance = (VectorF(myStartPoint - aRayOrigin) * surfaceNormal) / denominator;
	const VectorF hitPosition = aRayOrigin + (aRayVector.Normalize() * hitDistance);

	const VectorF heightVector = myStartPoint * myMagnitude;
	const VectorF widthVector = spreadVector * myThickness;
	const VectorF hitPositionVector = hitPosition - myStartPoint;

	float projectionLength = (hitPositionVector * widthVector) / widthVector.Length();
	if (projectionLength > widthVector.Length() || projectionLength < 0.f)
		return false;
	projectionLength = (hitPositionVector * heightVector) / heightVector.Length();
	if (projectionLength > widthVector.Length() || projectionLength < 0.f)
		return false;

	/*const VectorF hitVector = hitPosition - myStartPoint;
	const float hitVectorProjectionLen = hitVector * myHeightVector;
	if (hitVectorProjectionLen > myHeightVector.Length() || hitVectorProjectionLen < 0.f)
		return false;*/

	aOutHitPosition = hitPosition;
	aOutDistance = hitDistance;
	aOutSurfaceNormal = surfaceNormal;

	return true;
}
