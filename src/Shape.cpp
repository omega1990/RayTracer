#include "../inc/Shape.hpp"

const rt::Color& 
rt::Shape::GetColor() const
{
	return myColor;
}

rt::Shape::Shape()
{
}

rt::Shape::Shape(
	const Color & aColor)
	:myColor(aColor)
{
}
