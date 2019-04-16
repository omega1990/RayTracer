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
	, myDirection(aDirection)
	, myMagnitude(aMagnitude)
	, Shape(aStartPoint, aColor, false)
{
	myMaterial = aMaterial;
}

bool 
rt::Line::IsIntersecting(
	const VectorF& aRayVector, 
	const VectorF& aRayOrigin, 
	float& aOutDistance,
	VectorF& aOutHitPosition,
	VectorF& aOutSurfaceNormal) const
{
	////VectorF endPoint = myStartPoint + (myDirection * myMagnitude);

	//const VectorF spreadVectorN = myDirection.Cross(aRayVector).Normalize();

	////bool isIntersecting = false;
	//float result = 0.f;

	///*for (int i = -myThickness / 2; i < myThickness / 2; i++)
	//{*/
	//	result = aRayVector.Cross(myDirection) * (aRayOrigin - myStartPoint);

	//	if (abs(result) > 0 + 0.000005f)
	//		return false;

	//	aOutHitPosition = myStartPoint + (myDirection * result);
	//	aOutDistance = (aOutHitPosition - aRayOrigin).Length();
	//	aOutSurfaceNormal = aRayVector.Cross(myDirection);
	//	return true;

	////}
	////

	////return isIntersecting;

	const auto ray = aRayVector.Normalize();

	VectorF lineSurfaceSpreadVector = aRayVector.Cross(myDirection).Normalize();
	const VectorF surfaceNormal = lineSurfaceSpreadVector.Cross(myDirection);
	
	float projection = ray * surfaceNormal;
	if (projection > 0)
		return false;


	const float hitDistance = (surfaceNormal * (myPosition - aRayOrigin)) / (surfaceNormal * ray);
	const VectorF hitPosition = aRayOrigin + (ray * hitDistance);


	//const VectorF minHeight = myStartPoint;
	//const VectorF maxHeight = myStartPoint + (myDirection * myMagnitude);
	//const VectorF heightVector = maxHeight - minHeight;
	//const float heightCheck = abs((hitPosition - myStartPoint) * heightVector);
	//if (heightCheck > heightVector.Length())
	//	return false;


	const VectorF minWidth = myStartPoint - (lineSurfaceSpreadVector.Abs() * myThickness);
	const VectorF maxWidth = myStartPoint + (lineSurfaceSpreadVector.Abs() * myThickness);
	const VectorF widthVector = maxWidth - minWidth;
	const float widthCheck = abs((hitPosition - myStartPoint) * (widthVector / 2));
	if (widthCheck > widthVector.Length())
		return false;


	aOutHitPosition = hitPosition;
	aOutDistance = hitDistance;
	aOutSurfaceNormal = surfaceNormal;

	//return true;

	return true;
}
