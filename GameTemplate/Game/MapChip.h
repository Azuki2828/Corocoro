#pragma once

#include "Level.h"
#include "physics/PhysicsStaticObject.h"

class MapChip
{
public:
	MapChip(const LevelObjectData& objData);

private:
	PhysicsStaticObject m_physicsStaticObject;
};

