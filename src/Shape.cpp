#include "../inc/Shape.hpp"

const rt::Color& 
rt::Shape::GetColor() const
{
	return myColor;
}

bool rt::Shape::IsIntersecting(
	const Vector<float>& aRayVector, 
	const Vector<float>& aRayOrigin, 
	double&				 aOutDistance,
	double&				 aLight)
{
	return false;
}

rt::Shape::Shape()
{
}

rt::Shape::Shape(
	const Color & aColor)
	:myColor(aColor)
{
}
