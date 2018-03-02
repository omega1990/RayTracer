#include "../inc/Point.hpp"

rt::CanvasPixel::CanvasPixel()
{
}

rt::CanvasPixel::CanvasPixel(
	const float& aX, 
	const float& aY, 
	const float& aZ)
	: X(aX)
	, Y(aY)
	, Z(aZ)
{
}

rt::CanvasPixel::CanvasPixel(
	const CanvasPixel & aAnotherPoint)
{
	X = aAnotherPoint.X;
	Y = aAnotherPoint.Y;
	Z = aAnotherPoint.Z;
}

rt::CanvasPixel 
rt::CanvasPixel::operator=(
	const CanvasPixel & aAnotherPoint)
{
	X = aAnotherPoint.X;
	Y = aAnotherPoint.Y;
	Z = aAnotherPoint.Z;

	return *this;
}