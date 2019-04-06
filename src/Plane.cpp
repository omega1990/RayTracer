#include <cmath> 

#include "../inc/Plane.hpp"

rt::Plane::Plane(const Vector<float>& aPoint)
	:Shape(aPoint)
{
}

rt::Plane::Plane(
	const Vector<float>& aNorm, 
	const Vector<float>& aPoint, 
	const Color&		 aColor, 
	const Material&		 aMaterial)
	: myNormalVector(aNorm)
	, Shape(aPoint, aColor)
{
	myMaterial = aMaterial;
	myPosition = aPoint;
}

//rt::Plane::Plane(
//	const Color& aColor,
//	const Material& aMaterial)
//	: Shape(aColor)
//{
//	myMaterial = aMaterial;
//}

bool 
rt::Plane::IsIntersecting(
	const Vector<float>& aRayVector, 
	const Vector<float>& aRayOrigin,
	float&				 aOutDistance,
	Vector<float>& aOutHitPosition,
	Vector<float>& aOutSurfaceNormal) const
{
	//auto line = aRayVector + aRayOrigin;
	aOutSurfaceNormal = myNormalVector;
	const auto ray = aRayVector.Normalize();	

	float denom = aOutSurfaceNormal * ray;
	if (std::abs(denom) > 1e-6) // How far do I want to display this 
	{
		// Compute the X value for the directed line ray intersecting the plane
		//const float d = aOutSurfaceNormal * myPoint;
		//const float x = (d - (aOutSurfaceNormal * aRayOrigin)) / (aOutSurfaceNormal * aRayVector);
		//// output contact point
		//aOutHitPosition = aRayOrigin + ray * x; //Make sure your ray vector is normalized
		//aOutDistance = (aOutHitPosition - aRayOrigin).Length();

		////aOutDistance = p0l0 * aOutSurfaceNormal / denom;

		aOutDistance = (aOutSurfaceNormal * (myPosition - aRayOrigin)) / (aOutSurfaceNormal * ray);
		aOutHitPosition = aRayOrigin + (ray * aOutDistance);

		const VectorF p0l0 = aOutHitPosition - aRayOrigin;
		float t = (p0l0 * aOutSurfaceNormal) / denom;
		return (t >= 0);
	}

	
	return false;
}
