#include <cmath>

#include "../inc/Sphere.hpp"
#include "../inc/Color.hpp"

#define internal static

rt::Sphere::Sphere(
	const Vector<float>& aCenter, 
	const float&		 aRadius,
	const rt::Color&	 aColor, 
	const Material&		 aMaterial)
	: myRadius(aRadius)
	, Shape(aCenter, aColor)
{
	static float z = 50.f;
	// TODO
	myMaterial = aMaterial;
}

bool 
rt::Sphere::IsIntersecting(
	const Vector<float>& aRayVector, 
	const Vector<float>& aRayOrigin, 
	float& aOutDistance,
	Vector<float>& aOutHitPosition,
	Vector<float>& aOutSurfaceNormal) const
{
	auto D = aRayVector.Normalize();

	Vector<float> L = myPosition - aRayOrigin;
	float Tca = L * D;
	if (Tca < 0)
	{
		return false; // behind canvas
	}

	float d = sqrtf(powf(L.Length(),2) - powf(Tca, 2));
	if (d > myRadius)
	{
		return false; // no intersection
	}

	float Thc = sqrtf(powf(myRadius, 2) - powf(d,2));
	float t0 = Tca - Thc;
	float t1 = Tca + Thc;
	if (t1 < t0)
	{
		t0 = t1;
	}

	aOutHitPosition = aRayOrigin + D * t0;
	aOutSurfaceNormal = (aOutHitPosition - myPosition).Normalize();

	aOutDistance = (aOutHitPosition - aRayOrigin).Length();

	return true;
}
