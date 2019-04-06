
#include "../inc/Debug.h"

Debug::Debug(SDL_Renderer* const aRenderer)
	: myRenderer(aRenderer)
{

}

Debug::~Debug()
{

}

void Debug::DrawDebugLine(const rt::Color& aColor, const rt::VectorF& aLineStart, const rt::VectorF& aLineNormal, float aLength)
{
}
