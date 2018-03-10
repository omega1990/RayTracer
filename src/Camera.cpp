#include "../inc/Camera.hpp"
#include "../inc/Defaults.hpp"

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
rt::Camera::MoveRight(
	float aPixels)
{
	myDirection.SetX(myDirection.GetX() + aPixels);
	PrivCalculateRays();
}

void
rt::Camera::MoveLeft(
	float aPixels)
{
	myDirection.SetX(myDirection.GetX() - aPixels);
	PrivCalculateRays();
}

void 
rt::Camera::PrivCalculateRays()
{
	// Pixels are calculated in the local coordinate system
	// Important: For using this, it needs to be converted 
	// to the world coordinates

	myCanvas.CanvasPixels.clear();

	rt::Vector<float> yCameraAxis = myDirection.Cross(myTilt);

	int canvasHeight = static_cast<int>(myCanvas.GetHeight());
	int canvasWidth = static_cast<int>(myCanvas.GetWidth());
	
	for (int i = -canvasHeight / 2; i < canvasHeight / 2; i++)
	{
		for (int j = -canvasWidth / 2; j < canvasWidth / 2; j++)
		{
			CanvasPixel pixel(
				myTilt.GetX() * j + yCameraAxis.GetX() * i + myDirection.GetX() * myFocalDistance, // x
				myTilt.GetY() * j + yCameraAxis.GetY() * i + myDirection.GetY() * myFocalDistance, // y 
				myTilt.GetZ() * j + yCameraAxis.GetZ() * i + myDirection.GetZ() * myFocalDistance // z
			);

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

uint32 
rt::Canvas::GetWidth() const
{
	return myWidth;
}

uint32 
rt::Canvas::GetHeight() const
{
	return myHeight;
}
