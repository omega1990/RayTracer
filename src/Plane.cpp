#include <cmath> 

#include "../inc/Plane.hpp"

rt::Plane::Plane()
{
}

rt::Plane::Plane(
	const Vector<float>& aNorm, 
	const Vector<float>& aPoint, 
	const Color&		 aColor)
	: myNormalVector(aNorm)
	, myPoint(aPoint)
	, Shape(aColor)
{
}

rt::Plane::Plane(
	const Color&		 aColor)
	: Shape(aColor)
{
}

bool 
rt::Plane::IsIntersecting(
	const Vector<float>& aRayVector, 
	const Vector<float>& aRayOrigin,
	double&				 aOutDistance)
{
	auto line = aRayVector + aRayOrigin;
	auto normal = myNormalVector.Normalize();
	auto ray = aRayVector.Normalize();	

	float denom = normal * ray;
	if (std::abs(denom) > 1e-6) // How far do I want to display this 
	{
		Vector<float> p0l0 = myPoint - aRayOrigin;
		aOutDistance = p0l0 * normal / denom;
		return (aOutDistance >= 0);
	}

	return false;
}
