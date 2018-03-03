#pragma once

#include "Vector.hpp"
#include "Defaults.hpp"
#include "Point.hpp"

namespace rt
{
	class Canvas
	{
	public:
		Canvas();
		Canvas(const float& aWidth, const float& aHeight);
		std::vector<CanvasPixel> CanvasPixels;

		float GetWidth() const;
		float GetHeight() const;


	private:
		float myWidth = DEFAULT_CANVAS_WIDTH;
		float myHeight = DEFAULT_CANVAS_HEIGHT;
	};

	class Camera
	{
	public:
		Camera();
		Camera(const Vector<float>& aPoint);
		Camera(float aX, float aY, float aZ);

		Vector<float> GetPosition	() const;
		const Canvas& GetCanvas		() const;
		void MoveUp					(float aPixels);


	private:
		void PrivCalculateRays();

		Vector<float> myPosition{ 0.0f, 100.0f, 50.0f };
		Vector<float> myDirection{ 0.0f, 0.0f, -1.0f };
		float myFocalDistance = DEFAULT_FOCAL_DISTANCE;

		Canvas myCanvas;
	};
	
}