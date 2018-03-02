#pragma once

#include <cstdint>
#include <vector>

#define uint8 uint8_t

namespace rt
{
	enum ColorName
	{
		RED = 0,
		SKY = 1,
		GREY = 2,
		DARK_BLUE = 3,
		DARK_GREY = 4
	};

	class Color
	{
	public:
		Color(const uint8& aRed,
			const uint8& aGreen,
			const uint8& aBlue,
			const uint8& aAlpha);

		Color(
			const rt::ColorName& aColor);

		const Color operator-(const float& aNum) const;
		const Color operator+(const float & aNum) const;
		const Color operator*(const float & aNum) const;

		const static std::vector<Color> myPalette;

		uint8 Red = 0;
		uint8 Green = 0;
		uint8 Blue = 0;
		uint8 Alpha = 0;
	};
}
