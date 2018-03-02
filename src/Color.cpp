#include "../inc/Color.hpp"

rt::Color::Color(
	const uint8& aRed, 
	const uint8& aGreen, 
	const uint8& aBlue,
	const uint8& aAlpha = 255)
	: Red(aRed)
	, Green(aGreen)
	, Blue(aBlue)
	, Alpha(aAlpha)
{
}

rt::Color::Color(
	const rt::ColorName& aColor)
{
	Color color = myPalette[aColor];
	*this = color;
}

const rt::Color 
rt::Color::operator-(const float& aNum) const
{
	uint8 red = Red - aNum > 0 ? Red - (uint8)aNum : 0;
	uint8 green = Green - aNum > 0 ? Green - (uint8)aNum : 0;
	uint8 blue = Blue - aNum > 0 ? Blue - (uint8)aNum : 0;

	return Color(red, green, blue, Alpha);
}

const rt::Color
rt::Color::operator+(const float& aNum) const
{
	uint8 red = Red + aNum < 255 ? Red + (uint8)aNum : 255;
	uint8 green = Green + aNum < 255 ? Green + (uint8)aNum : 255;
	uint8 blue = Blue + aNum < 255 ? Blue + (uint8)aNum : 255;

	return Color(red, green, blue, Alpha);
}

const rt::Color
rt::Color::operator*(const float& aNum) const
{
	uint8 red = Red * aNum < 255 ? Red * (uint8)aNum : 255;
	uint8 green = Green * aNum < 255 ? Green * (uint8)aNum : 255;
	uint8 blue = Blue * aNum < 255 ? Blue * (uint8)aNum : 255;

	return Color(red, green, blue, Alpha);
}

const std::vector<rt::Color> rt::Color::myPalette =
{
	Color(255, 0, 0, 255),
	Color(126, 151, 228, 255),
	Color(100, 100, 100, 255),
	Color(0, 0, 100, 255),
	Color(50, 50, 50, 255),
};