#include "../inc/ScopedPerfTracker.h"

#include "SDL.h"

#include <iostream>

ScopedPerfTracker::ScopedPerfTracker(const std::string& aName)
	: myName(aName)
{
	myTimer = SDL_GetTicks();
}

ScopedPerfTracker::~ScopedPerfTracker()
{
	std::cout << myName << ": " << SDL_GetTicks() - myTimer << std::endl;
}
