#pragma once

#include <cstdint>

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

		uint32 GetWidth() const;
		uint32 GetHeight() const;


	private:
		uint32 myWidth  = DEFAULT_CANVAS_WIDTH;
		uint32 myHeight = DEFAULT_CANVAS_HEIGHT;
	};

	class Camera
	{
	public:
		Camera();
		Camera(const Vector<float>& aPoint);
		Camera(float aX, float aY, float aZ);

		Vector<float> GetPosition	() const;
		const Canvas& GetCanvas		() const;
		Vector<float> GetDirection	() const;
		Vector<float> GetTilt		() const;
		void MoveUp					(float aPixels);
		void MoveDown				(float aPixels);
		void MoveRight				(float aPixels);
		void MoveLeft				(float aPixels);

	private:
		void PrivCalculateRays();

		Vector<float> myPosition{ 0.0f, 100.0f, -590.0f };
		Vector<float> myDirection{ 0.0f, -0.3f, 1.0f }; //r
		Vector<float> myTilt{ 1.0f, 0.0f, 0.0f }; //p
		float myFocalDistance = DEFAULT_FOCAL_DISTANCE;

		Canvas myCanvas;
	};
	
}