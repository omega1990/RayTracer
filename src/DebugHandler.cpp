
#include "../inc/DebugHandler.h"

#include <algorithm>


void rt::DebugHandler::Draw(rt::DebugEntity* aDebugEntity)
{
	auto&& it = std::find_if(myDebugEntities.begin(), myDebugEntities.end(), [&](uint64_t entityId) { return entityId == aDebugEntity->Id;  });
	if (it != myDebugEntities.end())
		return;

	if (rt::Line* line = dynamic_cast<rt::Line*>(aDebugEntity))
	{
		DrawDebugLine(*line);
		myDebugEntities.push_back(aDebugEntity->Id);
	}
}

void rt::DebugHandler::DrawDebugLine(rt::Line& aLine)
{
	rt::World::GetInstance().AddShape(reinterpret_cast<rt::Shape*>(&aLine));
}


