#include "../inc/Defaults.hpp"
#include "../inc/Color.hpp"

namespace rt
{
	class DrawPixel
	{
	public:
		DrawPixel(	const Color&	aColor,
					const int&		aX,
					const int&		aY);

		Color myColor;
		int myX;
		int myY;
	};
}