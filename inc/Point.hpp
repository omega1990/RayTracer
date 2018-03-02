#pragma once

#include "Vector.hpp"

namespace rt
{
	class CanvasPixel
	{
	public:
		CanvasPixel();
		CanvasPixel(const float& aX, const float& aY, const float& aZ);
		CanvasPixel(const CanvasPixel& aAnotherPoint);
		CanvasPixel operator=(const CanvasPixel& aAnotherPoint);

		float X{ 0 };
		float Y{ 0 };
		float Z{ 0 };

	private:
		Vector<float> myRayVector{ 0.0f, 0.0f, 0.0f };
	};
}