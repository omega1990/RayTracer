#pragma once

#include <cstdint>
#include <vector>
#include <map>

#define uint8 uint8_t

namespace rt
{
	enum ColorName
	{
		RED = 0,
		SKY,
		GREY,
		DARK_BLUE,
		DARK_GREY,
		BLACK, 
		SPHERE,
		COPPER,
		CHROME
	};

	class Color
	{
	public:
		Color();
	
		Color(const uint8& aRed,
			const uint8& aGreen,
			const uint8& aBlue,
			const uint8& aAlpha);

		Color(
			const rt::ColorName& aColor);

		const Color operator-(const float& aNum) const;
		const Color operator+(const float& aNum) const;
		const Color operator*(const float& aNum) const;
		const Color operator+(const Color& aColor) const;


		static std::map<ColorName, Color> myPalette;

		uint8 Red = 0;
		uint8 Green = 0;
		uint8 Blue = 0;
		uint8 Alpha = 0;
	};
}
