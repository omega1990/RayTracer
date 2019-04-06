#include "../inc/LightSource.h"


namespace rt
{

LightSource::LightSource(const rt::Vector<float>& aPosition, float aIntensity)
	: myPosition(aPosition)
	, myIntensity(aIntensity)
{
}


LightSource::~LightSource()
{
}

}
