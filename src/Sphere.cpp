#include <cmath>

#include "../inc/Sphere.hpp"
#include "../inc/Color.hpp"

#define internal static

rt::Sphere::Sphere(
	const Vector<float>& aCenter, 
	const float&		 aRadius,
	const rt::Color&	 aColor, 
	const Material&		 aMaterial)
	: myCenter(aCenter)
	, myRadius(aRadius)
	, Shape(aColor)
{
	static float z = 50.f;
	// TODO
	myMaterial = aMaterial;
}

internal 
bool SolveQuadratic(
	const float&a, 
	const float&b, 
	const float&c, 
	float& x0, 
	float& x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0)
	{
		return false;
	}
	else if (discr == 0)
	{
		x0 = x1 = -0.5 * b / a;
	}
	else 
	{
		float q = (b > 0) ?
			-0.5f * (b + sqrt(discr)) :
			-0.5f * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);

	return true;
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
				  
	Vector<float> L = myCenter - aRayOrigin;
	float Tca = L * D;
	if (Tca < 0)
	{
		return false;
	}

	float d = sqrtf((L*L) - (Tca*Tca));
	if (d > myRadius)
	{
		return false;
	}

	float Thc = sqrtf(myRadius * myRadius - d * d);
	float t0 = Tca - Thc;
	float t1 = Tca + Thc;
	if (t1 < t0)
	{
		t0 = t1;
	}

	aOutHitPosition = aRayOrigin + D * t0;
	aOutSurfaceNormal = (aOutHitPosition - myCenter).Normalize();

	return true;
}
