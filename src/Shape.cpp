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

const rt::VectorF& rt::Shape::GetPosition() const
{
	return myPosition;
}

const void rt::Shape::SetPosition(const rt::VectorF& aPosition)
{
	myPosition = aPosition;
}

rt::Shape::Shape(const VectorF& aPosition)
	: myPosition(aPosition)
{
}

rt::Shape::Shape(const Shape&& aShape)
{
	this->myColor = std::move(aShape.myColor);
	this->myMaterial = std::move(aShape.myMaterial);
	this->myPosition = std::move(aShape.myPosition);
}

rt::Shape::Shape(
	const VectorF& aPosition,
	const Color & aColor)
	: myColor(aColor)
	, myPosition(aPosition)
{
}
