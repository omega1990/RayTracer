#include "../inc/Camera.hpp"

using namespace rt;

rt::Camera::Camera()
{
	PrivCalculateRays();
}

Camera::Camera(
	const Vector<float>& aPoint)
{
	myPosition = aPoint;
	PrivCalculateRays();
}

rt::Camera::Camera(
	float aX, 
	float aY, 
	float aZ)
	: myPosition(Vector<float>(aX, aY, aZ))
{
	PrivCalculateRays();
}

Vector<float> 
rt::Camera::GetPosition() const
{
	return myPosition;
}

const Canvas&
rt::Camera::GetCanvas() const
{
	return myCanvas;
}

Vector<float>
rt::Camera::GetDirection() const
{
	return myDirection;
}

rt::Vector<float> 
rt::Camera::GetTilt() const
{
	return myTilt;
}

void 
rt::Camera::MoveUp(	
	float aPixels)
{	
	myDirection.SetY(myDirection.GetY() + aPixels);
	PrivCalculateRays();
}

void
rt::Camera::MoveDown(
	float aPixels)
{
	myDirection.SetY(myDirection.GetY() - aPixels);
	PrivCalculateRays();
}

void 
rt::Camera::PrivCalculateRays()
{
	// Pixels are calculated in the local coordinate system
	// Important: For using this, it needs to be converted 
	// to the world coordinates

	myCanvas.CanvasPixels.clear();

	int canvasHeight = static_cast<int>(myCanvas.GetHeight());
	int canvasWidth = static_cast<int>(myCanvas.GetWidth());
	
	for (int i = -canvasHeight / 2; i < canvasHeight / 2; i++)
	{
		for (int j = -canvasWidth / 2; j < canvasWidth / 2; j++)
		{
			auto x = j;
			auto y = i;
			auto z = myFocalDistance;
			
			CanvasPixel pixel(x, y, z);
			myCanvas.CanvasPixels.push_back(pixel);
		}
	}
}

rt::Canvas::Canvas()
{
}

rt::Canvas::Canvas(
	const float & aWidth, 
	const float & aHeight)
	: myWidth(aWidth)
	, myHeight(aHeight)
{
}

float 
rt::Canvas::GetWidth() const
{
	return myWidth;
}

float 
rt::Canvas::GetHeight() const
{
	return myHeight;
}
