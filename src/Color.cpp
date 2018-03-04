#include "../inc/Color.hpp"

rt::Color::Color()
	: Red(0)
	, Green(0)
	, Blue(0)
	, Alpha(255)
{
}

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
	uint8 red = Red * aNum < 255 ? (uint8)(Red * aNum) : 255;
	uint8 green = Green * aNum < 255 ? (uint8)(Green * aNum) : 255;
	uint8 blue = Blue * aNum < 255 ? (uint8)(Blue * aNum) : 255;

	return Color(red, green, blue, Alpha);
}

std::map<rt::ColorName, rt::Color> rt::Color::myPalette =
{
	{rt::RED, Color(255, 0, 0, 255)},
	{rt::SKY, Color(126, 151, 228, 255)},
	{rt::GREY, Color(100, 100, 100, 255)},
	{rt::DARK_BLUE, Color(0, 0, 100, 255)},
	{rt::DARK_GREY, Color(50, 50, 50, 255)},
	{rt::BLACK, Color(0, 0, 0, 255)},
	{rt::SPHERE, Color(232, 50, 50)}
};