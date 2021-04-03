#pragma once
#include "stdafx.h"
#include "../../ExEngine/gameObject/IGameobject.h"

class LightBase : public IGameObject
{
	bool Start();
public:
	virtual bool StartSub() = 0;
	virtual void* GetLigData() = 0;
};

