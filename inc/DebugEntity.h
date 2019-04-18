#pragma once

#include <stdint.h>

namespace rt 
{

class DebugEntity
{
public: 
	virtual ~DebugEntity() = default;
	uint64_t Id;
};

}