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

void 
rt::Camera::MoveUp(	
	float aPixels)
{
	myPosition.SetY(myPosition.GetY() + aPixels);
	PrivCalculateRays();
}

void 
rt::Camera::PrivCalculateRays()
{
	// TODO: make this generic
	myCanvas.CanvasPixels.clear();

	int canvasHeight = static_cast<int>(myCanvas.GetHeight());
	int canvasWidth = static_cast<int>(myCanvas.GetWidth());
	
	for (int i = -canvasHeight / 2; i < canvasHeight / 2; i++)
	{
		for (int j = -canvasWidth / 2; j < canvasWidth / 2; j++)
		{
			auto x = myPosition.GetX() + j;
			auto y = myPosition.GetY() + i;
			auto z = myPosition.GetZ() + myFocalDistance;
			
			// TODO: camera position
			CanvasPixel pixel(x, y, z);
			//myCanvas.CanvasPixels.clear();
			//pixel.SetRayVector(Vector<float>(x, y, z));
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
