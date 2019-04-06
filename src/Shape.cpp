#include "../inc/Shape.hpp"
#include "../inc/LightSource.h"

const rt::Color& 
rt::Shape::GetColor() const
{
	return myColor;
}

bool rt::Shape::IsIntersecting(
	const Vector<float>& aRayVector, 
	const Vector<float>& aRayOrigin, 
	float&				 aOutDistance,
	Vector<float>& aOutHitPosition,
	Vector<float>& aOutSurfaceNormal) const
{
	return false;
}

const Material& rt::Shape::GetMaterial() const
{
	return myMaterial;
}

rt::Shape::Shape()
{
}

rt::Shape::Shape(const Shape&& aShape)
{
	this->myColor = std::move(aShape.myColor);
	this->myMaterial = std::move(aShape.myMaterial);
}

rt::Shape::Shape(
	const Color & aColor)
	: myColor(aColor)
{
}
