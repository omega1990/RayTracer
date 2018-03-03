#include "../inc/Sphere.hpp"
#include "../inc/Color.hpp"

#define internal static


rt::Sphere::Sphere(
	const Vector<float>& aCenter, 
	const float&		 aRadius,
	const rt::Color&	 aColor)
	: myCenter(aCenter)
	, myRadius(aRadius)
	, Shape(aColor)
{
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
	if (discr < 0) return false;
	else if (discr == 0) x0 = x1 = -0.5 * b / a;
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
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
	double& aOutDistance)
{
	auto ray = aRayVector.Normalize();

	float t0, t1; 
				  
	Vector<float> L = myCenter;
	float a = ray * ray;
	float b = ray * L * 2;
	float c = L * L - (myRadius * myRadius);
	if (!SolveQuadratic(a, b, c, t0, t1)) return false;
	
	if (t0 > t1)
	{
		std::swap(t0, t1);
	}

	if (t0 < 0) {
		t0 = t1; // if t0 is negative, let's use t1 instead 
		if (t0 < 0) return false; // both t0 and t1 are negative 
	}

	aOutDistance = t0;

	return true;
}
