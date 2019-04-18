#pragma once

#include "Singleton.h"
#include "Line.hpp"
#include "World.hpp"
#include "DebugEntity.h"

namespace rt 
{

class DebugHandler : public Singleton<DebugHandler>
{
public:
	void Draw(rt::DebugEntity* aDebugEntity);
	void DrawDebugLine(Line& aLine);

private:
	std::vector<uint64_t> myDebugEntities;

};

}