#pragma once

#include "SDL.h"
#include "Color.hpp"
#include "Vector.hpp"

#include <vector>

struct DebugLine
{
	rt::VectorF myLineNormal;
	float myLength;
};

class Debug
{
public:
	Debug(SDL_Renderer* const aRenderer);
	~Debug();

	void DrawDebugLine(const rt::Color& aColor, const rt::VectorF& aLineRoot, const rt::VectorF& aLineNormal, float aLength);

private:
	SDL_Renderer* const myRenderer;

};