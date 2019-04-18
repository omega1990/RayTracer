#include <cmath>

#include "../inc/Singleton.h"
#include "../inc/Line.hpp"
#include "../inc/World.hpp"

namespace rt 
{

class DebugHandler : public Singleton<DebugHandler>
{
	void DrawDebugLine(const Line& aLine);
};

}