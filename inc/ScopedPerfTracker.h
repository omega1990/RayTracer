#pragma once

#include "SDL.h"

#include <string>

class ScopedPerfTracker
{
public:
	ScopedPerfTracker(const std::string& aName);
	~ScopedPerfTracker();

private:
	std::string myName;
	Uint64 myTimer;
};

