#pragma once
#include "stdafx.h"
#include "../../ExEngine/gameObject/IGameobject.h"

class LightBase : public IGameObject
{
	bool Start();
public:
	~LightBase();
	virtual bool StartSub() = 0;
	//ライトのデータを取得する関数。
	virtual void* GetLigData() = 0;
};

